using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _803集_xml文档解析
{
    internal class CSkill
    {
        public int ID { get; set; } 
        public string Name { get; set; }
        public string Language { get; set; }
        public UInt32 Damage { get; set; }

        public override string ToString()
        {
            return "ID：" + this.ID + "\tName：" + this.Name + "\tLanguage：" + this.Language + "\tDamage：" + this.Damage;
        }
    }
}
