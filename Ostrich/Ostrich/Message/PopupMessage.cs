using DevExpress.Xpf.Core.DragAndDrop.TypedStyles;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ostrich.Message
{
    public class PopupMessage
    {


        #region Constructor
        public PopupMessage() {
            this.IsClose = false;
        
        }
        #endregion



        #region Public Property

        public bool IsClose
        {
            get;set;
        }

        public int MessageWidth { get; set; } = 200;
        public int MessageHeight { get; set; } = 200;
        #endregion


        #region Message Content
        public object Content
        {
            get;set;
        }
        #endregion






    }
}
