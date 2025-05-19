using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _301集_数据的初始化和LINQ的第一个基础使用
{
    internal class CKungFu
    {
        public UInt32 Id { get; set; }

        public string Name { get; set; }

        /// <summary>
        /// 杀伤力
        /// </summary>
        public UInt32 Lethality { get; set; }

        public override string ToString()
        {
            return String.Format("Id:{0}\tName:{1}\tLethality:{2}", Id, Name, Lethality);
        }
    }
}
