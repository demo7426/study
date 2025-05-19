using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _206集_面向对象编程_类
{
    internal class CCustomer
    {
        /// <summary>
        /// 顾客ID
        /// </summary>
        public UInt32 m_strId { get; set; }
        
        /// <summary>
        /// 顾客名称
        /// </summary>
        public string m_strName { get; set; }

        public void Show()
        {
            Console.WriteLine("Id 为：" + m_strId + "\n名称为：" + m_strName);
        }

    }
}
