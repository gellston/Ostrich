using Model.EventParameter;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model.Property
{
    public class ConstNumberModel : BasePropertyModel, ICloneable
    {

        #region Private Property
        private double _Data = 0;
        #endregion

        #region Constructor
        public ConstNumberModel() { 

        }
        #endregion

        #region Public Property
        public double Data
        {
            get => _Data;
            set {

                var modelChangedArg = new ModelChangedArg()
                {
                    Data = value,
                    Changed = false,
                    ObjectType = this.ObjectType
                };


                try
                {
                    this.ModelChangingCommand.Execute(modelChangedArg);

                    if (modelChangedArg.Changed == true)
                    {
                        SetProperty(ref _Data, value);
                    }
                }
                catch(Exception e)
                {

                }

            }
        }

        public override object Clone()
        {
            return new ConstNumberModel(){
                Data = this.Data
            };

        }
        #endregion

    }
}
