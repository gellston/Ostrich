﻿using CommunityToolkit.Mvvm.Input;
using DevExpress.Mvvm.Native;
using DevExpress.Utils.Extensions;
using DevExpress.Xpf.Printing.PreviewControl;
using HV.V2;
using Model;
using Model.EventParameter;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing.Text;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using ViewModel;

namespace Ostrich.Service
{
    public class NodeEngineManagerService
    {

        #region PrivateProperty
        private HV.V2.Script _NodeEngineModel = null;
        private ObservableCollection<ContextViewModel> _ContextViewModelCollection = new ObservableCollection<ContextViewModel>();
        private ObservableCollection<Addon> _AddonCollection = new ObservableCollection<Addon>();
        #endregion

        public NodeEngineManagerService()
        {
            this._NodeEngineModel = new HV.V2.Script();


            // Addon 경로 설정
            var currentPath = System.AppDomain.CurrentDomain.BaseDirectory;
            this._NodeEngineModel.SetAddonPath(currentPath);


        }


        #region Collection
        public ObservableCollection<ContextViewModel> ContextViewModelCollection
        {
            get => _ContextViewModelCollection;
        }

        public ObservableCollection<Addon> AddonCollection
        {
            get => _AddonCollection;
        }
        #endregion


        #region Public Property
        public HV.V2.Script NodeEngineModel()
        {
            return this._NodeEngineModel;
        }



        public void Run(string contextName)
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

                this._NodeEngineModel.Run(contextName, selectedNode[0].Uid);

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

            }catch(Exception ex)
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
                        var name = context.NodeInfoViewModelCollection.FirstOrDefault(info => info.ObjectType == objectType).NodeName;
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
                                PropertyModel = PropertyModelConstructor.Create(input.Type, this.ModelChangingCommand),
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
                                PropertyModel = PropertyModelConstructor.Create(output.Type, this.ModelChangingCommand),
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
                var sourceContext = this.ContextViewModelCollection.First(context => context.Name == sourceContextName);
                var targetContext = (ContextViewModel)sourceContext.Clone();
                targetContext.Name = targetContextName;

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
                context.Name = targetContextName;

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

                this._NodeEngineModel.RemoveContext(name);
                var context = this.ContextViewModelCollection.First(context => context.Name == name);
                this.ContextViewModelCollection.Remove(context);


            }catch(Exception ex)
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
                    Name = name
                };


                var managedContext = this._NodeEngineModel.Context(name);

                managedContext.RegisterProcessCompleteEvent(context.OnProcessCompleteHandler);
                managedContext.RegisterConstChangedEvent(context.OnConstChangedHandler);


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
            }catch(Exception ex)
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
                    System.Diagnostics.Debug.WriteLine("Mdoel chagned Test !!! =  " + arg.Data.ToString());
                    arg.Changed = true;
                }catch(Exception e)
                {

                }
            });
        }
        #endregion

    }
}