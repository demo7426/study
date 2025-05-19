using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _206集_拓展的通用的冒泡排序的方法
{
    internal class Program
    {
        static void CommonSort<T>(T[] _DataArray, Func<T, T, bool> _Func)
        {
            bool bSwapped = false;
            T nTempvalue;

            do
            {
                bSwapped = false;
                for (int i = 0; i < _DataArray.Length - 1; i++)
                {
                    if (_Func(_DataArray[i], _DataArray[i + 1]))
                    {
                        nTempvalue = _DataArray[i];
                        _DataArray[i] = _DataArray[i + 1];
                        _DataArray[i + 1] = nTempvalue;

                        bSwapped = true;
                    }
                }
            } while (bSwapped);

        }

        static void Test01()
        {
            CEmployee[] cEmployee = new CEmployee[]
            {
                new CEmployee("meixi", 20000),
                new CEmployee("crisi", 10000),
                new CEmployee("laiwan", 11000)
            };
            CommonSort(cEmployee, CEmployee.CompareTo);

            foreach (var item in cEmployee)
            {
                Console.WriteLine(item.ToString());
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
