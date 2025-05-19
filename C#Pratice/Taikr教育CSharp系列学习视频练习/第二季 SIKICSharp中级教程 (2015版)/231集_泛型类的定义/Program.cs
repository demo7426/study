using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _231集_泛型类的定义
{
    internal class Program
    {
        static void Test01()
        {
            CVector<int> cVector = new CVector<int>(12, 34);
            Console.WriteLine(cVector.GetSum());
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
