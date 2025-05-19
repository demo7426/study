using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _219集_密封类和密封方法
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //sealed两种功能：
            //  1、sealed密封类时，不允许该类再被继承
            //  2、sealed密封重写虚函数时，再次被继承时，不能再次重写
        }
    }

    class CPerson
    {
        public virtual void Eat()
        {
            Console.WriteLine("Person eat.");
        }
    }

    class CMan: CPerson
    {
        public sealed override void Eat()
        {
            Console.WriteLine("Person eat.");
        }
    }

    sealed class CStudent : CMan
    {
        //public override void Eat(){}//错误,sealed密封重写虚函数时，再次被继承时，不能再次重写
    }

    //class CStudent01 : CStudent//错误,sealed密封类时，不允许该类再被继承
    //{

    //}
}
