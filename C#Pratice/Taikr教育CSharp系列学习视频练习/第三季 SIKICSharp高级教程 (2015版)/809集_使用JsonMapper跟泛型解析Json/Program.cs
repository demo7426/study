using LitJson;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _809集_使用JsonMapper跟泛型解析Json
{
    internal class Program
    {
        private static List<CSkill> cSkills = new List<CSkill>();
        static void Test01()
        {
            //提前引入json的dll文件(每一种高级语言都有各自对应的若干种json库)
            //使用泛型进行解析，字段或者属性名称必须和文本内部元素名称一样
            CMonster cMonster = JsonMapper.ToObject<CMonster>(File.ReadAllText("Json.txt"));
            Console.WriteLine(cMonster);

            Console.WriteLine();
            CMonster cMonster1 = new CMonster { Age = 10, Level = 80, Name = "nazha" };
            Console.WriteLine(JsonMapper.ToJson(cMonster1));
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
