using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _301集_数据的初始化和LINQ的第一个基础使用
{
    internal class Program
    {
        static void Test01()
        {
            //初始化武林高手
            var masterList = new List<CMartiaMasterArts>(){
            new CMartiaMasterArts(){ Id = 1, Name = "黄蓉",    Age = 18, Menpai = "丐帮", KungFuName = "打狗棒法",  Level = 9  },
            new CMartiaMasterArts(){ Id = 2, Name = "洪七公",  Age = 70, Menpai = "丐帮", KungFuName = "打狗棒法",  Level = 10 },
            new CMartiaMasterArts(){ Id = 3, Name = "郭靖",    Age = 22, Menpai = "丐帮", KungFuName = "降龙十八掌",Level = 10 },
            new CMartiaMasterArts(){ Id = 4, Name = "任我行",  Age = 50, Menpai = "明教", KungFuName = "葵花宝典",  Level = 1  },
            new CMartiaMasterArts(){ Id = 5, Name = "东方不败",Age = 35, Menpai = "明教", KungFuName = "葵花宝典",  Level = 10 },
            new CMartiaMasterArts(){ Id = 6, Name = "林平之",  Age = 23, Menpai = "华山", KungFuName = "葵花宝典",  Level = 7  },
            new CMartiaMasterArts(){ Id = 7, Name = "岳不群",  Age = 50, Menpai = "华山", KungFuName = "葵花宝典",  Level = 8  },
            new CMartiaMasterArts() { Id = 8, Name = "令狐冲", Age = 23, Menpai = "华山", KungFuName = "独孤九剑", Level = 10 },
            new CMartiaMasterArts() { Id = 9, Name = "梅超风", Age = 23, Menpai = "桃花岛", KungFuName = "九阴真经", Level = 8 },
            new CMartiaMasterArts() { Id =10, Name = "黄药师", Age = 23, Menpai = "梅花岛", KungFuName = "弹指神通", Level = 10 },
            new CMartiaMasterArts() { Id = 11, Name = "风清扬", Age = 23, Menpai = "华山", KungFuName = "独孤九剑", Level = 10 }
            };

            //初始化武学
            var kongfuList = new List<CKungFu>(){
            new CKungFu(){Id=1, Name="打狗棒法", Lethality=90},
            new CKungFu(){Id=2, Name="降龙十八掌", Lethality=95},
            new CKungFu(){Id=3, Name="葵花宝典", Lethality=100},
            new CKungFu() { Id=  4, Name = "独孤九剑", Lethality = 100 },
            new CKungFu() { Id = 5, Name = "九阴真经", Lethality = 100 },
            new CKungFu() { Id = 6, Name = "弹指神通", Lethality = 100 }
            };

            //使用LINQ表达式进行检索
            //var masterList02 = from m in masterList//检索
            //                   where m.Level > 8//判定条件
            //                   //orderby m.Age descending//descending只能针对单个字段,按照多个字段进行排序的时候这条语句不起作用
            //                   orderby m.Level,m.Age 
            //                   select m;//返回值

            //使用扩展方法进行检索
            //var masterList02 = masterList.Where(FilteringMethod);
            var masterList02 = masterList.Where(m=> m.Level > 8).OrderBy(m=>m.Age).ThenBy(m=>m.Level);//使用Lambda表达式

            foreach (var item in masterList02)
            {
                Console.WriteLine(item.ToString());
            }
        }

        static bool FilteringMethod(CMartiaMasterArts _cMartiaMasterArts)
        {
            if (_cMartiaMasterArts.Level > 8 && _cMartiaMasterArts.Menpai == "丐帮")
                return true;
            return false;
        }

        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
