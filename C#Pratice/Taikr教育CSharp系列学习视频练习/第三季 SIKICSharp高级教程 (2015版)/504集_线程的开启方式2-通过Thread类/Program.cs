using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace _504集_线程的开启方式2_通过Thread类
{
    internal class Program
    {
        static void Add(object _X)
        {
            Console.WriteLine((int)_X + 1);
        }

        static void Test01()
        {
            Thread thread = new Thread(Add);
            thread.Start(2);
        }

       
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
