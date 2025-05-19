using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _231集_泛型类的定义
{
    internal class CVector<T>
    {
        private T X { get; set; }
        private T Y { get; set; }

        public CVector(T _X, T _Y)
        {
            this.X = _X;
            this.Y = _Y;
        }

        public string GetSum()
        {
            return this.X + "" + this.Y;
        }
    }
}
