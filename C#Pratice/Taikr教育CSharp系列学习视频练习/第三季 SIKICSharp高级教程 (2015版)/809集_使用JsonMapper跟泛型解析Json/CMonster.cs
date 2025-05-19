using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _809集_使用JsonMapper跟泛型解析Json
{
    internal class CMonster
    {
        public string Name { get; set; }
        public int Level { get; set; }
        public int Age { get; set; }

        public List<CSkill> SkillList { get; set; }

        public override string ToString()
        {
            string strRtnContext = "";
            strRtnContext += this.Name + " " + this.Level + " " + this.Age + "\n";

            foreach (CSkill c in this.SkillList)
            {
                strRtnContext += c.ToString();
            }
            return strRtnContext;
        }
    }
}
