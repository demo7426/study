using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _207集_类的定义和声明
{
    internal class Program
    {
        static void Test01()
        {
            CVector03 cVector03 = new CVector03();
            cVector03.Set(1, 2, 3);
            Console.WriteLine(cVector03.Length());

        }

        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
