using System;
using System.Collections.ObjectModel;

namespace ViewModel
{
    public class NodeViewModel : ViewModelBase
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

            //Test Code
            this._InputCollection.Add(new NodePropertyViewModel()
            {
                Name = "Exec",
                IsConnected = false,
                IsOutput = false,
                IsExecution = true,
                ObjectType = 1,
                Uid = this.Uid,
                ParentNodeViewModel = this
            });
            this._InputCollection.Add(new NodePropertyViewModel()
            {
                Name = "Input",
                IsConnected = false,
                IsMultiple = true,
                IsExecution = false,
                IsOutput = false,
                ObjectType = 50001,
                Uid = this.Uid,
                ParentNodeViewModel = this
            });
            this._InputCollection.Add(new NodePropertyViewModel()
            {
                Name = "X",
                IsConnected = false,
                IsExecution = false,
                IsOutput = false,
                ObjectType = 50002,
                Uid = this.Uid,
                ParentNodeViewModel = this
            });

            this._OutputCollection.Add(new NodePropertyViewModel()
            {
                Name = "Exec",
                IsConnected = false,
                IsOutput = true,
                IsExecution = true,
                ObjectType = 1,
                Uid = this.Uid,
                ParentNodeViewModel = this
            });
            this._OutputCollection.Add(new NodePropertyViewModel()
            {
                Name = "Result",
                IsExecution = false,
                IsConnected = false,
                IsOutput = true,
                ObjectType = 50001,
                Uid = this.Uid,
                ParentNodeViewModel = this
            });
            this._OutputCollection.Add(new NodePropertyViewModel()
            {
                Name = "Y",
                IsExecution = false,
                IsConnected = false,
                IsOutput = true,
                ObjectType = 50002,
                Uid = this.Uid,
                ParentNodeViewModel = this
            });

            //Test Code

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

    }
}
