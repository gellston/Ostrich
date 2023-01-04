using CommunityToolkit.Mvvm.Input;
using DevExpress.Diagram.Core.Shapes;
using DevExpress.Mvvm.Native;
using DevExpress.Utils.Extensions;
using DevExpress.Xpf.Printing.PreviewControl;
using HV.V2;
using Model;
using Model.EventParameter;
using Newtonsoft.Json;
using Ostrich.Model;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing.Text;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using System.Windows.Input;
using ViewModel;
using static DevExpress.Xpo.Helpers.AssociatedCollectionCriteriaHelper;

namespace Ostrich.Service
{
    public class NodeEngineManagerService
    {

        #region PrivateProperty
        private HV.V2.Script _NodeEngineModel = null;
        private ObservableCollection<ContextViewModel> _ContextViewModelCollection = new ObservableCollection<ContextViewModel>();
        private ObservableCollection<Ostrich.Model.Addon> _AddonCollection = new ObservableCollection<Ostrich.Model.Addon>();
        private ConcurrentQueue<Model.ConstNodeModel> _ConstNodeModelUpdateCollection = new ConcurrentQueue<Model.ConstNodeModel>();
        private object _lockUpdate = new object();

        #endregion

        public NodeEngineManagerService()
        {
            this._NodeEngineModel = new HV.V2.Script();


            // Addon 경로 설정
            var currentPath = System.AppDomain.CurrentDomain.BaseDirectory;
            var addonPath = currentPath + "Addon\\";

            if (!Directory.Exists(addonPath))
            {
                Directory.CreateDirectory(addonPath);
            }

            this._NodeEngineModel.SetAddonPath(addonPath);


        }


        #region Collection
        public ObservableCollection<ContextViewModel> ContextViewModelCollection
        {
            get => _ContextViewModelCollection;
        }

        public ObservableCollection<Ostrich.Model.Addon> AddonCollection
        {
            get => _AddonCollection;
        }
        #endregion


        
        #region Public Property

        public void LoadContextFromFile(string filePath)
        {
            try
            {
    
                var jsonContent = File.ReadAllText(filePath);
                var diagramContext = JsonConvert.DeserializeObject<VisionDiagramFile>(jsonContent);
                var contextName = diagramContext.Name;
                var nativeContext = diagramContext.NativeContext;
                var nodeViewModelCollection = diagramContext.Nodes;
                var pathViewModelCollection = diagramContext.Paths;

                this._NodeEngineModel.CreateContext(contextName);
                this._NodeEngineModel.DeSerialization(contextName, nativeContext);

                var context = this.FindContext(contextName);
                context.NodeViewModelCollection = new ObservableCollection<NodeViewModel>(nodeViewModelCollection);
                context.NodePathViewModelCollection = new ObservableCollection<NodePathViewModel>(pathViewModelCollection);
                context.NativeContext = nativeContext;


                foreach(var nodeViewModel in nodeViewModelCollection )
                {


                    foreach(var input in nodeViewModel.InputCollection)
                    {
                        input.ParentNodeViewModel = nodeViewModel;
                        input.PropertyModel = PropertyModelConstructor.Create(contextName, input.ObjectType, input.Uid, this.ModelChangingCommand);

                        foreach(var path in pathViewModelCollection )
                        {
                            if(input.Uid == path.TargetPropertyUID && input.ObjectType == path.TargetObjectType)
                            {
                                input.RegisterTargetPathViewModel(path);
                            }
                        }
                    }

                    foreach(var output in nodeViewModel.OutputCollection)
                    {
                        output.ParentNodeViewModel = nodeViewModel;
                        output.PropertyModel = PropertyModelConstructor.Create(contextName, output.ObjectType, output.Uid, this.ModelChangingCommand);

                        foreach (var path in pathViewModelCollection)
                        {
                            if (output.Uid == path.SourcePropertyUID && output.ObjectType == path.SourceObjectType)
                            {
                                output.RegisterSourcePathViewModel(path);
                            }
                        }
                    }

                }

                this._NodeEngineModel.UpdateAllConstNode(contextName);

                this.ContextViewModelCollection.Add(context);



            }
            catch (Exception ex)
            {

                System.Diagnostics.Debug.WriteLine(ex.Message);
            }
        }


        public void SaveContextAsFile(string filePath, ContextViewModel context)
        {
            try {
                var file = new VisionDiagramFile()
                {
                    Name = context.Name,
                    NativeContext = this._NodeEngineModel.Serialization(context.Name),
                    Paths = context.NodePathViewModelCollection.ToList(),
                    Nodes = context.NodeViewModelCollection.ToList(),
                };


                var jsonContent = JsonConvert.SerializeObject(file, Formatting.Indented);
                File.WriteAllText(filePath, jsonContent);
            
            }catch(Exception ex)
            {

                System.Diagnostics.Debug.WriteLine(ex.Message);
            }
        }
        


        public void OnRendering()
        {
            if(this._NodeEngineModel != null && this._ConstNodeModelUpdateCollection != null)
            {

                if (this._ConstNodeModelUpdateCollection.Count > 0)
                {
                    var count = this._ConstNodeModelUpdateCollection.Count;
                    for (var index = 0; index < count; index++){

                        try
                        {
                            Model.ConstNodeModel model = new Model.ConstNodeModel();
                            if (this._ConstNodeModelUpdateCollection.TryDequeue(out model))
                            {
                                var context = this.ContextViewModelCollection.First(context => context.Name == model.ContextName);
                                foreach (var node in context.NodeViewModelCollection)
                                {
                                    foreach (var output in node.OutputCollection)
                                    {
                                        if (output.Uid == model.Uid)
                                        {
                                            output.PropertyModel.Update(model.Data);
                                        }
                                    }

                                    foreach (var input in node.InputCollection)
                                    {
                                        if (input.Uid == model.Uid)
                                        {
                                            input.PropertyModel.Update(model.Data);
                                        }
                                    }
                                }
                            }
                        }
                        catch(Exception ex)
                        {
                            System.Diagnostics.Debug.WriteLine(ex.ToString());
                        }
                    }
                }
            }
        }


        public HV.V2.Script NodeEngineModel()
        {
            return this._NodeEngineModel;
        }


        public void Stop(string contextName)
        {
            try
            {
                this._NodeEngineModel.Stop(contextName);


            }
            catch (Exception ex)
            {
                throw ex;
            }

        }

        public async Task Run(string contextName, int delay)
        {
            try
            {
                var context = this.ContextViewModelCollection.First(context => context.Name == contextName);
                var selectedNode = context.NodeViewModelCollection.Where(node => node.IsSelected == true).ToList();

                if(selectedNode.Count == 0)
                {
                    throw new Exception("Node is not selected");
                }


                if(selectedNode.Count > 1)
                {
                    throw new Exception("You should select only one node.");

                }

                try
                {

                    context.ClearExecutionStatus();
                    await Task.Run(async () =>
                    {

                        this._NodeEngineModel.ExecutionDelay = delay;
                        this._NodeEngineModel.Run(contextName, selectedNode[0].Uid);
                    });

                }
                catch(Exception ex)
                {
                    throw ex;
                }



            }
            catch (Exception ex)
            {
                throw ex;
            }
        }



        public bool CheckNodeConnectivity(string contextName, ulong sourceUID, string sourcePropertyName, ulong targetUID, string targetPropertyName)
        {

            try
            {

                /// this._NodeEngineModel.Connect(contextName, sourceUID, sourcePropertyName, targetUID, targetPropertyName);

                return this._NodeEngineModel.CheckConnectability(contextName, sourceUID, sourcePropertyName, targetUID, targetPropertyName);

            }catch(Exception ex)
            {

                return false;
            }

        }

        public void ConnectNode(string contextName, ulong sourceUID, string sourcePropertyName, ulong targetUID, string targetPropertyName)
        {
            try
            {
   
                this._NodeEngineModel.Connect(contextName, sourceUID, sourcePropertyName, targetUID, targetPropertyName);
                var context = this.ContextViewModelCollection.First(context => context.Name == contextName);
                //context.NativeContext = this._NodeEngineModel.Serialization(contextName);

            }
            catch(Exception ex)
            {
                throw ex;
            }
        }

        public void DeleteSelectedPaths(string contextName)
        {
            try
            {

                var context = this.ContextViewModelCollection.First(context => context.Name == contextName);
                var selectedPathViewModelCollection = context.NodePathViewModelCollection.Where(path => path.IsSelected == true).ToList();

                foreach(var pathViewModel in selectedPathViewModelCollection)
                {
                    try
                    {
                        this._NodeEngineModel.Disconnect(contextName, pathViewModel.TargetNodeUID, pathViewModel.TargetPropertyName);
                        foreach(var node in context.NodeViewModelCollection)
                        {
                            node.UnRegisterPath(pathViewModel);
                        }
                        context.NodePathViewModelCollection.Remove(pathViewModel);
                    }
                    catch(Exception exception1)
                    {

                    }
                }
            }
            catch(Exception exception2)
            {
                throw exception2;
            }
        }


        public void DeleteSelectedNodes(string contextName)
        {
            try
            {
                var context = this.ContextViewModelCollection.First(context => context.Name == contextName);
                var nodeViewModelCollection = context.NodeViewModelCollection.ToList();
                var pathViewModelCollection = context.NodePathViewModelCollection.ToList();

                List<NodePathViewModel> removePathCollection = new List<NodePathViewModel>();

                foreach (var nodeViewModel in nodeViewModelCollection)
                {
                    if (nodeViewModel.IsSelected == true)
                    {
                        try
                        {
                            this._NodeEngineModel.RemoveNode(contextName, nodeViewModel.Uid);
                            context.NodeViewModelCollection.Remove(nodeViewModel);
                            var paths = nodeViewModel.Paths();
                            foreach(var path in paths)
                                removePathCollection.Add(path);
                        }
                        catch(Exception e)
                        {
                            System.Diagnostics.Debug.WriteLine(e.Message);
                        }
                    }
                }

                foreach(var nodeViewModel in nodeViewModelCollection)
                {
                    nodeViewModel.UnRegisterPath(removePathCollection);
                }

                context.UnRegisterPath(removePathCollection);

            }
            catch(Exception ex)
            {
                throw ex;
            }
        }

        public void AddNode(string contextName, int objectType)
        {
            try
            {

                if(this.ContextViewModelCollection.Count(context => context.Name == contextName) > 0)
                {

                    var context = this.ContextViewModelCollection.First(context => context.Name == contextName);
                    var nodeLocationX = context.CurrentDragPositionX;
                    var nodeLocationY = context.CurrentDragPositionY;
                    
                    using (var node = this._NodeEngineModel.AddNode(contextName, DateTime.Now.ToString("yyyy MM dd HH:mm:ss:fff"), objectType))
                    {
                        //context.NativeContext = this._NodeEngineModel.Serialization(contextName);

                        var name = context.NodeInfoViewModelCollection.First(info => info.ObjectType == objectType).NodeName;
                        NodeViewModel nodeViewModel = new NodeViewModel()
                        {
                            Name = name,
                            IsEvent = node.IsEventNode,
                            Uid = node.Uid,
                            X = nodeLocationX,
                            Y = nodeLocationY,
                        };

                        var inputs = node.Inputs;
                        var outputs = node.Outputs;

                        foreach (var input in inputs)
                        {
                            var property = new NodePropertyViewModel()
                            {
                                Name = input.Name,
                                ObjectType = input.Type,
                                IsMultiple = input.IsMultiple,
                                PropertyModel = PropertyModelConstructor.Create(contextName, input.Type, input.Uid, this.ModelChangingCommand),
                                IsOutput = false,
                                ParentNodeViewModel = nodeViewModel,
                                Uid = input.Uid,
                            };
                            nodeViewModel.InputCollection.Add(property);
                        }

                        foreach (var output in outputs)
                        {
                            var property = new NodePropertyViewModel()
                            {
                                Name = output.Name,
                                ObjectType = output.Type,
                                IsMultiple = output.IsMultiple,
                                PropertyModel = PropertyModelConstructor.Create(contextName, output.Type, output.Uid, this.ModelChangingCommand),
                                IsOutput = true,
                                ParentNodeViewModel = nodeViewModel,
                                Uid = output.Uid,
                            };
                            nodeViewModel.OutputCollection.Add(property);
                        }

                        context.NodeViewModelCollection.Add(nodeViewModel);
                    }
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        public void CopyContext(string sourceContextName, string targetContextName)
        {
            try
            {

                this._NodeEngineModel.CopyContext(sourceContextName, targetContextName);
                var nativeContext = this._NodeEngineModel.Context(targetContextName);

                var sourceContext = this.ContextViewModelCollection.First(context => context.Name == sourceContextName);
                var targetContext = (ContextViewModel)sourceContext.Clone();
                targetContext.ContextName(targetContextName);



                this._NodeEngineModel.RegisterProcessStartEvent(targetContextName, targetContext.OnProcessStartHandler);
                this._NodeEngineModel.RegisterProcessCompleteEvent(targetContextName, targetContext.OnProcessCompleteHandler);
                this._NodeEngineModel.RegisterConstChangedEvent(targetContextName, targetContext.OnConstChangedHandler);


                this.ContextViewModelCollection.Add(targetContext);

            }
            catch(Exception ex)
            {
                throw ex;
            }

        }



        public void RenameContext(string sourceContextName, string targetContextName)
        {
            try
            {

                this._NodeEngineModel.RenameContext(sourceContextName, targetContextName);
                var context = this.ContextViewModelCollection.First(context => context.Name == sourceContextName);
                context.ContextName(targetContextName);
                //context.NativeContext = this._NodeEngineModel.Serialization(targetContextName);


            }
            catch(Exception ex)
            {
                throw ex;
            }
        }



        public void RemoveContext(string name)
        {
            try
            {
                var nativeContext = this._NodeEngineModel.Context(name);

                var context = this.ContextViewModelCollection.First(context => context.Name == name);

                this._NodeEngineModel.ResetProcessCompleteEvent(name);
                this._NodeEngineModel.ResetConstChangedEvent(name);
                this._NodeEngineModel.ResetProcessStartEvent(name);



                this._NodeEngineModel.RemoveContext(name);
                this.ContextViewModelCollection.Remove(context);


            }catch(Exception ex)
            {
                throw ex;
            }
        }

        public ContextViewModel FindContext(string name)
        {
            try
            {


                this._NodeEngineModel.Context(name);


                var context = new ContextViewModel()
                {
                    ConstNodeChangedCommand = this.ConstNodeChangedCommand
                };

                this._NodeEngineModel.RegisterProcessCompleteEvent(name, context.OnProcessCompleteHandler);
                this._NodeEngineModel.RegisterProcessStartEvent(name, context.OnProcessStartHandler);
                this._NodeEngineModel.RegisterConstChangedEvent(name, context.OnConstChangedHandler);

                var addonInfo = this._NodeEngineModel.AddonInfo(name);
                foreach (var info in addonInfo)
                {
                    var addonName = info.Item1; // Name
                    var addonVersion = info.Item2;

                    var addonViewModel = new AddonViewModel()
                    {
                        Name = addonName,
                        Version = addonVersion
                    };

                    context.AddonViewModelCollection.Add(addonViewModel);
                }


                var addons = this._NodeEngineModel.Addons(name);
                foreach (var addon in addons)
                {
                    var infomation = addon.Information;
                    foreach (var info in infomation)
                    {
                        if (info.Category == "Constant") continue;
                        var nodeInfoViewModel = new NodeInfoViewModel()
                        {
                            Category = info.Category,
                            Name = info.Name,
                            ObjectType = info.Type,
                            NodeName = info.NodeName
                        };
                        context.NodeInfoViewModelCollection.Add(nodeInfoViewModel);
                    }
                    addon.Dispose();
                }

                context.ContextName(name);
                //context.NativeContext = this._NodeEngineModel.Serialization(name);

                return context;
            }
            catch (Exception ex)
            {

                throw ex;

            }
        }


        public void CreateContext(string name)
        {
            try
            {


                this._NodeEngineModel.CreateContext(name);


                var context = new ContextViewModel()
                {
                    ConstNodeChangedCommand = this.ConstNodeChangedCommand
                };

                this._NodeEngineModel.RegisterProcessCompleteEvent(name, context.OnProcessCompleteHandler);
                this._NodeEngineModel.RegisterProcessStartEvent(name, context.OnProcessStartHandler);
                this._NodeEngineModel.RegisterConstChangedEvent(name, context.OnConstChangedHandler);


                this.ContextViewModelCollection.Add(context);
                var addonInfo = this._NodeEngineModel.AddonInfo(name);
                foreach(var info in addonInfo)
                {
                    var addonName = info.Item1; // Name
                    var addonVersion = info.Item2;

                    var addonViewModel = new AddonViewModel()
                    {
                        Name = addonName,
                        Version = addonVersion
                    };

                    context.AddonViewModelCollection.Add(addonViewModel);
                }


                var addons = this._NodeEngineModel.Addons(name);
                foreach(var addon in addons)
                {
                    var infomation = addon.Information;
                    foreach(var info in infomation)
                    {
                        if (info.Category == "Constant") continue;
                        var nodeInfoViewModel = new NodeInfoViewModel()
                        {
                            Category = info.Category,
                            Name = info.Name,
                            ObjectType = info.Type,
                            NodeName = info.NodeName
                        };
                        context.NodeInfoViewModelCollection.Add(nodeInfoViewModel);
                    }
                    addon.Dispose();
                }

                context.ContextName(name);
                //context.NativeContext = this._NodeEngineModel.Serialization(name);
            }
            catch(Exception ex)
            {

                throw ex;

            }
        }


        #endregion


        #region Command
        public ICommand ModelChangingCommand
        {
            get => new RelayCommand<ModelChangedArg>((arg) =>
            {

                try
                {
                    // ModelChagned Code Here
                    using (var constNode = this._NodeEngineModel.ConstNode(arg.ContextName, arg.Uid))
                    {
                        PropertyModelUpdater.Update(constNode.Type, arg, constNode.Handle);
                    }


                    arg.Changed = true;
                        
                }catch(Exception e)
                {
                    arg.Changed = false;

                    System.Diagnostics.Debug.WriteLine(e.Message);

                }
            });
        }

        public ICommand ConstNodeChangedCommand
        {
            get => new RelayCommand<ModelChangedArg>((arg) =>
            {

                lock (_lockUpdate)
                {
                    try
                    {

                        using (var constNode = this._NodeEngineModel.ConstNode(arg.ContextName, arg.Uid))
                        {
                            var constNodeModel = new Model.ConstNodeModel()
                            {
                                ContextName = arg.ContextName,
                                ObjectType = arg.ObjectType,
                                Uid = arg.Uid,
                                Data = PropertyModelExtracter.Extract(arg.ObjectType, constNode.Handle)
                            };
                            this._ConstNodeModelUpdateCollection.Enqueue(constNodeModel);
                        }
                    }
                    catch (Exception ex)
                    {
                        arg.Changed = false;

                        System.Diagnostics.Debug.WriteLine(ex.Message);
                    }
                }
            });
        }
        #endregion

    }
}
