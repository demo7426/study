using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _214集_面向对象编程_继承
{
    internal class Program
    {
        static void Test01()
        {
            //虚函数被重写之后的调用只和构造函数有关，与类对象类型无关
            CEnemy cEnemy = new CEnemy();
            cEnemy.Move();
            Console.WriteLine();

            CBoss cBoss = new CBoss(); 
            cBoss.Move();
            Console.WriteLine();

            CBoss cEnemy1 = new CBoss();
            cEnemy1.Move();
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
