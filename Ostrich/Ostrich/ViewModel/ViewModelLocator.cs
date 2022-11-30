using CommunityToolkit.Mvvm.ComponentModel;
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


        public ViewModelLocator()
        {



        }


        public ObservableObject MainWindowViewModel
        {
            get => App.Current.Services.GetService<MainWindowViewModel>();
        }
    }
}
