using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _207集_多播委托
{
    internal class Program
    {
        private static void Printf01()
        {
            Console.WriteLine("Printf01调用");
        }
        private static void Printf02()
        {
            Console.WriteLine("Printf02调用");
        }

        static void Test01()//多播委托
        {
            Action action = new Action(Printf01);
            action += Printf02;
            action();
        }
        static void Test02()//获取多播委托的调用列表
        {
            Action action = Printf01;
            action += Printf02;

            Delegate[] delegates = action.GetInvocationList();
            foreach (Delegate d in delegates)
                d.DynamicInvoke();
        }

        static void Main(string[] args)
        {
            Test01();

            Console.WriteLine();
            Test02();
            Console.ReadKey();
        }
    }
}
