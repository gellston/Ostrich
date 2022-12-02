using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewModel
{
    public class ContextViewModel : ViewModelBase
    {

        #region PrivateProperty
        private string _Name = "";
        private string _NativeContext = "";
        private ObservableCollection<NodeViewModel> _NodeViewModelCollection = new ObservableCollection<NodeViewModel>();
        private ObservableCollection<ConnectorViewModel> _ConnectorViewModelCollection = new ObservableCollection<ConnectorViewModel>();
        #endregion



        #region Constructor
        public ContextViewModel() { 
        

        }

        #endregion



        #region PublicProperty
        public string Name
        {
            get => _Name;
            set => SetProperty(ref _Name, value);
        }

        public string NativeContext
        {
            get => _NativeContext;
            set => SetProperty(ref _NativeContext, value);  
        }

        public ObservableCollection<ConnectorViewModel> ConnectorViewModelCollection
        {
            get => _ConnectorViewModelCollection;
            set => SetProperty(ref _ConnectorViewModelCollection, value);
        }

        public ObservableCollection<NodeViewModel> NodeViewModelCollection
        {
            get => _NodeViewModelCollection;
            set => SetProperty(ref _NodeViewModelCollection, value);
        }
        #endregion
    }
}
