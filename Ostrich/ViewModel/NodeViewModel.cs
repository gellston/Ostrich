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
        private ObservableCollection<NodePropertyViewModel> _InputCollection = new ObservableCollection<NodePropertyViewModel>();
        private ObservableCollection<NodePropertyViewModel> _OutputCollection = new ObservableCollection<NodePropertyViewModel>();
        #endregion


        #region Constructor
        public NodeViewModel() { 
            
        
        }
        #endregion


        #region Public Property
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
