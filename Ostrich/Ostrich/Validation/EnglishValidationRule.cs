using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Ostrich.Validation
{
    public class EnglishValidationRule : ValidationRule
    {

        public EnglishValidationRule() { 
        
        
        }

        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            try
            {

                if(((string)value).Length == 0)
                {
                    return new ValidationResult(false, "Null string format");
                }


                var regexItem = new Regex("^[a-zA-Z0-9 ]*$");

                if (regexItem.IsMatch((string)value)) {
                    return ValidationResult.ValidResult;
                }
                else
                {
                    return new ValidationResult(false, "Invalid string format");
                }



            }catch(Exception ex)
            {


                return new ValidationResult(false, "Unexpected error : " + ex.Message);
            }


        }
    }
}
