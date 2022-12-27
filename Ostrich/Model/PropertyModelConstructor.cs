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






        static public BasePropertyModel Create(int objectType, ICommand modelChangedCommand)
        {
            try
            {

                switch(objectType)
                {
                    case 2:
                        return new ConstNumberModel()
                        {
                            ObjectType = objectType,
                            ModelChangingCommand = modelChangedCommand
                        };
                        break;


                    default:
                        return new BasePropertyModel()
                        {
                            ObjectType = objectType,
                            ModelChangingCommand = modelChangedCommand
                        };
                        break;
                }

            }catch(Exception ex)
            {
                return new BasePropertyModel()
                {
                    ObjectType = objectType,
                    ModelChangingCommand = modelChangedCommand
                };
            }
        }


    }

}
