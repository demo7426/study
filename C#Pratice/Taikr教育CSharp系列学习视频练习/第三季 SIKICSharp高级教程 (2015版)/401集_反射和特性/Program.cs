using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Reflection;

namespace _401集_反射和特性
{
    internal class Program
    {
        static void Test01()
        {
            CMyClass cMyClass = new CMyClass();
            Type type = cMyClass.GetType();

            Console.WriteLine(type.Name);//获取当前类的名字
            Console.WriteLine(type.Namespace);//获取该类的命名空间
            Console.WriteLine(type.Assembly);//获取该类的程序集56

            //只能获取到公共的字段、属性、方法。
            FieldInfo[] fieldInfos = type.GetFields();

            Console.Write("字段：");
            foreach (FieldInfo fieldInfo in fieldInfos)
            {
                Console.Write(fieldInfo.Name + " "); 
            }
            Console.WriteLine();

            PropertyInfo[] propertyInfos = type.GetProperties();
            Console.Write("属性：");
            foreach (PropertyInfo propertyInfo in propertyInfos)
            {
                Console.Write(propertyInfo.Name + " ");
            }
            Console.WriteLine();

            MethodInfo[] methodInfos = type.GetMethods();
            Console.Write("方法：");
            foreach(MethodInfo methodInfo in methodInfos)
            {
                Console.Write(methodInfo.Name + " ");
            }
            Console.WriteLine();
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
