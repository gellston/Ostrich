using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewModel
{
    public class NodePropertyViewModel : ViewModelBase
    {

        #region Private Property
        private bool _IsOutput = false;
        private bool _IsExecution = false;
        private string _Name = "";
        private ulong _Uid = 0;
        private bool _IsPressed = false;
        private bool _IsConnected = false;
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
            get => _IsExecution;
            set => SetProperty(ref _IsExecution, value);
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
            get => _IsConnected;
            set => SetProperty(ref _IsConnected, value);
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

        public void RegisterSourceConnectorViewModel(ConnectorViewModel viewModel)
        {
            this._SourceConnectorCollection.Add(viewModel);
        }

        public void UnRegisterSourceConnectorViewModel(ConnectorViewModel viewModel)
        {
            this._SourceConnectorCollection.Remove(viewModel);
        }

        public void RegisterTargetConnectorViewModel(ConnectorViewModel viewModel)
        {
            this._TargetConnectorCollection.Add(viewModel);
        }

        public void UnRegisterTargetConnectorViewModel(ConnectorViewModel viewModel)
        {
            this._TargetConnectorCollection.Remove(viewModel);
        }


        #endregion
    }
}
