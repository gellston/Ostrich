using GraphViewerTest.Util;
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

        protected Point _RightButtonDownPos;
        protected Point _LeftButtonDownPos;
        protected Point _PrevMousePos;
        protected bool _IsDraggingCanvas;
        private Matrix _ZoomAndPanStartMatrix;
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

            this._ZoomAndPan.UpdateTransform += _ZoomAndPan_UpdateTransform;
        }

        private void _ZoomAndPan_UpdateTransform()
        {
            if(this._NodeCanvas != null)
                this._NodeCanvas.RenderTransform = new MatrixTransform(this._ZoomAndPan.Matrix);
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
            Point delta = new Point(mousePos.X - _PrevMousePos.X, mousePos.Y - _PrevMousePos.Y);

            if (this._IsDraggingCanvas)
            {
                _ZoomAndPan.StartX -= delta.X;
                _ZoomAndPan.StartY -= delta.Y;
            }

            _PrevMousePos = mousePos;


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
        #endregion
    }
}
