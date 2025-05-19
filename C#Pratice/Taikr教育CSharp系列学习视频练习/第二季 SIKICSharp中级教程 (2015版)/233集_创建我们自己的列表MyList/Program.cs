using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _233集_创建我们自己的列表MyList
{
    internal class Program
    {
        static void Test01()
        {
            MyList<int> list = new MyList<int>();
            list.Add(1);
            list.Add(2);
            list.Add(3);
            list.Add(4);
            list.Add(5);
            list.Add(6);

            list.Insert(0, 10);
            for (int i = 0; i < list.Count; i++)
            {
                Console.Write(list[i] + " ");
            }

            list.RemoveAt(1);
            Console.WriteLine();
            for (int i = 0; i < list.Count; i++)
            {
                Console.Write(list[i] + " ");
            }
            Console.WriteLine();
        }

        static void Test02()
        {
            MyList<int> list = new MyList<int>();
            list.Add(10);
            list.Add(9);
            list.Add(8);
            list.Add(9);
            list.Add(11);
            for (int i = 0; i < list.Count; i++)
            {
                Console.Write(list[i] + " ");
            }
            Console.WriteLine();

            Console.WriteLine(list.IndexOf(9));
            Console.WriteLine(list.LastIndexOf(9));

            list.Sort();
            for (int i = 0; i < list.Count; i++)
            {
                Console.Write(list[i] + " ");
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Test01():");
            Test01();

            Console.WriteLine();
            Console.WriteLine("Test02():");
            Test02();
            Console.ReadKey();
        }
    }
}
