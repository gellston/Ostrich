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

        public ObservableCollection<ConnectorViewModel> ConnectorViewModelCollection { get; private set; } = new ObservableCollection<ConnectorViewModel>();

        private void view_Loaded(object sender, RoutedEventArgs e)
        {

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var source = new NodeViewModel()
            {
                X = 100,
                Y = 100,
                IsSelected = false,
                Name = "test",
            };

            var target = new NodeViewModel()
            {
                X = 200,
                Y = 100,
                IsSelected = false,
                Name = "test",
            };

            var target2 = new NodeViewModel()
            {
                X = 200,
                Y = 100,
                IsSelected = false,
                Name = "test",
            };


            this.NodeViewModelCollection.Add(source);
            this.NodeViewModelCollection.Add(target);
            this.NodeViewModelCollection.Add(target2);

            var connector = new ConnectorViewModel();
            var connector2 = new ConnectorViewModel();

            source.OutputCollection[0].RegisterSourceConnectorViewModel(connector);
            target.InputCollection[0].RegisterTargetConnectorViewModel(connector);

            source.OutputCollection[0].RegisterSourceConnectorViewModel(connector2);
            target2.InputCollection[0].RegisterTargetConnectorViewModel(connector2);

            this.ConnectorViewModelCollection.Add(connector);
            this.ConnectorViewModelCollection.Add(connector2);

        }
    }
}
