using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _103集_字符串类StringBuilder的构造
{
    internal class Program
    {
        static void Test01()
        {
            StringBuilder sb = new StringBuilder("www.baidu.com");//这种原字符串的值不可以被改变，如果改变只能像string一样，重新开辟空间赋值过去。
            StringBuilder sb2 = new StringBuilder(20);//指定容量，容量不够，再次开辟2倍大的空间进行使用
            StringBuilder sb3 = new StringBuilder("www.baidu.com", 100);
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
