using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _407集_创建自定义特性
{
    [MyTest("简单的特性类", ID = 48)]//当我们使用特性类时，后面的Attribute不需要写
    internal class Program
    {
        static void Test01()
        {
            Type type = typeof(Program);
            object[] objects = type.GetCustomAttributes(false);
            MyTestAttribute myTestAttribute = objects[0] as MyTestAttribute;
            Console.WriteLine(myTestAttribute.Description);
            Console.WriteLine(myTestAttribute.ID);
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
