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
        private bool _IsExecuting = false;
        private bool _HasError = false;
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

        public bool HasError
        {
            get => _HasError;
            set => SetProperty(ref _HasError, value);
        }

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

        public bool IsExecuting
        {
            get => _IsExecuting;
            set => SetProperty(ref _IsExecuting, value);
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


        public void UnRegisterPath(List<NodePathViewModel> paths)
        {
            foreach(var path in paths)
            {
                this.UnRegisterPath(path);
            }
        }

        public void UnRegisterPath(NodePathViewModel path)
        {
            foreach (var input in this.InputCollection)
            {
                input.UnRegisterSourcePathViewModel(path);
                input.UnRegisterTargetPathViewModel(path);
            }

            foreach (var output in this.OutputCollection)
            {
                output.UnRegisterSourcePathViewModel(path);
                output.UnRegisterTargetPathViewModel(path);
            }
        }


        public List<NodePathViewModel> Paths()
        {
            List<NodePathViewModel> paths = new List<NodePathViewModel>();
            foreach(var input in this.InputCollection)
            {
                var inputPaths = input.Paths();
                foreach(var inputPath in inputPaths)
                {
                    paths.Add(inputPath);
                }
            }

            foreach (var output in this.OutputCollection)
            {
                var outputPaths = output.Paths();
                foreach (var outputPath in outputPaths)
                {
                    paths.Add(outputPath);
                }
            }

            return paths;
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
