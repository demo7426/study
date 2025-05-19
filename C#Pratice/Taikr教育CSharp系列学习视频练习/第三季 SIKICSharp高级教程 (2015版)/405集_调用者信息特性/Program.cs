using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace _405集_调用者信息特性
{
    internal class Program
    {
        static void PrintfOut(string _strContext, [CallerFilePath] string _FilePath = "", [CallerLineNumber]int _LineNum = 0, 
            [CallerMemberName] string _MemberName = "")
        {
            Console.WriteLine(_strContext);
            Console.WriteLine(_FilePath);
            Console.WriteLine(_LineNum);
            Console.WriteLine(_MemberName);
        }

        static void Main(string[] args)
        {
            PrintfOut("Hello world.");
            Console.ReadKey();
        }
    }
}
