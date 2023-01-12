using Model.EventParameter;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace Model.Property
{
    public class ConstImageNode : BasePropertyModel, ICloneable
    {

        #region Private Property
        private WriteableBitmap _Image = null;
        #endregion

        #region Constructor
        public ConstImageNode()
        {

        }
        #endregion

        #region Public Property
        [JsonIgnore]
        [IgnoreDataMember]
        public WriteableBitmap Image
        {
            get => _Image;
            set
            {

                SetProperty(ref _Image, value);

            }
        }


        public override void Update(object data)
        {

            try
            {

                this.SetProperty(ref _Image, (WriteableBitmap)data);
                this.RaisePropertyChanged("Image");
            }
            catch (Exception e)
            {
                throw e;
            }

        }


        public override object Clone()
        {
            return new ConstImageNode()
            {
                ObjectType = this.ObjectType,
                ContextName = this.ContextName,
                ModelChangingCommand = this.ModelChangingCommand,
                Uid = this.Uid,
                Image = this.Image.Clone(),
            };

        }

        #endregion

    }
}
