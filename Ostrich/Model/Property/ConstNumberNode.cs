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
                    ObjectType = this.ObjectType,
                    Uid = this.Uid,
                    ContextName = this.ContextName
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


        public override void Update(object data)
        {

            try
            {
                this.SetProperty(ref _Data, (double)data);
                this.RaisePropertyChanged("Data");
            }
            catch(Exception e)
            {
                throw e;
            }

        }


        public override object Clone()
        {
            return new ConstNumberModel(){
                ObjectType = this.ObjectType,
                ContextName = this.ContextName,
                ModelChangingCommand = this.ModelChangingCommand,
                Uid = this.Uid,
                Data = this.Data,
            };

        }

        #endregion

    }
}
