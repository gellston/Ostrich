using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UC.EventParameter
{
    public class NodeConnectRequestArg : EventArgs
    {

        public string ContextName { get; set; } = "";

        public ulong SourceNodeUID { get; set; } = 0;
        public ulong SourcePropertyUID { get; set; } = 0;
        public string SourcePropertyName { get; set; } = "";


        public ulong TargetNodUID { get; set; } = 0;
        public ulong TargetPropertyUID { get; set; } = 0;
        public string TargetPropertyName { get; set; } = "";


        public bool ConnectComplete { get; set; } = false;
    }
}
