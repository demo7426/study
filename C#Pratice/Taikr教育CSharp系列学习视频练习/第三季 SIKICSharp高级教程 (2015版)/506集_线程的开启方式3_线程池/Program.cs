using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace _506集_线程的开启方式3_线程池
{
    internal class Program
    {
        static void PrintfOut(object state)
        {
            Console.WriteLine("线程开始" + Thread.CurrentThread.ManagedThreadId);
            Console.WriteLine("线程结束" + Thread.CurrentThread.ManagedThreadId);
        }
        static void Test01()
        {
            //线程池所创建的线程都是后台线程，需要阻塞进程，防止被主进程强行结束
            //ThreadPool提供的线程推荐应用于小任务，如果方法执行事件过长推荐使用Thread创建线程
            ThreadPool.QueueUserWorkItem(PrintfOut);
            ThreadPool.QueueUserWorkItem(PrintfOut);
            ThreadPool.QueueUserWorkItem(PrintfOut);
            ThreadPool.QueueUserWorkItem(PrintfOut);
            ThreadPool.QueueUserWorkItem(PrintfOut);
            ThreadPool.QueueUserWorkItem(PrintfOut);
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadLine();
        }
    }
}
