using Model.EventParameter;
using Model.PropertyModelUpdateCommand;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public class PropertyModelUpdater
    {

        #region Private Property
        static Dictionary<int, BasePropertyModelUpdateCommand> _command = new Dictionary<int, BasePropertyModelUpdateCommand>();
        #endregion

        static PropertyModelUpdater() {


            _command.Add(2, new ConstNumberNodeUpdateCommand());
        }


        static public void Update(int objectType, ModelChangedArg argument, IntPtr constNodePointer)
        {
            if (_command.ContainsKey(objectType))
            {
                _command[objectType].Update(argument, constNodePointer);
            }
            else
            {
                throw new Exception("Invalid property model type");
            }
        }
    }
}
