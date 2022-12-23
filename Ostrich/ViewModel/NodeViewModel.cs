using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows.Documents;

namespace ViewModel
{
    public class NodeViewModel : ViewModelBase, ICloneable
    {

        #region Private Property
        private bool _IsSelected = false;
        private bool _IsEvent = false;
        private double _X = 0;
        private double _Y = 0;
        private string _Name = "";
        private ulong _Uid = 0;
        private ObservableCollection<NodePropertyViewModel> _InputCollection = new ObservableCollection<NodePropertyViewModel>();
        private ObservableCollection<NodePropertyViewModel> _OutputCollection = new ObservableCollection<NodePropertyViewModel>();
        #endregion


        #region Constructor
        public NodeViewModel() {

        }
        #endregion


        #region Public Property

        public ulong Uid
        {
            get => _Uid;
            set => SetProperty(ref _Uid, value);
        }

        public bool IsEvent
        {
            get => _IsEvent;
            set => SetProperty(ref _IsEvent, value);
        }

        public bool IsSelected
        {
            get => _IsSelected;
            set => SetProperty(ref _IsSelected, value);
        }

        public double X
        {
            get => _X;
            set => SetProperty(ref _X, value);
        }

        public double Y
        {
            get => _Y;
            set => SetProperty(ref _Y, value);
        }

        public string Name
        {
            get => _Name;
            set => SetProperty(ref _Name, value);
        }
        #endregion


        #region Collection
        public ObservableCollection<NodePropertyViewModel> InputCollection
        {
            get => _InputCollection;
            set => SetProperty(ref _InputCollection, value);
        }

        public ObservableCollection<NodePropertyViewModel> OutputCollection
        {
            get => _OutputCollection;
            set => SetProperty(ref _OutputCollection, value);
        }


        #endregion


        #region Functions
        public void RegisterInputProperty(NodePropertyViewModel property)
        {
            property.ParentNodeViewModel = this;
            this.InputCollection.Add(property);
        }

        public void RegisterOutputProperty(NodePropertyViewModel property)
        {
            property.ParentNodeViewModel = this;
            this.OutputCollection.Add(property);
        }


        public void UnRegisterConnector(List<ConnectorViewModel> connectors)
        {
            foreach(var connector in connectors)
            {
                this.UnRegisterConnector(connector);
            }
        }

        public void UnRegisterConnector(ConnectorViewModel connector)
        {
            foreach (var input in this.InputCollection)
            {
                input.UnRegisterSourceConnectorViewModel(connector);
                input.UnRegisterTargetConnectorViewModel(connector);
            }

            foreach (var output in this.OutputCollection)
            {
                output.UnRegisterSourceConnectorViewModel(connector);
                output.UnRegisterTargetConnectorViewModel(connector);
            }
        }

        public List<ConnectorViewModel> Connectors()
        {
            List<ConnectorViewModel> connectors = new List<ConnectorViewModel>();
            foreach(var input in this.InputCollection)
            {
                var inputConnectors = input.Connectors();
                foreach(var inputConnector in inputConnectors)
                {
                    connectors.Add(inputConnector);
                }
            }

            foreach (var output in this.OutputCollection)
            {
                var outputConnectors = output.Connectors();
                foreach (var outputConnector in outputConnectors)
                {
                    connectors.Add(outputConnector);
                }
            }

            return connectors;
        }


        public object Clone()
        {
            var node = new NodeViewModel()
            {
                X = this.X,
                Y = this.Y,
                IsEvent = this.IsEvent,
                IsSelected = this.IsSelected,
                Name = this.Name,
                Uid = this.Uid,

            };


            foreach(var input in this.InputCollection)
            {
                node.RegisterInputProperty((NodePropertyViewModel)input.Clone());
            }

            foreach(var output in this.OutputCollection)
            {
                node.RegisterOutputProperty((NodePropertyViewModel)output.Clone());
            }


            return node;
        }
        #endregion

    }
}
