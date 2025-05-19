using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _809集_使用JsonMapper跟泛型解析Json
{
    internal class CSkill
    {
        public int id { get; set; }
        public string name { get; set; }
        public int damage { get; set; }
        public override string ToString()
        {
            return this.id + " " + this.name + " " + this.damage;
        }
    }
}
