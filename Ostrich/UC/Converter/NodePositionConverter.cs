using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows;
using ViewModel;
using UC.Util;

namespace UC.Converter
{
    public class NodePositionConverter : IMultiValueConverter
    {
        public object Convert(object[] values, Type targetType, object parameter, CultureInfo culture)
        {

            if (values.Length < 2 || values == null)
            {
                throw new ArgumentException("Invalid values");
            }

            ContentPresenter contentPresenter = values[0] as ContentPresenter;
            if (contentPresenter != null && contentPresenter.DataContext != null)
            {
                if (contentPresenter.DataContext.GetType() == typeof(NodeViewModel))
                {
                    var dataContext = (NodeViewModel)contentPresenter.DataContext;

                    List<NodeInputPropertyView> inputPropertyViewCollection = new List<NodeInputPropertyView>();
                    List<NodeOutputPropertyView> outputPropertyViewCollection = new List<NodeOutputPropertyView>();

                    ViewUtil.FindChildren(contentPresenter, inputPropertyViewCollection);
                    ViewUtil.FindChildren(contentPresenter, outputPropertyViewCollection);

                    foreach (var input in inputPropertyViewCollection)
                    {
                        List<Border> propertySpotCollection = new List<Border>();
                        ViewUtil.FindChildren<Border>(input, propertySpotCollection);

                        var borderControl = propertySpotCollection.Find(data => data.Name == "PART_Node_Spot");


                        if (borderControl != null)
                        {
                            var inputDataContext = input.DataContext as NodePropertyViewModel;
                            Point point = borderControl.TransformToAncestor(contentPresenter).Transform(new Point(0, 0));
                            inputDataContext.X = point.X + dataContext.X + borderControl.ActualWidth / 2;
                            inputDataContext.Y = point.Y + dataContext.Y + borderControl.ActualHeight / 2;
                        }
                    }

                    foreach (var output in outputPropertyViewCollection)
                    {
                        List<Border> propertySpotCollection = new List<Border>();
                        ViewUtil.FindChildren<Border>(output, propertySpotCollection);

                        var borderControl = propertySpotCollection.Find(data => data.Name == "PART_Node_Spot");
   

                        if (borderControl != null)
                        {
                            var outputDataContext = output.DataContext as NodePropertyViewModel;
                            Point point = borderControl.TransformToAncestor(contentPresenter).Transform(new Point(0, 0));
                            outputDataContext.X = point.X + dataContext.X + borderControl.ActualWidth / 2;
                            outputDataContext.Y = point.Y + dataContext.Y + borderControl.ActualHeight / 2;
                        }
                    }


                    if (values[1] != DependencyProperty.UnsetValue)
                    {
                        return (double)values[1];
                    }

                }
            }


            return 0.0;
        }

        public object[] ConvertBack(object value, Type[] targetTypes, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
