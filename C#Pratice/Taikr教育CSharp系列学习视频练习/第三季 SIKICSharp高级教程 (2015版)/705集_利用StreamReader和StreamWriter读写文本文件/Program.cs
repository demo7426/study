using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace _705集_利用StreamReader和StreamWriter读写文本文件
{
    internal class Program
    {
        static void Test01()
        {
            StreamReader streamReader = new StreamReader("TextFile1.txt");
            StreamWriter streamWriter  = new StreamWriter("TextFile1(副本).txt");

            while (true)
            {
                string strReadContent = streamReader.ReadLine();
                if (strReadContent is null)
                {
                    streamReader.Close();
                    streamWriter.Close();
                    break;
                }
                else
                {
                    streamWriter.WriteLine(strReadContent);
                    Console.WriteLine(strReadContent);
                }
            }
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
