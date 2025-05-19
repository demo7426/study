using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _205集_int类型的冒泡排序
{
    internal class Program
    {
        static void Sort(int[] _Array)
        {
            bool bSwapped = false;
            int nTempvalue = -1;

            do
            {
                bSwapped = false;
                for (int i = 0; i < _Array.Length - 1; i++)
                {
                    if (_Array[i] > _Array[i + 1])
                    {
                        nTempvalue = _Array[i];
                        _Array[i] = _Array[i + 1];
                        _Array[i + 1] = nTempvalue;

                        bSwapped = true;
                    }
                }
            } while (bSwapped);
        }
        static void Test01()
        {
            var nArray = new int[] { 10, 6, 78, 4, 5, 3 };
            Sort(nArray);
            foreach (int i in nArray)
            {
                Console.Write(i + " ");
            }
            Console.WriteLine();
        }

        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
