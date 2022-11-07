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

        protected Point _RightButtonDownPos;
        protected Point _LeftButtonDownPos;
        protected Point _PrevMousePosOnCanvas;
        protected bool _IsDraggingCanvas;
        protected bool _IsNodeDragging;
        private Matrix _ZoomAndPanStartMatrix;
        private NodeViewModel _SelectedNodeViewModel = null;
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
                    nodeViewModel.IsSelected = true;
                    Mouse.Capture(this, CaptureMode.SubTree);//?????????????????

                    //이전에 선택되어 있는 아이템 선택 해제 
                    if (nodeViewModel != this._SelectedNodeViewModel && this._SelectedNodeViewModel != null)
                        this._SelectedNodeViewModel.IsSelected = false;


                    if(nodeViewModel.IsSelected)
                    {
                        // 현재 아이템으로 선택 설정 드래깅 시작 
                        this._SelectedNodeViewModel = nodeViewModel;
                        _IsNodeDragging = true;
                    }
                }

            }
            else
            {    //노드가 아닌 오브젝트를 선택시 선택되어있던 오브젝트 해제 
                if (this._SelectedNodeViewModel != null)
                {
                    this._SelectedNodeViewModel.IsSelected = false;
                }
            }






            System.Diagnostics.Debug.WriteLine("test");
        }

        protected override void OnMouseLeftButtonUp(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonUp(e);



            if (this._IsNodeDragging == true)
            {
                this._IsNodeDragging = false;
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
                this._SelectedNodeViewModel.X += delta.X / _ZoomAndPan.Scale;
                this._SelectedNodeViewModel.Y += delta.Y / _ZoomAndPan.Scale;
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
        #endregion
    }
}
