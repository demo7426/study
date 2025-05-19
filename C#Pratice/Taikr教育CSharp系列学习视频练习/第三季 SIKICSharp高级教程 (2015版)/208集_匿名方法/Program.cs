using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _208集_匿名方法
{
    internal class Program
    {
        private static double Add(int _X, int _Y)
        {
            return _X + _Y;
        }
        static void Test01()
        {
            Func<int, int, double> func = delegate (int _X, int _Y)
            {
                return _X - _Y;
            };
            //Func<int, int, double> func += Add;//Func没有多播委托这个功能，因为它是必须有返回值的

            Console.WriteLine(func.Invoke(2, 3));
        }

        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
