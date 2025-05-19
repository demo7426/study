using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _218集_抽象类
{
    internal class Program
    {
        static void Test01()
        {
            CCrow cCrow = new CCrow();
            cCrow.Fly();

            CBird cBird = new CCrow();
            cBird.Fly();
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
