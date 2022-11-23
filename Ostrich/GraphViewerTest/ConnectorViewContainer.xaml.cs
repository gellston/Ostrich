using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
    /// ConnectorViewContainer.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class ConnectorViewContainer : UserControl
    {
        public ConnectorViewContainer()
        {
            InitializeComponent();
        }
        public static readonly DependencyProperty ConnectorViewModelCollectionProperty = DependencyProperty.Register("ConnectorViewModelCollection", typeof(ObservableCollection<ViewModel.ConnectorViewModel>), typeof(ConnectorViewContainer));
        public ObservableCollection<ViewModel.ConnectorViewModel> ConnectorViewModelCollection
        {

            get => (ObservableCollection<ViewModel.ConnectorViewModel>)GetValue(ConnectorViewModelCollectionProperty);
            set => SetValue(ConnectorViewModelCollectionProperty, value);
        }
    }
}
