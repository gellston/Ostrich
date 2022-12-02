using System;
using System.Collections.ObjectModel;

namespace ViewModel
{
    public class NodeViewModel : ViewModelBase
    {

        #region Private Property
        private bool _IsSelected = false;
        private double _X = 0;
        private double _Y = 0;
        private string _Name = "";
        private ulong _Uid = 0;
        private ObservableCollection<NodePropertyViewModel> _InputCollection = new ObservableCollection<NodePropertyViewModel>();
        private ObservableCollection<NodePropertyViewModel> _OutputCollection = new ObservableCollection<NodePropertyViewModel>();
        #endregion


        #region Constructor
        public NodeViewModel() {
            this._InputCollection.Add(new NodePropertyViewModel()
            {
                Name = "test",
                IsConnected = false,
                IsOutput = false,
                ObjectType = 1,
                Uid = this.Uid,
                ParentNodeViewModel = this
            });
            this._OutputCollection.Add(new NodePropertyViewModel()
            {
                Name = "test",
                IsConnected = false,
                IsOutput = true,
                ObjectType = 1,
                Uid = this.Uid,
                ParentNodeViewModel = this
            });

        }
        #endregion


        #region Public Property

        public ulong Uid
        {
            get => _Uid;
            set => SetProperty(ref _Uid, value);
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

    }
}
