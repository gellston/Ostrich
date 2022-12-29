using Model.EventParameter;
using Model.PropertyModelUpdateCommand;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace Model.PropertyModelUpdateCommand
{
    public class ConstNumberNodeUpdateCommand : BasePropertyModelUpdateCommand
    {

        public ConstNumberNodeUpdateCommand() { 
        
        }

        public void Update(ModelChangedArg argument, IntPtr constNodePointer)
        {
            try
            {
                var data = (double)argument.Data;
                HV.V2.Extension.PrimitiveNode.UpdateConstNumberNodeData(constNodePointer, data);

                System.Diagnostics.Debug.WriteLine("ConstNumberNodeCommand value update = " + data);
            }catch(Exception ex)
            {
                throw ex;
            }
        }
    }
}
