using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace _507集_线程的开启方式4_任务
{
    internal class Program
    {
        static void PrintfOut()
        {
            Console.WriteLine("线程开始" + Thread.CurrentThread.ManagedThreadId);
            Console.WriteLine("线程结束" + Thread.CurrentThread.ManagedThreadId);
        }
        static int PrintfOut02()
        {
            Console.WriteLine("线程开始" + Thread.CurrentThread.ManagedThreadId);
            Console.WriteLine("线程结束" + Thread.CurrentThread.ManagedThreadId);
            return -1;
        }
        static void Test01()
        {
            //Task的实质就是对Thread的一种再次封装
            Task task = new Task(PrintfOut);
            task.Start();

            TaskFactory taskFactory = new TaskFactory();
            taskFactory.StartNew(PrintfOut);

            TaskFactory<int> taskFactory2 = new TaskFactory<int>();
            var nRtn = taskFactory2.StartNew(PrintfOut02);

            Console.WriteLine("主进程开始");
            Console.WriteLine("主进程结束");
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
