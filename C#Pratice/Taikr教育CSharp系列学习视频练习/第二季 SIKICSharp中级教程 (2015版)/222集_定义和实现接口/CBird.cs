using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _222集_定义和实现接口
{
    internal class CBird:IFly,Interface2//实现接口(可以同时实现多个接口文件)
    {
        public void Fly()
        {
            Console.WriteLine("Bird fly.");
        }

        public void Method01()
        {

        }

        public void Method02()
        {

        }
    }
}
