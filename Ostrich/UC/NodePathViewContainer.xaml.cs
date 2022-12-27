using DevExpress.XtraSpreadsheet.Import.OpenXml;
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
    /// ConnectorViewContainer.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class NodePathViewContainer : UserControl
    {


        #region Constructor
        public NodePathViewContainer()
        {
            InitializeComponent();
        }
        #endregion


        #region Dependecny Property

        public static readonly DependencyProperty NodePathViewModelCollectionProperty = DependencyProperty.Register("NodePathViewModelCollection", typeof(ObservableCollection<ViewModel.NodePathViewModel>), typeof(NodePathViewContainer));
        public ObservableCollection<ViewModel.NodePathViewModel> NodePathViewModelCollection
        {

            get => (ObservableCollection<ViewModel.NodePathViewModel>)GetValue(NodePathViewModelCollectionProperty);
            set => SetValue(NodePathViewModelCollectionProperty, value);
        }

        #endregion


    }
}
