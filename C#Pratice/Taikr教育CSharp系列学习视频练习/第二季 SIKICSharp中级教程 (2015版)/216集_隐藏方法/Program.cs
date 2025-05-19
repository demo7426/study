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
            //隐藏方法的调用规则只和对象类型有关,和构造类型无关
            CEnemy cEnemy = new CEnemy();
            cEnemy.Move();
            Console.WriteLine();

            CBoss cBoss = new CBoss();
            cBoss.Move();
            Console.WriteLine();

            CEnemy cEnemy1 = new CBoss();
            cEnemy1.Move();
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
