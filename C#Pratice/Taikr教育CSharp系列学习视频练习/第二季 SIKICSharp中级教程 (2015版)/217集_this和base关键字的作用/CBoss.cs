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
        /// 冲撞攻击
        /// </summary>
        public void Dash()
        {
            Console.WriteLine("Boss Dash.");
        }

        /// <summary>
        /// 测试函数
        /// </summary>
        public void Test01()
        {
            //this可以访问子类父类中的所有可以访问的字段、属性、方法；
            //base只能访问父类中的所有可以访问的字段、属性、方法。主要是有IDE提示效果，
            this.Move();
            this.Dash();
            Console.WriteLine();

            float fValue = this.UltimateSkill;

            base.Move();
        }
    }
}
