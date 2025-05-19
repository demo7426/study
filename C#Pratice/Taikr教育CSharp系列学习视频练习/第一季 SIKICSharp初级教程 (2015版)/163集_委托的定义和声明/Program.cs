using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _163集_委托的定义和声明
{
    public delegate double MyDelegate(double _X, double _Y);
    internal class Program
    {
        static double Mul(double _X, double _Y)
        {
            return _X * _Y;
        }

        static double Divide(double _X, double _Y)
        {
            return _X/ _Y;
        }

        static void Main(string[] args)
        {
            MyDelegate myDelegate;
            myDelegate = Mul;

            Console.WriteLine(myDelegate(2, 3));

            myDelegate = Divide;
            Console.WriteLine(myDelegate(2, 3));
            Console.ReadKey();
        }
    }
}
