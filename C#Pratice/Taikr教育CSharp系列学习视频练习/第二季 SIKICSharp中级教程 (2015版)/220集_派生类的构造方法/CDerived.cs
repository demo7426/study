using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _220集_派生类的构造方法
{
    internal class CDerived:CBase
    {
        private int m_ny;

        public CDerived():base()//也可以简写为public CDerived()
        {
            Console.WriteLine("调用了CDerived构造函数。");
        }

        public CDerived(int _X, int _Y):base(_X)
        {
            m_ny = _Y;
            Console.WriteLine("调用了CDerived构造函数，赋值成功。" + this.m_ny);
        }
    }
}
