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
    /// NodeView.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class NodeView : UserControl
    {

        #region Constructor
        public NodeView()
        {
            InitializeComponent();
        }
        #endregion

        #region DependencyProperty
        public static readonly DependencyProperty IsSelectedProperty = DependencyProperty.Register("IsSelected", typeof(bool), typeof(NodeView), new PropertyMetadata(false));
        public bool IsSelected
        {
            set => SetValue(IsSelectedProperty, value);
            get => (bool)GetValue(IsSelectedProperty);
        }

        public static readonly DependencyProperty HasConnectionProperty = DependencyProperty.Register("HasConnection", typeof(bool), typeof(NodeView), new PropertyMetadata(false));
        public bool HasConnection
        {
            set => SetValue(HasConnectionProperty, value);
            get => (bool)GetValue(HasConnectionProperty);
        }

        public static readonly DependencyProperty SelectionThicknessProperty = DependencyProperty.Register("SelectionThickness", typeof(Thickness), typeof(NodeView), new PropertyMetadata(new Thickness(2.0)));
        public Thickness SelectionThickness
        {
            set => SetValue(SelectionThicknessProperty, value);
            get => (Thickness)GetValue(SelectionThicknessProperty);
        }

        public static readonly DependencyProperty CornerRadiusProperty = DependencyProperty.Register("CornerRadius", typeof(double), typeof(NodeView), new PropertyMetadata(8.0));
        public double CornerRadius
        {
            set => SetValue(CornerRadiusProperty, value);
            get => (double)GetValue(CornerRadiusProperty);
        }


        public static readonly DependencyProperty BorderSelectionColorProperty = DependencyProperty.Register("BorderSelectionColor", typeof(SolidColorBrush), typeof(NodeView), new PropertyMetadata(new SolidColorBrush((Color)ColorConverter.ConvertFromString("#121212"))));
        public SolidColorBrush BorderSelectionColor
        {
            set => SetValue(BorderSelectionColorProperty, value);
            get => (SolidColorBrush)GetValue(BorderSelectionColorProperty);
        }


        #endregion
    }
}
