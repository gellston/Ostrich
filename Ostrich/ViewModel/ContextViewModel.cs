using Model.EventParameter;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace ViewModel
{
    public class ContextViewModel : ViewModelBase, ICloneable
    {

        #region PrivateProperty
        private string _Name = "";
        private string _NativeContext = "";
        private ObservableCollection<NodeViewModel> _NodeViewModelCollection = new ObservableCollection<NodeViewModel>();
        private ObservableCollection<NodePathViewModel> _NodePathViewModelCollection = new ObservableCollection<NodePathViewModel>();
        private ObservableCollection<AddonViewModel> _AddonViewModelCollection = new ObservableCollection<AddonViewModel>();
        private ObservableCollection<NodeInfoViewModel> _NodeInfoViewModelCollection = new ObservableCollection<NodeInfoViewModel>();
        private double _Scale = 1;
        private double _CanvasStartX = 0;
        private double _CanvasStartY = 0;

        private double _CurrentDragPositionX = 0;
        private double _CurrentDragPositionY = 0;

        #endregion



        #region Constructor
        public ContextViewModel() { 
        

        }

        #endregion




        #region Command


        public ICommand ConstNodeChangedCommand { get; set; } = null;


        #endregion



        #region PublicProperty
        public string Name
        {
            get => _Name;
            set => SetProperty(ref _Name, value);
        }

        public string NativeContext
        {
            get => _NativeContext;
            set => SetProperty(ref _NativeContext, value);  
        }

        public ObservableCollection<NodePathViewModel> NodePathViewModelCollection
        {
            get => _NodePathViewModelCollection;
            set => SetProperty(ref _NodePathViewModelCollection, value);
        }

        public ObservableCollection<NodeViewModel> NodeViewModelCollection
        {
            get => _NodeViewModelCollection;
            set => SetProperty(ref _NodeViewModelCollection, value);
        }

        public ObservableCollection<AddonViewModel> AddonViewModelCollection
        {
            get => _AddonViewModelCollection;
            set => SetProperty(ref _AddonViewModelCollection, value);
        }

        public ObservableCollection<NodeInfoViewModel> NodeInfoViewModelCollection
        {
            get => _NodeInfoViewModelCollection;
            set => SetProperty(ref _NodeInfoViewModelCollection, value);
        }

        public double Scale
        {
            get => _Scale;
            set => SetProperty(ref _Scale, value);
        }

        public double CanvasStartX
        {
            get => _CanvasStartX;
            set => SetProperty(ref _CanvasStartX, value);
        }

        public double CanvasStartY
        {
            get => _CanvasStartY;
            set => SetProperty(ref _CanvasStartY, value);
        }

        public double CurrentDragPositionX
        {
            get => _CurrentDragPositionX;
            set => SetProperty(ref _CurrentDragPositionX, value);
        }

        public double CurrentDragPositionY
        {
            get => _CurrentDragPositionY;
            set => SetProperty(ref _CurrentDragPositionY, value);
        }




        #endregion



        #region Function

        public void OnProcessCompleteHandler(System.Object sender, int nodeType, ulong compositeUID)
        {

            foreach (var node in this.NodeViewModelCollection)
            {
                if (node.Uid == compositeUID)
                    node.IsExecuting = false;
            }
        }

        public void OnConstChangedHandler(System.Object sender, int nodeType, ulong constUID)
        {

            var arg = new ModelChangedArg()
            {
                ContextName = this.Name,
                Data = null,
                Changed = false,
                ObjectType = nodeType,
                Uid = constUID,
            };

            this.ConstNodeChangedCommand.Execute(arg);
        }

        public void OnProcessStartHandler(System.Object sender, int nodeType, ulong compositeUID)
        {
            foreach (var node in this.NodeViewModelCollection)
            {
                if (node.Uid == compositeUID)
                    node.IsExecuting = true;
            }
        }


        public void ClearExecutionStatus()
        {
            foreach(var node in this.NodeViewModelCollection)
            {
                node.IsExecuting = false;
            }
        }
        public void ContextName(string name)
        {
            this.Name = name;
            foreach(var node in this.NodeViewModelCollection)
            {
                foreach(var input in node.InputCollection)
                {
                    input.PropertyModel.ContextName = name;
                }

                foreach(var output in node.OutputCollection)
                {
                    output.PropertyModel.ContextName = name;
                }
            }
        }

        public void UnRegisterPath(List<NodePathViewModel> paths)
        {
            foreach(var path in paths)
            {
                this.NodePathViewModelCollection.Remove(path);
            }
        }

        public void UnRegisterPath(NodePathViewModel paths)
        {
            this.NodePathViewModelCollection.Remove(paths);
        }


        public object Clone()
        {

            ObservableCollection<NodePathViewModel> nodePathViewModelCollection = new ObservableCollection<NodePathViewModel>();
            ObservableCollection<NodeViewModel> nodeViewModelCollection = new ObservableCollection<NodeViewModel>();
            ObservableCollection<NodeInfoViewModel> nodeInfoViewModelCollection = new ObservableCollection<NodeInfoViewModel>();
            ObservableCollection<AddonViewModel> addonViewModelCollection = new ObservableCollection<AddonViewModel>();

            foreach (var path in this.NodePathViewModelCollection)
            {
                nodePathViewModelCollection.Add((NodePathViewModel)path.Clone());
            }

            foreach (var node in this.NodeViewModelCollection)
            {
                var _node = (NodeViewModel)node.Clone();
                foreach (var inputProperty in _node.InputCollection)
                {
                    foreach (var path in nodePathViewModelCollection)
                    {
                        if (inputProperty.Uid == path.TargetPropertyUID &&
                           inputProperty.ObjectType == path.TargetObjectType &&
                           inputProperty.Name == path.TargetPropertyName)
                        {
                            inputProperty.RegisterTargetPathViewModel(path);
                        }
                    }
                }

                foreach (var outputProperty in _node.OutputCollection)
                {
                    foreach (var nodePath in nodePathViewModelCollection)
                    {
                        if (outputProperty.Uid == nodePath.SourcePropertyUID &&
                            outputProperty.ObjectType == nodePath.SourceObjectType &&
                            outputProperty.Name == nodePath.SourcePropertyName)
                        {
                            outputProperty.RegisterSourcePathViewModel(nodePath);
                        }
                    }
                }
                nodeViewModelCollection.Add(_node);
            }


            foreach (var nodeInfo in this.NodeInfoViewModelCollection)
            {
                nodeInfoViewModelCollection.Add((NodeInfoViewModel)nodeInfo.Clone());
            }

            foreach (var addonViewModel in this.AddonViewModelCollection)
            {
                addonViewModelCollection.Add((AddonViewModel)addonViewModel.Clone());
            }

            var context = new ContextViewModel()
            {
                Name = this.Name,
                CanvasStartX = this.CanvasStartX,
                CanvasStartY = this.CanvasStartY,
                Scale = this.Scale,
                NativeContext = this.NativeContext,
                NodePathViewModelCollection = nodePathViewModelCollection,
                NodeViewModelCollection = nodeViewModelCollection,
                NodeInfoViewModelCollection = nodeInfoViewModelCollection,
                AddonViewModelCollection = addonViewModelCollection,


                ConstNodeChangedCommand = this.ConstNodeChangedCommand,
            };

            context.ContextName(this.Name);

            return context;
        }
        #endregion
    }
}
