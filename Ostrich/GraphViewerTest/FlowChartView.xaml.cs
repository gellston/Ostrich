using GraphViewerTest.Util;
using GraphViewerTest.ViewModel;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
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

namespace GraphViewerTest
{
    /// <summary>
    /// FlowChartView.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class FlowChartView : UserControl
    {

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
        #endregion


        #region Constructor
        public FlowChartView()
        {
            InitializeComponent();

        }

        #endregion


        #region Functions
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
            if(this._NodeCanvas != null)
                this._NodeCanvas.RenderTransform = new MatrixTransform(this._ZoomAndPan.Matrix);


            if(this._ConnectorCanvas != null)
                this._ConnectorCanvas.RenderTransform = new MatrixTransform(this._ZoomAndPan.Matrix);
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
            if(clickedItem != null && clickedItem.DataContext != null)
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


                if(clickedItem.DataContext.GetType() == typeof(NodePropertyViewModel))
                {
                    var property = clickedItem.DataContext as NodePropertyViewModel;
                    property.IsPressed = true;
                    Mouse.Capture(this, CaptureMode.SubTree);//?????????????????

                    this._SelectedNodePropertyViewModel = property;
                    this._IsNodePropertyDragging = true;
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

            if(this._IsNodePropertyDragging == true)
            {
                if (this._SelectedNodePropertyViewModel != null)
                    this._SelectedNodePropertyViewModel.IsPressed = false;
                this._IsNodePropertyDragging = false;
                Mouse.Capture(null);
            }


            if(this._IsDragSelectionStart == true)
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
            Mouse.Capture(this, CaptureMode.SubTree );//?????????????????

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


            if (this._IsDragSelectionStart)
            {

                Point dragCanvasMousePos = e.GetPosition(this.PART_DragAndSelectionCanvas);

                if(dragCanvasMousePos.X - this.SelectionStartX > 0)
                {
                    this.SelectionWidth = dragCanvasMousePos.X - this.SelectionStartX;
                }

                if(dragCanvasMousePos.Y - this.SelectionStartY > 0)
                {
                    this.SelectionHeight = dragCanvasMousePos.Y - this.SelectionStartY;
                }


                this._SelectionCanvasEndPose = e.GetPosition(this.NodeCanvas);


                //Group Selection Start
                foreach(var node in this.NodeViewModelCollection)
                {

                    if(node.X > this._SelectionCanvasStartPos.X &&
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
