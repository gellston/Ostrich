using System;

namespace ConsoleSharp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            try
            {
                HV.V2.Script script = new HV.V2.Script();
                script.SetAddonPath("C://Github//Ostrich//Ostrich//x64//Debug//");


                script.CreateContext("test");
                using var start = script.AddNode("test", "start", 50002);
                using var end1 = script.AddNode("test", "end1", 50003);
                using var end2 = script.AddNode("test", "end2", 50003);
                using var loop = script.AddNode("test", "loop", 50004);
                using var sleep = script.AddNode("test", "sleep", 50005);



                script.Connect("test", start, "Exec", loop, "Exec");
                script.Connect("test", loop, "Complete", end1, "Exec");
                script.Connect("test", loop, "Loop", sleep, "Exec");
                script.Connect("test", sleep, "Exec", end2, "Exec");

                script.CopyContext("test", "test2");
                for(int count =0; count < 20; count ++)
                {
                    try
                    {


                        script.Run("test2");
     


                    }
                    catch(Exception ex)
                    {
                        Console.WriteLine(ex.ToString());
                    }

                }

                script.Save("test", "C://Github//Ostrich//Ostrich//x64//Debug//test.js");
                script.Save("test2", "C://Github//Ostrich//Ostrich//x64//Debug//test2.js");

            }
            catch(Exception ex)
            {
                System.Console.WriteLine(ex.ToString());
            }


            
            
        }
    }
}
