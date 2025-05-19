using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _220集_派生类的构造方法
{
    internal class Program
    {
        static void Test01()
        {
            //先调用父类构造函数，再调用子类构造函数
            //CDerived cDerived = new CDerived();
            
            CDerived cDerived1 = new CDerived(1, 2);
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadLine();
        }
    }
}
