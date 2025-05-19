using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _403集_Obsolete特性
{
    internal class Program
    {
        [Obsolete]//Obsolete表示该方法已经过时；
        static void Method01()
        {
            Console.WriteLine("Method01 被调用");
        }
        [Obsolete("This method is out of date.")]//第一个参数为警告调用方的信息
        static void Method02()
        {
            Console.WriteLine("Method02 被调用");
        }
        [Obsolete("This method is out of date.", true)]//第二个参数代表该方法是否允许调用;true--不允许被调用,false--允许被调用
        static void Method03()
        {
            Console.WriteLine("Method03 被调用");
        }
        static void Main(string[] args)
        {
            Method01();
            Method02();
            //Method03();
            Console.ReadKey();
        }
    }
}
