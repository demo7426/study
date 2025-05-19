using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _218集_抽象类
{
    internal class CCrow : CBird
    {
        public override void Fly()//必须实现父类里面的抽象类
        {
            Console.WriteLine("Crow fly.");
        }
    }
}
