using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _209集_Lambda表达式
{
    internal class Program
    {
        static void Test01()
        {
            Func<int, int, int> func = (x, y) =>//Lambda表达式标准写法(推荐使用这个)
            {
                return x + y;
            };

            Func<int, int> func1 = x => x + 1;//只有一个参数的情况(如果方法内部只有一条语句，可以不使用{}、及return,编译器会自行判定是否需要添加return语句)

            Console.WriteLine(func(1, 2));
            Console.WriteLine(func1(1));
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
