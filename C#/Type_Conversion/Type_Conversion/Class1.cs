using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Type_Conversion
{
    class Class1
    {
        public void Print_Vale(string buffer)
        {
            
            
        }
    }
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        [STAThread]
        static void Main()
        {
            string buffer = "00001235109510051300";
            int i;
            int j = 0;
            int[] a=new int[10];
            
            float[] Pressure_Value = new float[10];
            //float b = Convert.ToSingle(a);
            //float b = float.Parse(a);

            for (i = 0; i < buffer.Length; i= i+4)
            {
                string Value_Buffer= buffer.Substring(i+1,3);
                a[j] = int.Parse(Value_Buffer);
                Console.WriteLine("{0}", a[j]);
                j++;
                Console.ReadKey();
            }
        }
    }
}
