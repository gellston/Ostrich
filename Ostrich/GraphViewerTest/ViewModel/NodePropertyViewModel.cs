using CommunityToolkit.Mvvm.ComponentModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.RightsManagement;
using System.Text;
using System.Threading.Tasks;

namespace GraphViewerTest.ViewModel
{
    public class NodePropertyViewModel : ObservableObject
    {

        #region PrivateProperty
        private bool _IsOutput = false;
        private bool _IsExecution = false;
        private string _Name = "";
        private ulong _Uid = 0;
        private bool _IsPressed = false;
        private bool _IsConnected = false;
        private int _ObjectType = -1;
        #endregion


        #region Constructor
        public NodePropertyViewModel()
        {

        }
        #endregion


        #region PublicProperty
        public string Name
        {
            get => _Name;
            set => SetProperty(ref _Name, value);
        }

        public bool IsExecution
        {
            get => _IsExecution;
            set => SetProperty(ref _IsExecution, value);
        }

        public bool IsOutput
        {
            get => _IsOutput;
            set => SetProperty(ref _IsOutput, value);
        }

        public bool IsPressed
        {
            get => _IsPressed;
            set => SetProperty(ref _IsPressed, value);
        }

        public bool IsConnected
        {
            get => _IsConnected;
            set => SetProperty(ref _IsConnected, value);
        }


        public ulong Uid
        {
            get => _Uid;
            set => SetProperty(ref _Uid, value);
        }


        public int ObjectType
        {
            get => _ObjectType;
            set => SetProperty(ref _ObjectType, value);
        }
        #endregion
    }
}
