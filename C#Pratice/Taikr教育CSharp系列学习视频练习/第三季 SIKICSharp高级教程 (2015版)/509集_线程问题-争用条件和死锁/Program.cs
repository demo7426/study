using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace _509集_线程问题_争用条件和死锁
{
    internal class Program
    {
        static void Test01()
        {
            CMyChangeObject cMyChangeObject = new CMyChangeObject();

            while (true)
            {
                Thread thread = new Thread(cMyChangeObject.ChangeValue);
                Thread thread01 = new Thread(cMyChangeObject.ChangeValue);

                thread.Start();
                thread01.Start();
            }
        }
        static void Main(string[] args)
        {
            Test01();
        }
    }

    class CMyChangeObject
    {
        private int _state = 5;

        public int _State
        {
            get { return _state; }
            set { _state = value; }
        }

        public void ChangeValue()
        {
            lock(this)
            {
                _State++;
                if (_State == 5)
                    Console.WriteLine(Thread.CurrentThread.ManagedThreadId);

                _State = 5;
            }
        }
    }
}
