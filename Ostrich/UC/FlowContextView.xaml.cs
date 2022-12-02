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
    /// FlowContextView.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class FlowContextView : UserControl
    {
        public FlowContextView()
        {
            InitializeComponent();
        }


        public static readonly DependencyProperty ContextViewModelCollectionProperty = DependencyProperty.Register("ContextViewModelCollection", typeof(ObservableCollection<ViewModel.ContextViewModel>), typeof(FlowContextView));
        public ObservableCollection<ViewModel.ContextViewModel> ContextViewModelCollection
        {
            get
            {
                return (ObservableCollection<ViewModel.ContextViewModel>)GetValue(ContextViewModelCollectionProperty);
            }

            set
            {
                SetValue(ContextViewModelCollectionProperty, value);
            }
        }


        public static readonly DependencyProperty SelectedContextViewModelProperty = DependencyProperty.Register("SelectedContextViewModel", typeof(ViewModel.ContextViewModel), typeof(FlowContextView));
        public ViewModel.ContextViewModel SelectedContextViewModel
        {
            get
            {
                return (ViewModel.ContextViewModel)GetValue(SelectedContextViewModelProperty);
            }

            set
            {
                SetValue(SelectedContextViewModelProperty, value);
            }
        }


        public static readonly DependencyProperty ContextCloseCommandProperty = DependencyProperty.Register("ContextCloseCommand", typeof(ICommand), typeof(FlowContextView));
        public ICommand ContextCloseCommand
        {
            get
            {
                return (ICommand)GetValue(ContextCloseCommandProperty);
            }

            set
            {
                SetValue(ContextCloseCommandProperty, value);
            }
        }





    }
}
