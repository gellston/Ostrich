using CommunityToolkit.Mvvm.ComponentModel;
using DevExpress.Data;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ostrich.ViewModel
{
    public class ViewModelLocator
    {

        #region Constructor
        public ViewModelLocator()
        {



        }
        #endregion



        #region Public Property

        public ObservableObject MainWindowViewModel
        {
            get => App.Current.Services.GetService<MainWindowViewModel>();
        }



        public ObservableObject CalculatorViewModel
        {
            get => App.Current.Services.GetService<CalculatorViewModel>();
        }

        public ObservableObject MessageViewModel
        {
            get => App.Current.Services.GetService<MessageViewModel>();
        }
        #endregion
    }
}
