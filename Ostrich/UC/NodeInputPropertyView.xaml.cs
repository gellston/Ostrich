using DevExpress.Xpf.Core.Native;
using System;
using System.Collections.Generic;
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
using ViewModel;

namespace UC
{
    /// <summary>
    /// NodeInputPropertyView.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class NodeInputPropertyView : UserControl
    {

        #region Private Property
        private bool loaded = false;
        #endregion


        #region Constructor

        public NodeInputPropertyView()
        {
            InitializeComponent();
        }

        #endregion




        #region Private Functions
        private void UserControl_LayoutUpdated(object sender, EventArgs e)
        {
            try
            {

                if (loaded == false && this.PART_Node_Spot.ActualHeight > 0 && this.PART_Node_Spot.ActualWidth > 0)
                {
                    var property = this.DataContext as NodePropertyViewModel;
                    property.ParentNodeViewModel.RaisePropertyChanged("X");
                    property.ParentNodeViewModel.RaisePropertyChanged("Y");
                    loaded = true;
                }

            }
            catch (Exception exception)
            {
                System.Diagnostics.Debug.WriteLine(exception.Message);
            }
        }
        #endregion
    }
}
