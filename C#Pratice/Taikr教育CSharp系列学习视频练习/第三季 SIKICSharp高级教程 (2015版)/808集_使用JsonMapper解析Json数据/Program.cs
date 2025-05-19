using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using LitJson;

namespace _808集_使用JsonMapper解析Json数据
{
    internal class Program
    {
        private static List<CSkill> cSkills = new List<CSkill>();
        static void Test01()
        {
            //提前引入json的dll文件(每一种高级语言都有各自对应的若干种json库)
            JsonData jsonData = JsonMapper.ToObject(File.ReadAllText("Json.txt"));

            foreach (JsonData item in jsonData)
            {
                CSkill cSkill = new CSkill();

                JsonData jsonDataId = item["id"];
                JsonData jsonDataName = item["name"];
                JsonData jsonDataDamage = item["damage"];

                cSkill.Id = int.Parse(jsonDataId.ToString());
                cSkill.Name = jsonDataName.ToString();
                cSkill.Damage = int.Parse(jsonDataDamage.ToString());

                cSkills.Add(cSkill);
            }

            foreach (var item in cSkills)
            {
                Console.WriteLine(item);
            }
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
