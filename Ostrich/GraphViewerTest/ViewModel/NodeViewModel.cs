using CommunityToolkit.Mvvm.ComponentModel;
using System;
using System.Collections.Generic;
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


        #endregion
    }
}
