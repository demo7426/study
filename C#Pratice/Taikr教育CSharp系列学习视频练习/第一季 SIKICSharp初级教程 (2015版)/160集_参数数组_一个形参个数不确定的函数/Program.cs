using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _160集_参数数组_一个形参个数不确定的函数
{

    internal class Program
    {
        static int Sum(params int[] _Num)
        {
            int nSum = 0;
            foreach (var item in _Num)
                nSum += item;
            return nSum;
        }

        static void Main(string[] args)
        {
            Console.WriteLine(Sum(13, 34, 22, 1, 672));//由编译器自己将这些数据转换位数组，赋值给形参
            Console.ReadKey();
        }
    }
}
