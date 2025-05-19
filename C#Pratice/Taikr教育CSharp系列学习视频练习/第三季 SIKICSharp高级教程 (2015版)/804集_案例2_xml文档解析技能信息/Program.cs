using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace _804集_案例2_xml文档解析技能信息
{
    internal class Program
    {
        private static List<CSkillInfo> _cskillInfo = new List<CSkillInfo>();

        static void Test01()
        {
            XmlDocument xmlDocument = new XmlDocument();
            xmlDocument.Load("xml技能信息.txt");

            XmlNode xmlNodeSkillInfo = xmlDocument.FirstChild;//取出SkillInfo根结点
            XmlNode xmlNodeSkillList = xmlNodeSkillInfo.FirstChild;//取出SkillList根结点

            XmlNodeList xmlNodeListSkill = xmlNodeSkillList.ChildNodes;
            foreach (XmlNode xmlNodeSkill in xmlNodeListSkill)
            {
                CSkillInfo cSkillInfo = new CSkillInfo();

                //获取Skill属性
                XmlAttributeCollection xmlAttributeCollection = xmlNodeSkill.Attributes;
                cSkillInfo.SkillID = Int32.Parse(xmlAttributeCollection["SkillID"].Value);
                cSkillInfo.SkillEngName = xmlAttributeCollection["SkillEngName"].Value;
                cSkillInfo.TriggerType = Int32.Parse(xmlAttributeCollection["TriggerType"].Value);
                cSkillInfo.ImageFile = xmlAttributeCollection["ImageFile"].Value;
                cSkillInfo.AvailableRace = Int32.Parse(xmlAttributeCollection["AvailableRace"].Value);

                cSkillInfo.Name = xmlNodeSkill.ChildNodes[0].InnerText;

                _cskillInfo.Add(cSkillInfo);
            }

            foreach (var item in _cskillInfo)
            {
                Console.WriteLine(item.ToString());
            }
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
