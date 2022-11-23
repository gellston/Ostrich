﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ViewModel
{
    public class ConnectorViewModel : ViewModelBase
    {

        #region Private Property
        private ulong _SourceNodeUID = 0;
        private ulong _SourcePropertyUID = 0;
        private int _SourceType = 0;

        private ulong _TargetNodeUID = 0;
        private ulong _TargetPropertyUID = 0;
        private int _TargetType = 0;

        private string _Curve = "";

        private double _SourceX = 0;
        private double _SourceY = 0;

        private double _TargetX = 0;
        private double _TargetY = 0;

        #endregion


        #region Consturctor
        public ConnectorViewModel() { 

        }

        #endregion

        #region Public Property
        public string Curve
        {
            get => _Curve;
            set => SetProperty(ref _Curve, value);
        }

        public double SourceX
        {
            get => _SourceX;
            set
            {
                SetProperty(ref _SourceX, value);   
                ComputeCurve(SourceX, _SourceY, _TargetX, _TargetY);
            }
        }

        public double SourceY
        {
            get => _SourceY;
            set
            {
                SetProperty(ref _SourceY, value);
                ComputeCurve(SourceX, SourceY, TargetX, TargetY);
            }
        }

        public double TargetX
        {
            get => _TargetX;
            set
            {
                SetProperty(ref _TargetX, value);
                ComputeCurve(SourceX, SourceY, TargetX, TargetY);
            }
        }

        public double TargetY
        {
            get => _TargetY;
            set
            {
                SetProperty(ref _TargetY, value);
                ComputeCurve(SourceX, SourceY, TargetX, TargetY);
            }
        }

        public ulong SourceNodeUID
        {
            get => _SourceNodeUID;
            set => SetProperty(ref _SourceNodeUID, value);
        }

        public ulong SourcePropertyUID
        {
            get => _SourcePropertyUID;
            set => SetProperty(ref _SourcePropertyUID, value);
        }

        public int SourceType
        {
            get => _SourceType;
            set => SetProperty(ref _SourceType, value);
        }


        public ulong TargetNodeUID
        {
            get => _TargetNodeUID;
            set => SetProperty(ref _TargetNodeUID, value);
        }

        public ulong TargetPropertyUID
        {
            get => _TargetPropertyUID;
            set => SetProperty(ref _TargetPropertyUID, value);
        }

        public int TargetType
        {
            get => _TargetType;
            set => SetProperty(ref _TargetType, value);
        }
        #endregion

        #region Functions
        public void ComputeCurve(double sourceX, double sourceY, double targetX, double targetY)
        {
            Point start = new Point(sourceX, sourceY);
            Point end = new Point(targetX, targetY);
            Point center = new Point((start.X + end.X) * 0.5, (start.Y + end.Y) * 0.5);

            if (start.X > end.X)
            {
                Point temp = start;
                start = end;
                end = temp;
            }

            double ratio = Math.Min(1.0, (center.X - start.X) / 100.0);
            Point c0 = start;
            Point c1 = end;
            c0.X += 100 * ratio;
            c1.X -= 100 * ratio;

            var curveData = string.Format("M{0},{1} C{0},{1} {2},{3} {4},{5} " +
                                          "M{4},{5} C{4},{5} {6},{7} {8},{9}",
                                          (int)start.X, (int)start.Y, // 0, 1
                                          (int)c0.X, (int)c0.Y, // 2, 3
                                          (int)center.X, (int)center.Y, // 4, 5
                                          (int)c1.X, (int)c1.Y, // 6, 7
                                          (int)end.X, (int)end.Y); // 8.9

            this.Curve = curveData;
        }
        #endregion
    }
}
