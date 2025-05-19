using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _205集_异常处理_案列2
{
    internal class Program
    {
        static void Test01()
        {
            int[] nNum = new int[] { 0, 0 };

            for (int i = 0; i < nNum.Length; i++)
            {
                Console.WriteLine("请输入第" + i + "个数字：");

                while (true)
                {
                    try
                    {
                        nNum[i] = Convert.ToInt32(Console.ReadLine());//如果try语句块捕获到了异常，则后续try语句不在执行。
                        break;
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine("您输入的参数错误，请重新输入。");
                        //throw new Exception("您输入" + i + "个的参数错误，请重新输入。", ex);
                    }
                }
            }

            Console.WriteLine("计算的和为：" + (nNum[0] + nNum[1]));

        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
