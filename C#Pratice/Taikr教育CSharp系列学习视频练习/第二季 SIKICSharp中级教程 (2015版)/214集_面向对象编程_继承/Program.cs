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
            CEnemy cEnemy = new CEnemy();
            cEnemy.Move();
            cEnemy.Attack();
            Console.WriteLine();

            CBoss cBoss = new CBoss();
            cBoss.Move();
            cBoss.Attack();
            cBoss.Dash();
            Console.WriteLine();

            CEnemy cEnemy1 = new CBoss();
            cEnemy1.Move();
            cEnemy1.Attack();
            ((CBoss)cEnemy1).Dash();

            //CBoss cBoss1 = (CBoss)cEnemy;//父类无法强制转换为子类，因为子类的功能大于等于了父类

        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
