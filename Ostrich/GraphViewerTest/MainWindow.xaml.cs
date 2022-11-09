using GraphViewerTest.ViewModel;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace GraphViewerTest
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        #region Overrides InotifyPropertyChanged

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion // Overrides INotifyPropertyChanged

        public MainWindow()
        {
            InitializeComponent();


        }

        public ObservableCollection<NodeViewModel> NodeViewModelCollection { get; private set; } = new ObservableCollection<NodeViewModel>();

        private void view_Loaded(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {

            this.NodeViewModelCollection.Add(new NodeViewModel()
            {
                X = 100,
                Y = 100,
                IsSelected = false,
                Name = "test",
            });
        }
    }
}
