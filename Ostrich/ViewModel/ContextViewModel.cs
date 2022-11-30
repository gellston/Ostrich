using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewModel
{
    public class ContextViewModel : ViewModelBase
    {

        #region PrivateProperty
        private string _Name = "";
        private string _NativeContext = "";
        #endregion



        #region Constructor
        public ContextViewModel() { 
        

        }

        #endregion



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
