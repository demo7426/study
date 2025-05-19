using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _406集_DebuggerStepThrough特性
{
    internal class Program
    {
        [DebuggerStepThrough]//表示在逐语句调试时，不需要进入该函数执行
        static void Test01()
        {
            Console.WriteLine("Test01 被调用.");
        }

        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
