using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _704集_使用FileStream读写文件
{
    internal class Program
    {
        static void Test01()
        {
            //FileStream主要用于读写二进制文件
            byte[] bytesRead = new byte[1024];

            FileStream fileStreamCreat = new FileStream("Test01.txt", FileMode.Create);
            
            for (int i = 0; i < 1026; i++)
            {
                fileStreamCreat.Write(new byte[] { 97, 98 }, 0, 2);
            }
            fileStreamCreat.Close();

            FileStream fileStreamRead = new FileStream("Test01.txt", FileMode.Open);
            FileStream fileStreamWrite = new FileStream("Test01(副本).txt", FileMode.OpenOrCreate);
            while (true)
            {
                int nLenth = fileStreamRead.Read(bytesRead, 0, bytesRead.Length);
                if (nLenth == 0)
                {
                    Console.WriteLine("\n文件读取结束");
                    fileStreamRead.Close();
                    fileStreamWrite.Close();
                    break;
                }
                else
                {
                    fileStreamWrite.Write(bytesRead, 0, nLenth);
                    Console.Write(Encoding.UTF8.GetString(bytesRead, 0, nLenth));
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
