using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _808集_使用JsonMapper解析Json数据
{
    internal class CSkill
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Damage { get; set; }
        public override string ToString()
        {
            return this.Id + " " + this.Name + " " + this.Damage;
        }
    }
}
