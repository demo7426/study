using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _232集_泛型方法
{
    internal class Program
    {
        static string GetSum01<T>(T _X, T _Y)
        {
            return _X + "" + _Y;
        }
        static string GetSum02<T,T2,T3>(T _X, T _Y)
        {
            T2 strContext;
            return _X + "" + _Y;
        }
        static void Test01()
        {
           Console.WriteLine(GetSum01(12, 34));
           Console.WriteLine(GetSum02<int, string, double>(56, 78));
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
