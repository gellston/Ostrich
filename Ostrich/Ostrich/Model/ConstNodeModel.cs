using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ostrich.Model
{
    public class ConstNodeModel
    {

        public ConstNodeModel() { }


        public string ContextName { get; set; } = "";

        public int ObjectType { get; set; } = 0;


        public ulong Uid { get; set; } = 0;

        public object Data { get; set; } = null;



    }
}
