using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace ViewModel
{
    public class ViewModelBase : INotifyPropertyChanged
    {

        #region Overrides INotifyPropertyChanged
        public event PropertyChangedEventHandler? PropertyChanged;
        public void RaisePropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion


        #region Constructor
        public ViewModelBase() { 
        
        }
        #endregion


        #region Model PropertyChanged

        protected virtual void ModelPropertyChanged(object sender, PropertyChangedEventArgs e)
        {

        }

        #endregion


        #region Functions
        public void SetProperty<T>(ref T field, T value, [CallerMemberName] string propertyName = "")
        {
            field = value;
            this.RaisePropertyChanged(propertyName);
        }
        #endregion
    }
}
