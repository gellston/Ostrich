using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.EventParameter
{
    public class ModelChangedArg : EventArgs
    {

        public int ObjectType { get; set; } = 0;

        public bool Changed { get; set; } = false;


        public object Data { get; set; } = null;
    }
}
