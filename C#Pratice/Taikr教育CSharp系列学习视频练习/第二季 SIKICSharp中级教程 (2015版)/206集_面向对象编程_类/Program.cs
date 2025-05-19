using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _206集_面向对象编程_类
{
    internal class Program
    {
        static void Test01()
        {
            CCustomer cCustomer = new CCustomer();
            cCustomer.m_strId = 0x01;
            cCustomer.m_strName = "李华";
            cCustomer.Show();

        }

        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
