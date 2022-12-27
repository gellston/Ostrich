using Model.EventParameter;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.Cryptography.Xml;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Model.Property
{
    public class BasePropertyModel : INotifyPropertyChanged, ICloneable
    {

        #region Overrides INotifyPropertyChanged
        public event PropertyChangedEventHandler? PropertyChanged;
        public void RaisePropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion

        #region Private Property
        private ICommand _ModelChangingCommand = null;
        private int _ObjectType = 0;
        #endregion


        #region Constructor
        public BasePropertyModel()
        {
        }
        #endregion



        #region Model PropertyChanged

        protected virtual void ModelPropertyChanged(object sender, PropertyChangedEventArgs e)
        {

        }


        public ICommand ModelChangingCommand { 
            get => _ModelChangingCommand; 
            set => _ModelChangingCommand = value;
        }
        #endregion


        #region Public Property
        public int ObjectType
        {
            get => _ObjectType;
            set => SetProperty(ref _ObjectType, value);
        }
        #endregion



        #region Functions
        public void SetProperty<T>(ref T field, T value, [CallerMemberName] string propertyName = "")
        {
            field = value;
            this.RaisePropertyChanged(propertyName);
        }

        public virtual object Clone()
        {
            return new BasePropertyModel();
        }
        #endregion
    }
}
