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

        public MainWindowViewModel() { 
        
        
        }

        public ObservableCollection<NodeViewModel> NodeViewModelCollection { get; private set; } = new ObservableCollection<NodeViewModel>();

        public ObservableCollection<ConnectorViewModel> ConnectorViewModelCollection { get; private set; } = new ObservableCollection<ConnectorViewModel>();


        public ICommand TestCommand
        {
            get => new RelayCommand(() =>
            {
                try
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
                catch (Exception ex)
                {

                }
            });
        }

    }
}
