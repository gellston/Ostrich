using Model.EventParameter;
using Model.PropertyModelExtractCommand;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace Model.PropertyModelExtractCommand
{
    public class ConstNumberNodeExtractCommand : BasePropertyModelExtractCommand
    {

        public ConstNumberNodeExtractCommand()
        {

        }

        public object Extract(IntPtr constNodePointer)
        {
            try
            {
                return HV.V2.Extension.PrimitiveNode.FindConstNumberNodeData(constNodePointer);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
}
