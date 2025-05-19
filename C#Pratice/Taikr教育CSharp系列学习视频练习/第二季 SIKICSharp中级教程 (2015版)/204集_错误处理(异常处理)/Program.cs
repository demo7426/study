using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _204集_错误处理_异常处理_
{
    internal class Program
    {
        static void Test01()
        {
            //catch可以有0个或多个，finally可以有0个或1个；
            //catch、finally可以同时存在，但是最少存在其中一个。
            try
            {
                int[] nArray = new int[] { 10, 11, 12 };
                int nValue = nArray[nArray.Length];

            }
            catch (IndexOutOfRangeException ex)
            {
                Console.WriteLine("Array out of range.");
                //throw new IndexOutOfRangeException("Array out of range.");
            }
            catch(NullReferenceException e)
            {
                Console.WriteLine("执行catch NullReferenceException语句块.");
            }
            finally
            {
                Console.WriteLine("执行finally语句块.");
            }

        }

        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
