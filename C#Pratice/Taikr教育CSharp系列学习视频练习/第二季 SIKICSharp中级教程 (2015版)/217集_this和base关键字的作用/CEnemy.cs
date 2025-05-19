using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _214集_面向对象编程_继承
{
    /// <summary>
    /// 敌人基类
    /// </summary>
    internal class CEnemy
    {
        /// <summary>
        /// 血量
        /// </summary>
        private float hp;

        /// <summary>
        /// 速度
        /// </summary>
        private float speed;

        /// <summary>
        /// 字段对应的属性
        /// </summary>
        public float Hp
        { 
            get { return hp; } 
            set { hp = value; } 
        }

        /// <summary>
        /// 字段对应的属性
        /// </summary>
        public float Speed
        {
            get { return speed; }
            set { speed = value; }
        }

        /// <summary>
        /// 攻击
        /// </summary>
        public void Attack()
        {
            Console.WriteLine("Enemy attack.");
        }

        /// <summary>
        /// 移动
        /// </summary>
        public void Move()
        {
            Console.WriteLine("Enemy move.");
        }
    }
}
