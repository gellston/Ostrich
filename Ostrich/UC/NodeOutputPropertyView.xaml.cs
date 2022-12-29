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
    /// NodeOutputPropertyView.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class NodeOutputPropertyView : UserControl
    {
        #region Private Property
        private bool loaded = false;
        private double _ActualHeight = -1;
        private double _ActualWidth = -1;
        #endregion



        #region Constructor

        public NodeOutputPropertyView()
        {
            InitializeComponent();
        }
        #endregion



        #region Private Property
        private void UserControl_LayoutUpdated(object sender, EventArgs e)
        {
            try
            {

                if (this.ActualHeight != this._ActualHeight && this.ActualWidth != this._ActualWidth)
                {
                    var property = this.DataContext as NodePropertyViewModel;
                    property.ParentNodeViewModel.RaisePropertyChanged("X");
                    property.ParentNodeViewModel.RaisePropertyChanged("Y");

                    this._ActualHeight = this.ActualHeight;
                    this._ActualWidth = this.ActualWidth;
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
