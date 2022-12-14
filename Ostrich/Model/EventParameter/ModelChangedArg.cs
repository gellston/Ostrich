using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.EventParameter
{
    public class ModelChangedArg : EventArgs
    {


        public ulong Uid { get; set; } = 0;
        public int ObjectType { get; set; } = 0;

        public bool Changed { get; set; } = false;

        public string ContextName { get; set; } = "";


        public object Data { get; set; } = null;
    }
}
