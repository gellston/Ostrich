using Model.EventParameter;
using Model.PropertyModelExtractCommand;
using Model.PropertyModelUpdateCommand;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public class PropertyModelExtracter
    {

        #region Private Property
        static Dictionary<int, BasePropertyModelExtractCommand> _command = new Dictionary<int, BasePropertyModelExtractCommand>();
        #endregion

        static PropertyModelExtracter() {
            _command.Add(2, new ConstNumberNodeExtractCommand());
        }


        static public object Extract(int objectType, IntPtr constNodePointer)
        {
            {
                if (_command.ContainsKey(objectType))
                {
                    return _command[objectType].Extract(constNodePointer);
                }
                else
                {
                    throw new Exception("Invalid property model type");
                }
            }
        }
    }
}
