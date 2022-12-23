using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ViewModel
{
    public class NodeInfoViewModel : ViewModelBase, ICloneable
    {


        #region Private Property
        private string _Name = "";
        private string _NodeName = "";
        private string _Category = "";
        private int _ObjectType = 0;
        #endregion


        #region Constructor
        public NodeInfoViewModel() { 
        
        }
        #endregion

        #region Public Property
        public string Name { 
            get => _Name; 
            set => SetProperty(ref _Name, value);
        }

        public string NodeName
        {
            get => _NodeName;
            set => SetProperty(ref _NodeName, value);
        }

        public string Category
        {
            get => _Category;
            set => SetProperty(ref _Category, value);
        }

        public int ObjectType
        {
            get => _ObjectType;
            set => SetProperty(ref _ObjectType, value);
        }

        public object Clone()
        {
            var nodeInfo = new NodeInfoViewModel()
            {
                Name = this.Name,
                NodeName = this.NodeName,
                Category = this.Category,
                ObjectType = this.ObjectType,
            };

            return nodeInfo;
        }
        #endregion

    }
}
