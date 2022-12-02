using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using ViewModel;

namespace Ostrich.ViewModel
{
    public class MainWindowViewModel : ObservableObject
    {


        #region PrivateProperty
        private ContextViewModel _SelectedContextViewModel = null;
        #endregion


        #region Constructor

        public MainWindowViewModel() { 
        
        
        }
        #endregion



        #region Collection
        public ObservableCollection<ContextViewModel> ContextViewModelCollection { get; private set; } = new ObservableCollection<ContextViewModel>();
        #endregion



        #region Public Property
        public ContextViewModel SelectedContextViewModel
        {
            get => _SelectedContextViewModel;
            set => SetProperty(ref _SelectedContextViewModel, value);
        }
        #endregion



        #region Command

        public ICommand AddContextCommand
        {
            get => new RelayCommand(() =>
            {
                try
                {

                    var context = new ContextViewModel()
                    {
                        Name = "Test",
                        NativeContext = ""
                    };

                    this.ContextViewModelCollection.Add(context);

                }
                catch (Exception ex)
                {

                }
            });
        }

        public ICommand AddNodeCommand
        {
            get => new RelayCommand(() =>
            {
                try
                {

                    if(this.SelectedContextViewModel != null)
                    {
                        this.SelectedContextViewModel.NodeViewModelCollection.Add(new NodeViewModel()
                        {
                            Name = "test",
                            X = 100,
                            Y = 100
                        });
                    }
                }
                catch (Exception ex)
                {

                }
            });
        }
        #endregion

    }
}
