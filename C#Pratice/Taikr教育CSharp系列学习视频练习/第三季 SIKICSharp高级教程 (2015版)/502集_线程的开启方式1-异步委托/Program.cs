using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace _502集_线程的开启方式1_异步委托
{
    internal class Program
    {
        static int StrSplice(int _ID, string _Name)
        {
            Console.WriteLine(Convert.ToString(_ID) + _Name);
            Thread.Sleep(100);
            return -1;
        }

        static void Test01()
        {
            Func<int, string, int> func = new Func<int, string, int>(StrSplice);

            //异步委托调用（实质是单独开辟线程调用该委托内部方法）
            IAsyncResult asyncResult = func.BeginInvoke(35, "MeiXi", null, null);

            Console.WriteLine(36 + "Cristiano");

            while (asyncResult.IsCompleted == false)
            {
                Console.Write(".");
                Thread.Sleep(10);
            }
            Console.WriteLine();

            int nRtn = func.EndInvoke(asyncResult);//取得异步线程的返回值
            Console.WriteLine(nRtn);
        }

        static void Main(string[] args)
        {
            Test01();
            Console.ReadLine();
        }
    }
}
