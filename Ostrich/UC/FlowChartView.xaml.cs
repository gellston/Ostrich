﻿using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml.Linq;
using UC.Util;
using ViewModel;

namespace UC
{
    /// <summary>
    /// FlowChartView.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class FlowChartView : UserControl, INotifyPropertyChanged
    {

        #region Overrides INotifyPropertyChanged
        public event PropertyChangedEventHandler? PropertyChanged;
        public void RaisePropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public void SetProperty<T>(ref T field, T value, [CallerMemberName] string propertyName = "")
        {
            field = value;
            this.RaisePropertyChanged(propertyName);
        }

        #endregion


        #region Property
        private ZoomAndPan _ZoomAndPan = new ZoomAndPan();
        public ZoomAndPan ZoomAndPan
        {
            get { return _ZoomAndPan; }
        }

        protected FrameworkElement? _NodeCanvas = null;
        public FrameworkElement? NodeCanvas
        {
            get { return _NodeCanvas; }
        }

        protected FrameworkElement? _ConnectorCanvas = null;
        public FrameworkElement? ConnectorCanvas
        {
            get { return _ConnectorCanvas; }
        }


        protected FrameworkElement? _ConnectorPreviewCanvas = null;
        public FrameworkElement? ConnectorPreviewCanvas
        {
            get { return _ConnectorPreviewCanvas; }
        }


        public string PreviewCurve
        {
            get => _PreviewCurve;
            set => SetProperty(ref _PreviewCurve, value);
        }

        public double PreviewCurveStartX
        {
            get => _PreviewCurveStartX;
            set => SetProperty(ref _PreviewCurveStartX, value);
        }

        public double PreviewCurveStartY
        {
            get => _PreviewCurveStartY;
            set => SetProperty(ref _PreviewCurveStartY, value);
        }

        public double PreviewCurveEndX
        {
            get => _PreviewCurveEndX;
            set => SetProperty(ref _PreviewCurveEndX, value);
        }

        public double PreviewCurveEndY
        {
            get => _PreviewCurveEndY;
            set => SetProperty(ref _PreviewCurveEndY, value);
        }




        private string _PreviewCurve = "";

        protected Point _RightButtonDownPos;
        protected Point _LeftButtonDownPos;
        protected Point _PrevMousePosOnCanvas;

        protected Point _SelectionCanvasStartPos;
        protected Point _SelectionCanvasEndPose;

        protected bool _IsDraggingCanvas;
        protected bool _IsNodeDragging;
        protected bool _IsNodePropertyDragging;
        protected bool _IsDragSelectionStart = false;
        private Matrix _ZoomAndPanStartMatrix;
        private NodePropertyViewModel _SelectedNodePropertyViewModel = null;


        private double _PreviewCurveStartX = 0;
        private double _PreviewCurveStartY = 0;
        private double _PreviewCurveEndX = 0;
        private double _PreviewCurveEndY = 0;

        private bool PreviewCurveStart2End = false;
        private bool PreviewCurveEnd2Start = false;

        #endregion


        #region Constructor
        public FlowChartView()
        {
            InitializeComponent();
        }
        #endregion



        #region Functions


        private void ComputeCurve()
        {
            Point start = new Point(this.PreviewCurveStartX, this.PreviewCurveStartY);
            Point end = new Point(this.PreviewCurveEndX, this.PreviewCurveEndY);
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

            this.PreviewCurve = curveData;
        }


        private void FlowChartViewControl_DataContextChanged(object sender, DependencyPropertyChangedEventArgs e)
        {

        }

        private void FlowChartViewControl_Loaded(object sender, RoutedEventArgs e)
        {
            if (this._NodeCanvas == null)
            {
                this._NodeCanvas = ViewUtil.FindChild<Canvas>(this.PART_NodeViewContainer);
            }

            if (this._ConnectorCanvas == null)
            {
                this._ConnectorCanvas = ViewUtil.FindChild<Canvas>(this.PART_ConnectorViewContainer);
            }



            this._ZoomAndPan.UpdateTransform += _ZoomAndPan_UpdateTransform;
        }

        private void _ZoomAndPan_UpdateTransform()
        {
            if (this._NodeCanvas != null)
                this._NodeCanvas.RenderTransform = new MatrixTransform(this._ZoomAndPan.Matrix);

            if (this._ConnectorCanvas != null)
                this._ConnectorCanvas.RenderTransform = new MatrixTransform(this._ZoomAndPan.Matrix);

            if(this.PART_ConnectorPreviewCanvas != null)
                this.PART_ConnectorPreviewCanvas.RenderTransform = new MatrixTransform(this._ZoomAndPan.Matrix);
        }


        protected override void OnMouseWheel(MouseWheelEventArgs e)
        {
            base.OnMouseWheel(e);

            double newScale = this._ZoomAndPan.Scale;
            newScale += (0.0 > e.Delta) ? -0.05 : 0.05;
            newScale = Math.Max(0.1, Math.Min(1.0, newScale));

            Point vsZoomCenter = e.GetPosition(this);
            Point zoomCenter = this._ZoomAndPan.MatrixInv.Transform(vsZoomCenter);

            this._ZoomAndPan.Scale = newScale;

            Point vsNextZoomCenter = this._ZoomAndPan.Matrix.Transform(zoomCenter);
            Point vsDelta = new Point(vsZoomCenter.X - vsNextZoomCenter.X, vsZoomCenter.Y - vsNextZoomCenter.Y);

            this._ZoomAndPan.StartX -= vsDelta.X;
            this._ZoomAndPan.StartY -= vsDelta.Y;
        }


        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);

            Keyboard.Focus(this);


            var mousePosition = Mouse.GetPosition(this);
            var clickedItem = this.InputHitTest(mousePosition) as FrameworkElement;
            if (clickedItem != null && clickedItem.DataContext != this.DataContext)
            {
                if (clickedItem.DataContext.GetType() == typeof(NodeViewModel))
                {

                    var nodeViewModel = clickedItem.DataContext as NodeViewModel;
                    Mouse.Capture(this, CaptureMode.SubTree);//?????????????????


                    //그룹선택하여 이동시에 선택이 해제되지 않도록 
                    if (Keyboard.IsKeyDown(Key.LeftShift) == false)
                    {
                        //DeSelection
                        foreach (var node in this.NodeViewModelCollection)
                        {

                            node.IsSelected = false;
                        }
                        //DeSelection
                    }

                    this._IsNodeDragging = true;

                    //Selection Activation;
                    nodeViewModel.IsSelected = true;
                }


                if (clickedItem.DataContext.GetType() == typeof(NodePropertyViewModel))
                {
                    var property = clickedItem.DataContext as NodePropertyViewModel;
                    property.IsPressed = true;
                    Mouse.Capture(this, CaptureMode.SubTree);//?????????????????

                    this._SelectedNodePropertyViewModel = property;
                    this._IsNodePropertyDragging = true;


                    if(property.IsConnected == false)
                    {
                        if(property.IsOutput == true)
                        {
                            this.PreviewCurveStartX = property.X;
                            this.PreviewCurveStartY = property.Y;
                            this.PreviewCurveEndX = property.X;
                            this.PreviewCurveEndY = property.Y;
                            this.PreviewCurveStart2End = true;
                            this.PreviewCurveEnd2Start = false;
                            this.ComputeCurve();
                            this.ConnectorVisibility = Visibility.Visible;
                        }
                        else
                        {
                            this.PreviewCurveStartX = property.X;
                            this.PreviewCurveStartY = property.Y;
                            this.PreviewCurveEndX = property.X;
                            this.PreviewCurveEndY = property.Y;
                            this.PreviewCurveStart2End = false;
                            this.PreviewCurveEnd2Start = true;
                            this.ComputeCurve();
                            this.ConnectorVisibility = Visibility.Visible;
                        }
                    }
                }

            
            }
            else
            {

                //DeSelection
                foreach (var node in this.NodeViewModelCollection)
                {
                    node.IsSelected = false;
                }
                //DeSelection

                //Selection Start 
                if (Keyboard.IsKeyDown(Key.LeftShift))
                {
                    this._IsDragSelectionStart = true;
                    Point mousePos = e.GetPosition(this.PART_DragAndSelectionCanvas);
                    this.SelectionStartX = mousePos.X;
                    this.SelectionStartY = mousePos.Y;
                    this.SelectionVisibility = Visibility.Visible;

                    this._SelectionCanvasStartPos = e.GetPosition(this.NodeCanvas);
                }
            }




        }

        protected override void OnMouseLeftButtonUp(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonUp(e);

            if (this._IsNodeDragging == true)
            {
                this._IsNodeDragging = false;
                Mouse.Capture(null);
            }

            if (this._IsNodePropertyDragging == true)
            {
                if (this._SelectedNodePropertyViewModel != null)
                {
                    this._SelectedNodePropertyViewModel.IsPressed = false;

                    //Final Connection 
                    //Final Connection 
                    var mousePosition = Mouse.GetPosition(this);
                    var clickedItem = this.InputHitTest(mousePosition) as FrameworkElement;
                    if (clickedItem != null && clickedItem.DataContext != this.DataContext)
                    {
                        if (clickedItem.DataContext.GetType() == typeof(NodePropertyViewModel) && 
                            this._SelectedNodePropertyViewModel != clickedItem.DataContext &&
                            this._SelectedNodePropertyViewModel.IsOutput != ((NodePropertyViewModel)clickedItem.DataContext).IsOutput)
                        {
                            var targetNodePropertyViewModel = clickedItem.DataContext as NodePropertyViewModel;

                            if (this.PreviewCurveStart2End == true && 
                                targetNodePropertyViewModel.IsConnected == false)
                            {

                                var connector = new ConnectorViewModel()
                                {
                                    SourceNodeUID = this._SelectedNodePropertyViewModel.Uid,
                                    SourceObjectType = this._SelectedNodePropertyViewModel.ObjectType,
                                    SourcePropertyName = this._SelectedNodePropertyViewModel.Name,
                                    SourceX = this._SelectedNodePropertyViewModel.X,
                                    SourceY = this._SelectedNodePropertyViewModel.Y,

                                    TargetNodeUID = targetNodePropertyViewModel.Uid,
                                    TargetObjectType = targetNodePropertyViewModel.ObjectType,
                                    TargetPropertyName = targetNodePropertyViewModel.Name,
                                    TargetX = targetNodePropertyViewModel.X,
                                    TargetY = targetNodePropertyViewModel.Y
                                };

                                this._SelectedNodePropertyViewModel.RegisterSourceConnectorViewModel(connector);
                                targetNodePropertyViewModel.RegisterTargetConnectorViewModel(connector);
                                this.ConnectorViewModellCollection.Add(connector);

                                targetNodePropertyViewModel.IsConnected = true;

                            }

                            if(this.PreviewCurveEnd2Start == true &&
                                this._SelectedNodePropertyViewModel.IsConnected == false)
                            {
                                var connector = new ConnectorViewModel()
                                {
                                    SourceNodeUID = targetNodePropertyViewModel.Uid,
                                    SourceObjectType = targetNodePropertyViewModel.ObjectType,
                                    SourcePropertyName = targetNodePropertyViewModel.Name,
                                    SourceX = targetNodePropertyViewModel.X,
                                    SourceY = targetNodePropertyViewModel.Y,

                                    TargetNodeUID = _SelectedNodePropertyViewModel.Uid,
                                    TargetObjectType = _SelectedNodePropertyViewModel.ObjectType,
                                    TargetPropertyName = _SelectedNodePropertyViewModel.Name,
                                    TargetX = _SelectedNodePropertyViewModel.X,
                                    TargetY = _SelectedNodePropertyViewModel.Y
                                };

                                this._SelectedNodePropertyViewModel.RegisterTargetConnectorViewModel(connector);
                                targetNodePropertyViewModel.RegisterSourceConnectorViewModel(connector);
                                this.ConnectorViewModellCollection.Add(connector);

                                this._SelectedNodePropertyViewModel.IsConnected = true;
                            }
                            
                        }
                    }
                    //Final Connection 
                    //Final Connection 
                }

                this._IsNodePropertyDragging = false;
                this.ConnectorVisibility = Visibility.Hidden;
                Mouse.Capture(null);
            }

            if (this._IsDragSelectionStart == true)
            {
                this._IsDragSelectionStart = false;
                this.SelectionVisibility = Visibility.Hidden;
                this.SelectionWidth = 0;
                this.SelectionHeight = 0;
                Mouse.Capture(null);
            }
        }



        protected override void OnMouseRightButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseRightButtonDown(e);


            // Dragging Test!!!
            // Dragging Test!!!
            Keyboard.Focus(this);
            this._RightButtonDownPos = e.GetPosition(this);
            this._ZoomAndPanStartMatrix = this.ZoomAndPan.Matrix;
            Mouse.Capture(this, CaptureMode.SubTree);//?????????????????

            // Dragging Test!!!
            // Dragging Test!!!


            this._IsDraggingCanvas = true;



        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            base.OnMouseMove(e);


            // Current Mouse Position 
            Point mousePos = e.GetPosition(this);
            Point delta = new Point(mousePos.X - _PrevMousePosOnCanvas.X, mousePos.Y - _PrevMousePosOnCanvas.Y);

            if (this._IsDraggingCanvas)
            {
                _ZoomAndPan.StartX -= delta.X;
                _ZoomAndPan.StartY -= delta.Y;
            }

            if (this._IsNodeDragging)
            {
                //Group Selection Start
                foreach (var node in this.NodeViewModelCollection)
                {

                    if (node.IsSelected == true)
                    {
                        node.X += delta.X / _ZoomAndPan.Scale;
                        node.Y += delta.Y / _ZoomAndPan.Scale;


                    }
                }
            }

            if (this._IsNodePropertyDragging)
            {

                if(this.PreviewCurveStart2End == true)
                {
                    this.PreviewCurveEndX += delta.X / _ZoomAndPan.Scale;
                    this.PreviewCurveEndY += delta.Y / _ZoomAndPan.Scale;
                    this.ComputeCurve();
                }
                else if(this.PreviewCurveEnd2Start == true)
                {
                    this.PreviewCurveStartX += delta.X / _ZoomAndPan.Scale;
                    this.PreviewCurveStartY += delta.Y / _ZoomAndPan.Scale;
                    this.ComputeCurve();
                }
            }


            if (this._IsDragSelectionStart)
            {

                Point dragCanvasMousePos = e.GetPosition(this.PART_DragAndSelectionCanvas);

                if (dragCanvasMousePos.X - this.SelectionStartX > 0)
                {
                    this.SelectionWidth = dragCanvasMousePos.X - this.SelectionStartX;
                }

                if (dragCanvasMousePos.Y - this.SelectionStartY > 0)
                {
                    this.SelectionHeight = dragCanvasMousePos.Y - this.SelectionStartY;
                }


                this._SelectionCanvasEndPose = e.GetPosition(this.NodeCanvas);


                //Group Selection Start
                foreach (var node in this.NodeViewModelCollection)
                {

                    if (node.X > this._SelectionCanvasStartPos.X &&
                       node.X < this._SelectionCanvasEndPose.X &&
                       node.Y > this._SelectionCanvasStartPos.Y &&
                       node.Y < this._SelectionCanvasEndPose.Y)
                    {
                        node.IsSelected = true;
                    }
                    else
                    {
                        node.IsSelected = false;
                    }
                }
            }


            //Update mouse Pose
            _PrevMousePosOnCanvas = mousePos;

            e.Handled = true;

        }

        protected override void OnMouseRightButtonUp(MouseButtonEventArgs e)
        {
            base.OnMouseRightButtonUp(e);



            if (this._IsDraggingCanvas)
            {
                this._IsDraggingCanvas = false;
                Mouse.Capture(null);
            }
        }


        private void FlowChartViewControl_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            this._ZoomAndPan.ViewWidth = ActualWidth;
            this._ZoomAndPan.ViewHeight = ActualHeight;
        }
        #endregion


        #region DependencyObjects

        public static readonly DependencyProperty NodeViewModelCollectionProperty = DependencyProperty.Register("NodeViewModelCollection", typeof(ObservableCollection<ViewModel.NodeViewModel>), typeof(FlowChartView));
        public ObservableCollection<ViewModel.NodeViewModel> NodeViewModelCollection
        {
            get
            {
                return (ObservableCollection<ViewModel.NodeViewModel>)GetValue(NodeViewModelCollectionProperty);
            }

            set
            {
                SetValue(NodeViewModelCollectionProperty, value);
            }
        }

        public static readonly DependencyProperty ConnectorViewModellCollectionProperty = DependencyProperty.Register("ConnectorViewModellCollection", typeof(ObservableCollection<ViewModel.ConnectorViewModel>), typeof(FlowChartView));
        public ObservableCollection<ViewModel.ConnectorViewModel> ConnectorViewModellCollection
        {
            get
            {
                return (ObservableCollection<ViewModel.ConnectorViewModel>)GetValue(ConnectorViewModellCollectionProperty);
            }

            set
            {
                SetValue(ConnectorViewModellCollectionProperty, value);
            }
        }




        public static readonly DependencyProperty ConnectorVisibilityProperty = DependencyProperty.Register("ConnectorVisibility", typeof(Visibility), typeof(FlowChartView), new PropertyMetadata(Visibility.Hidden));
        public Visibility ConnectorVisibility
        {
            get
            {
                return (Visibility)GetValue(ConnectorVisibilityProperty);
            }

            set
            {
                SetValue(ConnectorVisibilityProperty, value);
            }
        }





        public static readonly DependencyProperty SelectionVisibilityProperty = DependencyProperty.Register("SelectionVisibility", typeof(Visibility), typeof(FlowChartView), new PropertyMetadata(Visibility.Hidden));
        public Visibility SelectionVisibility
        {
            get
            {
                return (Visibility)GetValue(SelectionVisibilityProperty);
            }

            set
            {
                SetValue(SelectionVisibilityProperty, value);
            }
        }



        public static readonly DependencyProperty SelectionStartXProperty = DependencyProperty.Register("SelectionStartX", typeof(double), typeof(FlowChartView), new PropertyMetadata(0.0));
        public double SelectionStartX
        {
            get
            {
                return (double)GetValue(SelectionStartXProperty);
            }

            set
            {
                SetValue(SelectionStartXProperty, value);
            }
        }

        public static readonly DependencyProperty SelectionStartYProperty = DependencyProperty.Register("SelectionStartY", typeof(double), typeof(FlowChartView), new PropertyMetadata(0.0));
        public double SelectionStartY
        {
            get
            {
                return (double)GetValue(SelectionStartYProperty);
            }

            set
            {
                SetValue(SelectionStartYProperty, value);
            }
        }


        public static readonly DependencyProperty SelectionWidthProperty = DependencyProperty.Register("SelectionWidth", typeof(double), typeof(FlowChartView), new PropertyMetadata(0.0));
        public double SelectionWidth
        {
            get
            {
                return (double)GetValue(SelectionWidthProperty);
            }

            set
            {
                SetValue(SelectionWidthProperty, value);
            }
        }

        public static readonly DependencyProperty SelectionHeightProperty = DependencyProperty.Register("SelectionHeight", typeof(double), typeof(FlowChartView), new PropertyMetadata(0.0));


        public double SelectionHeight
        {
            get
            {
                return (double)GetValue(SelectionHeightProperty);
            }

            set
            {
                SetValue(SelectionHeightProperty, value);
            }
        }


        #endregion

    }
}