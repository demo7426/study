using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _206集_拓展的通用的冒泡排序的方法
{
    internal class CEmployee
    {
        public string Name { get; set; }
        public int Slary { get; set; }
        public CEmployee(string name, int slary)
        {
            Name = name;
            Slary = slary;
        }

        public override string ToString()
        {
            return Name + ":" + Slary;
        }

        /// <summary>
        /// 比较(如果前者大于后者则返回true，反之返回false)
        /// </summary>
        /// <param name="_CEmployee01"></param>
        /// <param name="_CEmployee02"></param>
        /// <returns></returns>
        public static bool CompareTo(CEmployee _CEmployee01, CEmployee _CEmployee02)
        {
            if (_CEmployee01.Slary > _CEmployee02.Slary)
            {
                return true;
            }
            return false;
        }
    }
}
