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

namespace UC
{
    /// <summary>
    /// NodeViewsContainer.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class NodeViewsContainer : UserControl
    {


        #region Constructor
        public NodeViewsContainer()
        {
            InitializeComponent();
        }
        #endregion

        #region DependencyObjects
        public static readonly DependencyProperty NodeViewModelCollectionProperty = DependencyProperty.Register("NodeViewModelCollection", typeof(ObservableCollection<ViewModel.NodeViewModel>), typeof(NodeViewsContainer));
        public ObservableCollection<ViewModel.NodeViewModel> NodeViewModelCollection
        {

            get => (ObservableCollection<ViewModel.NodeViewModel>)GetValue(NodeViewModelCollectionProperty);
            set => SetValue(NodeViewModelCollectionProperty, value);
        }
        #endregion
    }
}
