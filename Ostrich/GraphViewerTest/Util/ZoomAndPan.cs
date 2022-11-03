using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace GraphViewerTest.Util
{
    public class ZoomAndPan
    {
        #region Properties

        private double _ViewWidth;
        public double ViewWidth
        {
            get { return _ViewWidth; }
            set
            {
                if (value != _ViewWidth)
                {
                    _ViewWidth = value;
                }
            }
        }

        private double _ViewHeight;
        public double ViewHeight
        {
            get { return _ViewHeight; }
            set
            {
                if (value != _ViewHeight)
                {
                    _ViewHeight = value;
                }
            }
        }

        private double _StartX = 0.0;
        public double StartX
        {
            get { return _StartX; }
            set
            {
                if (value != _StartX)
                {
                    _StartX = value;
                    _UpdateTransform();
                }
            }
        }

        private double _StartY = 0.0;
        public double StartY
        {
            get { return _StartY; }
            set
            {
                if (value != _StartY)
                {
                    _StartY = value;
                    _UpdateTransform();
                }
            }
        }

        private double _Scale = 1.0;
        public double Scale
        {
            get { return _Scale; }
            set
            {
                if (value != _Scale)
                {
                    _Scale = value;
                    _UpdateTransform();
                }
            }
        }

        private Matrix _Matrix = Matrix.Identity;
        public Matrix Matrix
        {
            get { return _Matrix; }
            set
            {
                if (value != _Matrix)
                {
                    _Matrix = value;
                    _MatrixInv = value;
                    _MatrixInv.Invert();
                }
            }
        }

        private Matrix _MatrixInv = Matrix.Identity;
        public Matrix MatrixInv
        {
            get { return _MatrixInv; }
        }


        #endregion // Properties

        #region Methdos

        private void _UpdateTransform()
        {
            Matrix newMatrix = Matrix.Identity;
            newMatrix.Scale(_Scale, _Scale);
            newMatrix.Translate(-_StartX, -_StartY);

            Matrix = newMatrix;

            UpdateTransform?.Invoke();
        }

        #endregion // Methods

        #region Events

        public delegate void UpdateTransformDelegate();
        public event UpdateTransformDelegate UpdateTransform;

        #endregion // Events
    }
}
