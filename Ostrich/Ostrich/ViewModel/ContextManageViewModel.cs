using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using DevExpress.Xpf.Gantt;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Ostrich.ViewModel
{
    public class ContextManageViewModel : ObservableObject
    {

        #region Private Property
        private string _ContextName = "";
        private ICommand _ConfirmCommand = null;
        private ICommand _CloseCommand = null;
        #endregion

        public ContextManageViewModel() { 
        
        }

        #region Public Property
        public string ContextName
        {
            get => _ContextName;
            set => SetProperty(ref _ContextName, value);
        }


        public ICommand ConfirmCommand
        {
            get => _ConfirmCommand;
            set => SetProperty(ref _ConfirmCommand, value);
        }
        public ICommand CloseCommand
        {
            get => _CloseCommand;
            set => SetProperty(ref _CloseCommand, value);
        }

        #endregion
    }
}
