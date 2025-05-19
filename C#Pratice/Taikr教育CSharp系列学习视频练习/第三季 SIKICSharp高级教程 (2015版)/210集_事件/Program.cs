using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _210集_事件
{
    internal class Program
    {
        private delegate double MyDelegate(int _X, int _Y);

        private MyDelegate myDelegate;
        static double Add(int _X, int _Y)
        {
            return _X + _Y;
        }

        static void Test01()
        {
            Program program = new Program();
            program.myDelegate = Add;

            Console.WriteLine(program.myDelegate(1, 2));
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
