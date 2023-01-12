using Model.Property;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Model
{
    public class PropertyModelConstructor
    {






        static public BasePropertyModel Create(string contextName, int objectType, ulong objectUid, ICommand modelChangedCommand)
        {
            try
            {

                switch(objectType)
                {
                    case 2:
                        return new ConstNumberModel()
                        {
                            ObjectType = objectType,
                            Uid = objectUid,
                            ModelChangingCommand = modelChangedCommand,
                            ContextName = contextName,
                        };
                        break;

                    case 3:
                        return new ConstImageNode()
                        {
                            ObjectType = objectType,
                            Uid = objectUid,
                            ModelChangingCommand = modelChangedCommand,
                            ContextName = contextName
                        };
                        break;
                    default:
                        return new BasePropertyModel()
                        {
                            ObjectType = objectType,
                            Uid = objectUid,
                            ModelChangingCommand = modelChangedCommand,
                            ContextName = contextName,
                        };
                        break;
                }

            }catch(Exception ex)
            {
                return new BasePropertyModel()
                {
                    ObjectType = objectType,
                    Uid = objectUid,
                    ModelChangingCommand = modelChangedCommand,
                    ContextName = contextName,
                };
            }
        }


    }

}
