using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace ini_rw
{
    class ini_rw
    {
        [DllImport("kernel32")]
        private static extern int GetPrivateProfileInt(string lpAppName, string lpKeyName, int nDefault, string lpFileName);
        static void Main()
        {
            int x_value;
            x_value = GetPrivateProfileInt("x_value", "x", 5, "D:/work/C#/ini_rw/config.ini");
            Console.WriteLine("{0}", x_value);
            Console.ReadKey();
        }
        
    }
}
