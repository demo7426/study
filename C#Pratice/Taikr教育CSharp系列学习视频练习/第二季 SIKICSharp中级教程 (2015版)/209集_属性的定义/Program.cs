using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _209集_属性的定义
{
    internal class Program
    {
        static void Test01()
        {
            CStudent cStudent = new CStudent();
            cStudent.Id = 0x10;
            //cStudent.Name = "siki";//Name的set方法为私有，外部无法访问
            Console.WriteLine("Id 为" + cStudent.Id);
            Console.WriteLine("Name 为" + cStudent.Name);

        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
