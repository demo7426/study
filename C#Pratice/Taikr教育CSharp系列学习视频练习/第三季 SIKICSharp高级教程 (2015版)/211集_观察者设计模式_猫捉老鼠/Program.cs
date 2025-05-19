using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _211集_观察者设计模式_猫捉老鼠
{
    internal class Program
    {
        static void Test01()
        {
            CCat cCat = new CCat("Tom", "蓝白色");
            CMouse[] cMousses = new CMouse[]
            {
                new CMouse("米奇", "白色", cCat),
                new CMouse("米林", "粉色", cCat),
                new CMouse("米胡", "黑色", cCat)
            };

            cCat.Comming();
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
