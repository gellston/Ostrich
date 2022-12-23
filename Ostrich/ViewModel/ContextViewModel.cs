using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace ViewModel
{
    public class ContextViewModel : ViewModelBase, ICloneable
    {

        #region PrivateProperty
        private string _Name = "";
        private string _NativeContext = "";
        private ObservableCollection<NodeViewModel> _NodeViewModelCollection = new ObservableCollection<NodeViewModel>();
        private ObservableCollection<ConnectorViewModel> _ConnectorViewModelCollection = new ObservableCollection<ConnectorViewModel>();
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

        public ObservableCollection<ConnectorViewModel> ConnectorViewModelCollection
        {
            get => _ConnectorViewModelCollection;
            set => SetProperty(ref _ConnectorViewModelCollection, value);
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


        public void UnRegisterConnector(List<ConnectorViewModel> connectors)
        {
            foreach(var connector in connectors)
            {
                this.ConnectorViewModelCollection.Remove(connector);
            }
        }

        public void UnRegisterConnector(ConnectorViewModel connector)
        {
            this.ConnectorViewModelCollection.Remove(connector);
        }


        public object Clone()
        {

            ObservableCollection<ConnectorViewModel> connectorViewModelCollection = new ObservableCollection<ConnectorViewModel>();
            ObservableCollection<NodeViewModel> nodeViewModelCollection = new ObservableCollection<NodeViewModel>();
            ObservableCollection<NodeInfoViewModel> nodeInfoViewModelCollection = new ObservableCollection<NodeInfoViewModel>();
            ObservableCollection<AddonViewModel> addonViewModelCollection = new ObservableCollection<AddonViewModel>();

            foreach (var connector in this.ConnectorViewModelCollection)
            {
                connectorViewModelCollection.Add((ConnectorViewModel)connector.Clone());
            }

            foreach (var node in this.NodeViewModelCollection)
            {
                var _node = (NodeViewModel)node.Clone();
                foreach (var inputProperty in _node.InputCollection)
                {
                    foreach (var connector in connectorViewModelCollection)
                    {
                        if (inputProperty.Uid == connector.TargetPropertyUID &&
                           inputProperty.ObjectType == connector.TargetObjectType &&
                           inputProperty.Name == connector.TargetPropertyName)
                        {
                            inputProperty.RegisterTargetConnectorViewModel(connector);
                        }
                    }
                }

                foreach (var outputProperty in _node.OutputCollection)
                {
                    foreach (var connector in connectorViewModelCollection)
                    {
                        if (outputProperty.Uid == connector.SourcePropertyUID &&
                            outputProperty.ObjectType == connector.SourceObjectType &&
                            outputProperty.Name == connector.SourcePropertyName)
                        {
                            outputProperty.RegisterSourceConnectorViewModel(connector);
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
                ConnectorViewModelCollection = connectorViewModelCollection,
                NodeViewModelCollection = nodeViewModelCollection,
                NodeInfoViewModelCollection = nodeInfoViewModelCollection,
                AddonViewModelCollection = addonViewModelCollection
            };

            return context;
        }
        #endregion
    }
}
