using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Ostrich.Model
{
    public class Addon
    {

        public Addon()
        {

        }


        public string Name { get; set; } = "";

        public ObservableCollection<ulong> ObjectTypeCollection { get; set; } = new ObservableCollection<ulong>();

    }
}
