using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _703集_使用File读写文件
{
    internal class Program
    {
        static void Test01()
        {
            string strFilePath = "Test01.txt";
            File.WriteAllText(strFilePath, "1\n22\n333");

            Console.WriteLine(File.ReadAllText(strFilePath));
            string[] strings = File.ReadAllLines(strFilePath);

            foreach (var item in strings)
            {
                Console.WriteLine(item);
            }
            
            byte[] bytes = File.ReadAllBytes("3.LINQ.png");
            File.WriteAllBytes("3.LINQ(副本).png", bytes);
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
