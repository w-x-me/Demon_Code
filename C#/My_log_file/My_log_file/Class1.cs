using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
namespace My_log_file
{
    class Class1
    {

        static void Main()
        {
            string message = string.Format(DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff") + ":" + "异物检测完毕");
            Console.WriteLine("{0}", message);
            using (StreamWriter writer = File.AppendText(@"D:/work/C#/My_log_file/1.txt"))
            {
                //writer.WriteLine(message);
                writer.Write(message);
            }
            Console.WriteLine("hello world");
            Console.ReadKey();
        }
    }
}
