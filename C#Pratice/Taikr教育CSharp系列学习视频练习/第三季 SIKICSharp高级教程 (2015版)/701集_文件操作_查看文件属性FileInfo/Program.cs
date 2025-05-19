using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _701集_文件操作_查看文件属性FileInfo
{
    internal class Program
    {
        static void Test01()
        {
            FileInfo fileInfo = new FileInfo("TextFile1.txt");

            Console.WriteLine(fileInfo.Exists);
            Console.WriteLine(fileInfo.FullName);
            Console.WriteLine(fileInfo.Length);

            fileInfo.Delete();

            //创建文件
            FileInfo fileInfo1 = new FileInfo("1.txt");
            if (!fileInfo1.Exists)
            {
                fileInfo1.Create();
            }
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
