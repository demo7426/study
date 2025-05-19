using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _201集_委托的定义和使用
{
    internal class Program
    {
        private delegate string GetAnString();
        private delegate void Printf();

        private static void Test01()
        {
            int nValue = -1;
            GetAnString getAnString = new GetAnString(nValue.ToString);

            Console.WriteLine(getAnString());
        }

        private static void Test02()
        {
            Printf printf = Printf01;
            PrintfStr(printf);
        }

        private static void PrintfStr(Printf _Printf)//委托相当于C语言里面的函数指针
        {
            _Printf();
        }

        private static void Printf01()
        {
            Console.WriteLine("Printf01 调用。");
        }
        static void Main(string[] args)
        {
            Test01();
            Test02();
            Console.ReadKey();
        }
    }
}
