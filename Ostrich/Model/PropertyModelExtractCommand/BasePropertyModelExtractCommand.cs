using Model.EventParameter;
using Model.Property;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Model.PropertyModelExtractCommand
{
    public interface BasePropertyModelExtractCommand
    {


        #region Consturctor

        #endregion



        #region Public Property

        public object Extract(IntPtr constNodePointer);
        #endregion


    }
}
