using DevExpress.Mvvm.Native;
using DevExpress.Utils.Extensions;
using HV.V2;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing.Text;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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


        public void DeleteSelectedNodes(string contextName)
        {
            try
            {
                var context = this.ContextViewModelCollection.First(context => context.Name == contextName);
                var nodeViewModelCollection = context.NodeViewModelCollection.ToList();
                var connectorViewModelCollection = context.ConnectorViewModelCollection.ToList();

                List<ConnectorViewModel> removeConnectorCollection = new List<ConnectorViewModel>();

                foreach (var nodeViewModel in nodeViewModelCollection)
                {
                    if (nodeViewModel.IsSelected == true)
                    {
                        try
                        {
                            this._NodeEngineModel.RemoveNode(contextName, nodeViewModel.Uid);
                            context.NodeViewModelCollection.Remove(nodeViewModel);
                            var connectors = nodeViewModel.Connectors();
                            foreach(var connector in connectors)
                                removeConnectorCollection.Add(connector);
                        }
                        catch(Exception e)
                        {
                            System.Diagnostics.Debug.WriteLine(e.Message);
                        }
                    }
                }

                foreach(var nodeViewModel in nodeViewModelCollection)
                {
                    nodeViewModel.UnRegisterConnector(removeConnectorCollection);
                }

                context.UnRegisterConnector(removeConnectorCollection);

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

    }
}
