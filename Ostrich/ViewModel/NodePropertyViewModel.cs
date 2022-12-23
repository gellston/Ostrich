using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewModel
{
    public class NodePropertyViewModel : ViewModelBase, ICloneable
    {

        #region Private Property
        private bool _IsOutput = false;
        private string _Name = "";
        private ulong _Uid = 0;
        private bool _IsPressed = false;
        private int _ObjectType = -1;
        private bool _IsMultiple = false;
        private double _X = 0;
        private double _Y = 0;
        private List<ConnectorViewModel> _SourceConnectorCollection = new List<ConnectorViewModel>();
        private List<ConnectorViewModel> _TargetConnectorCollection = new List<ConnectorViewModel>();
        private NodeViewModel _ParentNodeViewModel = null;
        #endregion


        #region Constructor
        public NodePropertyViewModel() { 
        
        }
        #endregion


        #region PublicProperty
        public string Name
        {
            get => _Name;
            set => SetProperty(ref _Name, value);
        }


        public bool IsExecution
        {
            get
            {
                if(this.ObjectType == 1)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        public bool IsOutput
        {
            get => _IsOutput;
            set => SetProperty(ref _IsOutput, value);
        }

        public bool IsPressed
        {
            get => _IsPressed;
            set => SetProperty(ref _IsPressed, value);
        }

        public bool IsConnected
        {
            get
            {
                if (this.IsOutput == true && this._SourceConnectorCollection.Count > 0)
                    return true;
                else if (this.IsOutput == false && this._TargetConnectorCollection.Count > 0)
                    return true;
                else return false;

            }
        }

        public bool IsMultiple
        {
            get => _IsMultiple;
            set => SetProperty(ref _IsMultiple, value);
        }


        public ulong Uid
        {
            get => _Uid;
            set => SetProperty(ref _Uid, value);
        }


        public int ObjectType
        {
            get => _ObjectType;
            set => SetProperty(ref _ObjectType, value);
        }

        public NodeViewModel ParentNodeViewModel
        {
            get => _ParentNodeViewModel;
            set => SetProperty(ref _ParentNodeViewModel, value);
        }


        public double X
        {
            get => _X;
            set
            {
                SetProperty(ref _X, value);
                if (this.IsOutput == false)
                {
                    foreach (var viewModel in this._TargetConnectorCollection)
                    {
                        viewModel.TargetX = _X;
                    }
                }
                else
                {
                    foreach (var viewModel in this._SourceConnectorCollection)
                    {
                        viewModel.SourceX = _X;
                    }
                }
            }
        }

        public double Y
        {
            get => _Y;
            set
            {
                SetProperty(ref _Y, value);
                if (this.IsOutput == false)
                {
                    foreach (var viewModel in this._TargetConnectorCollection)
                    {
                        viewModel.TargetY = _Y;
                    }
                }
                else
                {
                    foreach (var viewModel in this._SourceConnectorCollection)
                    {
                        viewModel.SourceY = _Y;
                    }
                }
            }
        }


        #endregion


        #region Functions


        public List<ConnectorViewModel> Connectors()
        {
            List<ConnectorViewModel> connectors = new List<ConnectorViewModel>();

            foreach(var connnector in this._SourceConnectorCollection)
            {
                connectors.Add(connnector);
            }

            foreach(var connector in this._TargetConnectorCollection)
            {
                connectors.Add(connector);
            }

            return connectors;
        }



        public void RegisterSourceConnectorViewModel(ConnectorViewModel viewModel)
        {
            this._SourceConnectorCollection.Add(viewModel);
            this.RaisePropertyChanged("IsConnected");
        }

        public void UnRegisterSourceConnectorViewModel(ConnectorViewModel viewModel)
        {
            this._SourceConnectorCollection.Remove(viewModel);
            this.RaisePropertyChanged("IsConnected");
        }

        public void RegisterTargetConnectorViewModel(ConnectorViewModel viewModel)
        {
            this._TargetConnectorCollection.Add(viewModel);
            this.RaisePropertyChanged("IsConnected");
        }

        public void UnRegisterTargetConnectorViewModel(ConnectorViewModel viewModel)
        {
            this._TargetConnectorCollection.Remove(viewModel);
            this.RaisePropertyChanged("IsConnected");
        }

        public object Clone()
        {
            var property = new NodePropertyViewModel()
            {
                IsMultiple = this.IsMultiple,
                IsOutput = this.IsOutput,
                IsPressed = this.IsPressed,
                X = this.X,
                Y = this.Y,
                Name = this.Name,
                ObjectType = this.ObjectType,
                Uid = this.Uid,
            };

            return property;
        }

        #endregion
    }
}
