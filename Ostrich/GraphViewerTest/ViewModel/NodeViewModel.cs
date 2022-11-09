using CommunityToolkit.Mvvm.ComponentModel;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphViewerTest.ViewModel
{
    public class NodeViewModel : ObservableObject
    {

        #region PrivateProperty
        private bool _IsSelected = false;
        private double _X = 0;
        private double _Y = 0;
        private string _Name = "";
        private ObservableCollection<NodePropertyViewModel> _InputCollection = new ObservableCollection<NodePropertyViewModel>();
        private ObservableCollection<NodePropertyViewModel> _OutputCollection = new ObservableCollection<NodePropertyViewModel>();
        #endregion


        #region Constructor
        public NodeViewModel() {
            this._InputCollection.Add(new NodePropertyViewModel()
            {
                Name = "test",
                IsConnected = true,
            });
            this._OutputCollection.Add(new NodePropertyViewModel()
            {
                Name = "test"
            });
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
            set
            {
                if(_X != value)
                    SetProperty(ref _X, value);
            }
        }

        public double Y
        {
            get => _Y;
            set
            {
                if (_Y != value)
                    SetProperty(ref _Y, value);
            }
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
        }

        public ObservableCollection<NodePropertyViewModel> OutputCollection
        {
            get => _OutputCollection;
        }
        #endregion
    }
}
