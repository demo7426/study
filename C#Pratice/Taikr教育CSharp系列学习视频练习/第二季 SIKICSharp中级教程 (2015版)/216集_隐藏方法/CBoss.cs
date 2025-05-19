using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _214集_面向对象编程_继承
{
    //C#语法不支持同时继承多个类
    internal class CBoss:CEnemy
    {
        /// <summary>
        /// 终极技能伤害
        /// </summary>
        private float ultimateSkill;
        
        public float UltimateSkill
        {
            get { return ultimateSkill; }
            set { ultimateSkill = value; }
        }

        /// <summary>
        /// 移动 (隐藏方法：将父类的Move方法隐藏了，实际上是有的)
        /// </summary>
        public new void Move()
        {
            Console.WriteLine("Boss move.");
        }

        /// <summary>
        /// 冲撞攻击
        /// </summary>
        public void Dash()
        {
            Console.WriteLine("Boss Dash.");
        }
    }
}
