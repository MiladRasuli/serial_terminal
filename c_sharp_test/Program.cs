using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using clr;
namespace c_sharp_test
{
    class Program
    {

        public static void _callback(string msg,UInt32 len)
        {
            //string message;
            Console.WriteLine(msg.Substring(0, (int)len));
        }
        static void Main(string[] args)
        {
          
            var math_clr = new clr.math();
            var serial_clr = new clr.serial(9600, "COM10");
            math_clr.print_message("Welcom to clr. this message is from c#");
            math_clr.print_pow(7, 5);
            Console.Write("------------------\n");
            serial_clr.write("Hello from C# program\r\n");
            /*_callback("salam", 2);*/
            serial_clr.on_receive(_callback) ;
            Console.Read();
        }
    }
}
