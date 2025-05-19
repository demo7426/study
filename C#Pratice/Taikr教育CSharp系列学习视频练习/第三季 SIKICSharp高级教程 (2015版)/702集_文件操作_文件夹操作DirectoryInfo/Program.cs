using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _702集_文件操作_文件夹操作DirectoryInfo
{
    internal class Program
    {
        private static void Test01()
        {
            DirectoryInfo directoryInfo = new DirectoryInfo("Test01");
            if (!directoryInfo.Exists)
            {
                directoryInfo.Create();
            }

            Console.WriteLine(directoryInfo.FullName);
            Console.WriteLine(directoryInfo.ToString());
            Console.WriteLine(((int)directoryInfo.Attributes));
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadLine();
        }
    }
}
