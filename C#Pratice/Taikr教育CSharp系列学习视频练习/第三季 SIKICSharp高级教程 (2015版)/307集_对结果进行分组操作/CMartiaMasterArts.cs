using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _301集_数据的初始化和LINQ的第一个基础使用
{
    /// <summary>
    /// 武林高手
    /// </summary>
    internal class CMartiaMasterArts
    {
        /// <summary>
        /// Id号
        /// </summary>
        public UInt32 Id { get; set; }
        /// <summary>
        /// 名字
        /// </summary>
        public string Name { get; set; }
        /// <summary>
        /// 年龄
        /// </summary>
        public UInt32 Age { get; set; }
        /// <summary>
        /// 门派
        /// </summary>
        public string Menpai { get; set; }
        /// <summary>
        /// 功夫名称
        /// </summary>
        public string KungFuName { get; set; }
        /// <summary>
        /// 等级
        /// </summary>
        public UInt32 Level { get; set; }

        public override string ToString()
        {
            return String.Format("Id:{0}\tName:{1}\tAge:{2}\tMenpai:{3}\tKungFuName:{4}\tLevel:{5}", Id, Name, Age, Menpai, KungFuName, Level);
        }
    }
}
