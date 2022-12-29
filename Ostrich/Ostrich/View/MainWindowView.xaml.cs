using DevExpress.Xpf.Core;
using Microsoft.Extensions.DependencyInjection;
using Ostrich.Service;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Ostrich.View
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : ThemedWindow
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void view_Loaded(object sender, RoutedEventArgs e)
        {
            CompositionTarget.Rendering += CompositionTarget_Rendering; ;
            Window.GetWindow(this).Closing += (sender, e) =>
            {
                CompositionTarget.Rendering -= CompositionTarget_Rendering;
            };

        }

        private void CompositionTarget_Rendering(object sender, EventArgs e)
        {

            try
            {
                App.Current.Services.GetService<NodeEngineManagerService>().OnRendering();
            }
            catch(Exception ex)
            {
                System.Diagnostics.Debug.WriteLine(ex.Message);
            }

        }
    }
}
