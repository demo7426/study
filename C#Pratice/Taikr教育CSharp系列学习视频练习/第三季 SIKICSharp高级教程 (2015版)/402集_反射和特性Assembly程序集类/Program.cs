using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace _402集_反射和特性Assembly程序集类
{
    internal class Program
    {
        static void Test01()
        {
            CMyClass cMyClass = new CMyClass();
            Assembly assembly = cMyClass.GetType().Assembly;
            Console.WriteLine(assembly.FullName);

            Type[] types = assembly.GetTypes();
            foreach (Type t in types)
            {
                Console.WriteLine(t);
                //Console.WriteLine(t.FullName);//上下两种写法都可以
            }
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
