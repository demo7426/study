using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace _503集_检测委托线程的结束_通过等待句柄和回调函数
{
    internal class Program
    {
        static int StrSplice(int _ID, string _Name)
        {
            Console.WriteLine(Convert.ToString(_ID) + _Name);
            Thread.Sleep(100);
            return -1;
        }

        static void Test01()//通过等待句柄判断异步委托线程是否结束
        {
            Func<int, string, int> func = StrSplice;
            IAsyncResult asyncResult = func.BeginInvoke(35, "MeiXi", null, null);

            Console.WriteLine(36 + "Cristiano");

            //等待1000ms，在等待时间内结束函数则成功返回true,反之失败返回false
            bool bRtn = asyncResult.AsyncWaitHandle.WaitOne(1000);

            if (bRtn)
            {
                Console.WriteLine(func.EndInvoke(asyncResult));
            }
        }

        static void Test02()//当异步委托线程结束时，会默认调用传入的回调函数
        {
            Func<int, string, int> func = new Func<int, string, int>(StrSplice);

            //单数第二个参数为回调函数，倒数第一个参数为回调函数的传入数据
            //IAsyncResult asyncResult = func.BeginInvoke(35, "MeiXi", OnCallBackFunc, func);
            IAsyncResult asyncResult = func.BeginInvoke(35, "MeiXi", a =>
            {
                Console.WriteLine(func.EndInvoke(a));
            }, null);

            Console.WriteLine(36 + "Cristiano");
        }

        private static void OnCallBackFunc(IAsyncResult ar)
        {
            Func<int, string, int> func = ar.AsyncState as Func<int, string, int>;
            Console.WriteLine(func.EndInvoke(ar));
        }

        static void Main(string[] args)
        {
            //Test01();
            Test02();
            Console.ReadKey();
        }

    }
}
