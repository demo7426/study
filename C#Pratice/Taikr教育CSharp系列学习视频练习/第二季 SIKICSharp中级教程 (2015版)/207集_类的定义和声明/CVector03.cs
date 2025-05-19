using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _207集_类的定义和声明
{
    internal class CVector03
    {
        //没有使用get,set的均是字段，反之称为属性
        private float m_fX = 0;
        private float m_fY = 0;
        private float m_fZ = 0;

        /// <summary>
        /// 设置类内部属性
        /// </summary>
        /// <param name="_X"></param>
        /// <param name="_Y"></param>
        /// <param name="_Z"></param>
        public void Set(float _X, float _Y, float _Z)
        {
            this.m_fX = _X;
            this.m_fY = _Y;
            this.m_fZ = _Z;
        }

        public float Length()
        {
            return (float)Math.Sqrt(m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ);
        }
    }
}
