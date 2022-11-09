using CommunityToolkit.Mvvm.ComponentModel;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphViewerTest.ViewModel
{
    public class ContextViewModel : ObservableObject
    {


        #region PrivateProperty
        private string _Name = "";
        private string _NativeContext = "";
        #endregion

        public ContextViewModel() { 
        
            
        }

        #region PublicProperty
        public string Name
        {
            get => _Name;
            set => SetProperty(ref _Name, value);
        }

        public string NativeContext
        {
            get => _NativeContext;
            set => SetProperty(ref _NativeContext, value);
        }
        #endregion
    }
}
