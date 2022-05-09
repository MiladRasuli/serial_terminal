using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using clr;
namespace c_sharp_test
{
    class Program
    {

        public static void _callback(string msg,UInt32 len)
        {
            //string message;
            Console.WriteLine(msg.Substring(0,(int)len));
        }
        public static void _err_callback(System.String err)
        {
            Console.WriteLine(err);
        }
        static void Main(string[] args)
        {
          
            var math_clr = new clr.math();
            math_clr.print_message("Welcom to clr. this message is from c#");
            math_clr.print_pow(10, 2);
            Console.Write("------------------\n");
            
            /*serial_clr.on_receive(_callback); // get from serial console
            serial_clr.on_error(_err_callback);
            serial_clr.start();
            serial_clr.write("salam!!"); // send to serial console

            Console.ReadLine();
            serial_clr.stop();
            */
            
            bool start_status = false;
            var serial_clr = new clr.serial(9600, "COM10");
            string command;
            do
            {
                command = Console.ReadLine();

                if (command.Contains("start") == true)
                {
                    Console.WriteLine("native serial initiate.");
                    serial_clr.on_receive(_callback);
                    serial_clr.on_error(_err_callback);
                    serial_clr.start();
                    start_status = true;

                }
                else if (command.Contains("stop") == true)
                {
                    if (!start_status) continue;
                    Console.WriteLine("native serial stopped.");
                    serial_clr.stop();
                    //sleep(10);
                    start_status = false;
                }
                if (start_status == true)
                {
                    serial_clr.write(command);
                }
            } while (!command.Contains("close"));
        }
    }
}
