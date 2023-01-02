using CommunityToolkit.Mvvm.ComponentModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ViewModel;

namespace Ostrich.Model
{
    public class VisionDiagramFile
    {



        public VisionDiagramFile()
        {


        }


        public string Name { get; set; } = "";

        public string NativeContext { get; set; } = "";



        public List<NodePathViewModel> Paths { get; set; } = new List<NodePathViewModel>();

        public List<NodeViewModel> Nodes { get; set; } = new List<NodeViewModel>();

    }
}
