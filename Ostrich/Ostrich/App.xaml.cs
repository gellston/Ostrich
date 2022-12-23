using DevExpress.XtraPrinting.Native;
using Microsoft.Extensions.DependencyInjection;
using Ostrich.Service;
using Ostrich.ViewModel;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Windows;

namespace Ostrich
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public App()
        {
            Services = ConfigureServices();




            this.InitializeComponent();
        
        }

        public IServiceProvider Services { get; }

        public new static App Current => (App)Application.Current;


        private static IServiceProvider ConfigureServices()
        {
            var services = new ServiceCollection();



            //Service
            services.AddSingleton<NodeEngineManagerService>();


            //ViewModel
            services.AddSingleton<MainWindowViewModel>();
            services.AddSingleton<CalculatorViewModel>();
            services.AddSingleton<MessageViewModel>();
            services.AddSingleton<ContextManageViewModel>();

            return services.BuildServiceProvider();
        }



    }





}
