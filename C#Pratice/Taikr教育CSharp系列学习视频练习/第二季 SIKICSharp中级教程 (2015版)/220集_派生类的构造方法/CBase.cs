using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _220集_派生类的构造方法
{
    internal class CBase
    {
        private int m_nx;

        public CBase()
        {
            Console.WriteLine("调用了CBase构造函数。");
        }

        public CBase(int _X)
        {
            this.m_nx = _X;
            Console.WriteLine("调用了CBase构造函数 ，赋值成功。" + this.m_nx);
        }
    }
}
