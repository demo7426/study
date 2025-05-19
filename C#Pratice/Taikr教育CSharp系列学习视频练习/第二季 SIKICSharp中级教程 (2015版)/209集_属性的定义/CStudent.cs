using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _209集_属性的定义
{
    internal class CStudent
    {
        /// <summary>
        /// 属性，这种简写语法，编译器后端会在自动补全字段
        /// </summary>
        public int Id { get; set; }

        /// <summary>
        /// 字段
        /// </summary>
        private string name;

        /// <summary>
        /// 属性
        /// </summary>
        public string Name
        {
            get { return name; }
            private set { name = value; }
        }


    }
}
