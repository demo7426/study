using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _804集_案例2_xml文档解析技能信息
{
    internal class CSkillInfo
    {
        public string Name { get; set; }
        public Int32 SkillID { get; set; }
        public string SkillEngName { get; set; }
        public Int32 TriggerType { get; set; }
        public string ImageFile { get; set; }
        public Int32 AvailableRace { get; set; }

        public override string ToString()
        {
            return "Name：" + this.Name + "\tSkillID：" + this.SkillID + "\tSkillEngName：" + this.SkillEngName +
                "\tTriggerType：" + this.TriggerType + "\tImageFile：" + this.ImageFile + "\tAvailableRace：" + this.AvailableRace;
        }
    }
}
