using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace _803集_xml文档解析
{
    internal class Program
    {
        static void Test01()
        {
            List<CSkill> list = new List<CSkill>();

            XmlDocument xmlDocument = new XmlDocument();

            xmlDocument.Load("TextFile1.txt");
            XmlNode xmlNode = xmlDocument.FirstChild;//获取第一个根节点

            XmlNodeList xmlNodeList = xmlNode.ChildNodes;//获取第一个根节点的所有子节点

            foreach (XmlNode xmlNode2 in xmlNodeList)
            {
                CSkill cskill = new CSkill();

                XmlNodeList xmlNodeList1 = xmlNode2.ChildNodes;//获取skill下所有子节点

                foreach (XmlNode xmlNode3 in xmlNodeList1)
                {
                    if (xmlNode3.Name == "id")
                        cskill.ID = int.Parse(xmlNode3.InnerText);
                    else if (xmlNode3.Name == "name")
                    {
                        cskill.Name = xmlNode3.InnerText;
                        cskill.Language = xmlNode3.Attributes[0].Value;
                    }
                    else if (xmlNode3.Name == "damage")
                        cskill.Damage = uint.Parse(xmlNode3.InnerText);

                }
                list.Add(cskill);
            }

            foreach (var item in list)
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
