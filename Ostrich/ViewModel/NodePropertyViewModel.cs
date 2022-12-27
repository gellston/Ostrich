using Model.Property;
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
        private List<NodePathViewModel> _SourcePathCollection = new List<NodePathViewModel>();
        private List<NodePathViewModel> _TargetPathCollection = new List<NodePathViewModel>();
        private NodeViewModel _ParentNodeViewModel = null;


        private BasePropertyModel _PropertyModel = new BasePropertyModel();
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
                if (this.IsOutput == true && this._SourcePathCollection.Count > 0)
                    return true;
                else if (this.IsOutput == false && this._TargetPathCollection.Count > 0)
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

        public BasePropertyModel PropertyModel
        {
            get => _PropertyModel;
            set => SetProperty(ref _PropertyModel, value);
        }

        public double X
        {
            get => _X;
            set
            {
                SetProperty(ref _X, value);
                if (this.IsOutput == false)
                {
                    foreach (var viewModel in this._TargetPathCollection)
                    {
                        viewModel.TargetX = _X;
                    }
                }
                else
                {
                    foreach (var viewModel in this._SourcePathCollection)
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
                    foreach (var viewModel in this._TargetPathCollection)
                    {
                        viewModel.TargetY = _Y;
                    }
                }
                else
                {
                    foreach (var viewModel in this._SourcePathCollection)
                    {
                        viewModel.SourceY = _Y;
                    }
                }
            }
        }


        #endregion


        #region Functions


        public List<NodePathViewModel> Paths()
        {
            List<NodePathViewModel> paths = new List<NodePathViewModel>();

            foreach(var path in this._SourcePathCollection)
            {
                paths.Add(path);
            }

            foreach(var path in this._TargetPathCollection)
            {
                paths.Add(path);
            }

            return paths;
        }



        public void RegisterSourcePathViewModel(NodePathViewModel viewModel)
        {
            this._SourcePathCollection.Add(viewModel);
            this.RaisePropertyChanged("IsConnected");
        }

        public void UnRegisterSourcePathViewModel(NodePathViewModel viewModel)
        {
            this._SourcePathCollection.Remove(viewModel);
            this.RaisePropertyChanged("IsConnected");
        }

        public void RegisterTargetPathViewModel(NodePathViewModel viewModel)
        {
            this._TargetPathCollection.Add(viewModel);
            this.RaisePropertyChanged("IsConnected");
        }

        public void UnRegisterTargetPathViewModel(NodePathViewModel viewModel)
        {
            this._TargetPathCollection.Remove(viewModel);
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
                PropertyModel = this.PropertyModel
            };

            return property;
        }

        #endregion
    }
}
