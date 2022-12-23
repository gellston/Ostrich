using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewModel
{
    public class AddonViewModel : ViewModelBase, ICloneable
    {

        #region Private Property
        private string _Name = "";
        private string _Version = "";
        #endregion

        #region Constructor

        public AddonViewModel() { 
            
        }
        #endregion

        #region Public Property
        public string Name
        {
            get => _Name;
            set => SetProperty(ref _Name, value);
        }

        public string Version
        {
            get => _Version;
            set => SetProperty(ref _Version, value);
        }

        public object Clone()
        {
            var addon = new AddonViewModel()
            {
                Name = this.Name,
                Version = this.Version
            };

            return addon;
        }




        #endregion
    }
}
