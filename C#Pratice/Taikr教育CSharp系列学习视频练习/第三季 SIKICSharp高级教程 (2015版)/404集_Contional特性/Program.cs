#define IsTest02//宏定义

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _404集_Contional特性
{
    internal class Program
    {
        [Conditional("IsTest01")]
        static void Test01()
        {
            Console.WriteLine("Test01 被调用");
        }
        [Conditional("IsTest02")]
        static void Test02()
        {
            Console.WriteLine("Test02 被调用");
        }
        static void Main(string[] args)
        {
            Test01();
            Test01();
            Test02();
            Console.ReadKey();
        }
    }
}
