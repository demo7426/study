using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 传值_输出_引用_数组_具名_可选参数_扩展方法
{
    internal class Program
    {
        static void Main(string[] args)
        {
            CByValuePam.Test();

            Console.WriteLine();
            COutPam.Test();

            Console.WriteLine();
            CRefPam.Test();

            Console.WriteLine();
            CArrayPam.Test();

            Console.WriteLine();
            CNamedPam cNamedPam = new CNamedPam();
            cNamedPam.Test();

            Console.WriteLine("\n扩展方法测试：");
            double dbValue = 3.1415926;
            Console.WriteLine("\t{0}", dbValue.Round(4));
        }
    }

    /// <summary>
    /// 传值参数测试:包括值类型、引用类型
    /// </summary>
    class CByValuePam
    {
        public int m_nValue { get; set; }

        CByValuePam(int _Value)
        {
            this.m_nValue = _Value;
        }

        public void AddOne(CByValuePam ByValue)
        {
            ByValue.m_nValue += 1;
        }

        public void AddOne(int _Value)
        {
            _Value += 1;
        }

        /// <summary>
        /// 传值参数的测试字段
        /// </summary>
        public static void Test()
        {
            CByValuePam cByValue = new CByValuePam(20);

            Console.WriteLine("传值参数测试_值类型:");

            int nValue = 10;
            Console.WriteLine("\t传入前：nValue = {0}", nValue);
            cByValue.AddOne(nValue);
            Console.WriteLine("\t传入后：nValue = {0}", nValue);

            Console.WriteLine("传值参数测试_引用类型:");
            Console.WriteLine("\t传入前：cByValue.m_nValue = {0}", cByValue.m_nValue);
            cByValue.AddOne(cByValue);
            Console.WriteLine("\t传入后：cByValue.m_nValue = {0}", cByValue.m_nValue);

        }
    }

    /// <summary>
    /// 输出参数测试:包括值类型、引用类型
    /// </summary>
    class COutPam
    {
        public int m_nValue { get; set; }

        COutPam(int _Value)
        {
            this.m_nValue = _Value;
        }

        public void CreateCOutPam(out COutPam OutPam)
        {
            COutPam cOutPam = new COutPam(40);
            OutPam = cOutPam;
        }

        public void OutEleven(out int _Value)
        {
            _Value = 11;
        }

        /// <summary>
        /// 输出参数的测试字段
        /// </summary>
        public static void Test()
        {
            COutPam cByValue = new COutPam(20);

            Console.WriteLine("输出参数测试_值类型:");

            int nValue = 10;
            Console.WriteLine("\t传入前：nValue = {0}", nValue);
            cByValue.OutEleven(out nValue);
            Console.WriteLine("\t传入后：nValue = {0}", nValue);

            Console.WriteLine("输出参数测试_引用类型:");
            Console.WriteLine("\t传入前：cByValue.m_nValue = {0}", cByValue.m_nValue);
            //cByValue = null;
            cByValue.CreateCOutPam(out cByValue);
            Console.WriteLine("\t传入后：cByValue.m_nValue = {0}", cByValue.m_nValue);

        }

    }

    /// <summary>
    /// 引用参数测试:包括值类型、引用类型
    /// </summary>
    class CRefPam
    {
        public int m_nValue { get; set; }

        CRefPam(int _Value)
        {
            this.m_nValue = _Value;
        }

        public void AddOne(ref CRefPam ByValue)
        {
            ByValue.m_nValue += 10;
        }

        public void AddOne(ref int _Value)
        {
            _Value += 1;
        }

        /// <summary>
        /// 引用参数的测试字段
        /// </summary>
        public static void Test()
        {
            CRefPam cRefPam = new CRefPam(20);

            Console.WriteLine("引用参数测试_值类型:");

            int nValue = 10;
            Console.WriteLine("\t传入前：nValue = {0}", nValue);
            cRefPam.AddOne(ref nValue);
            Console.WriteLine("\t传入后：nValue = {0}", nValue);

            Console.WriteLine("引用参数测试_引用类型:");
            Console.WriteLine("\t传入前：cByValue.m_nValue = {0}", cRefPam.m_nValue);
            cRefPam.AddOne(ref cRefPam);
            Console.WriteLine("\t传入后：cByValue.m_nValue = {0}", cRefPam.m_nValue);

        }
    }

    /// <summary>
    /// 数组参数测试
    /// </summary>
    class CArrayPam
    {
        private int GetSum(params int[] _ArrValue)
        {
            int nSum = 0;
            foreach (var _i in _ArrValue)
            {
                nSum += _i;
            }

            return nSum;
        }

        /// <summary>
        /// 数组参数的测试字段
        /// </summary>
        public static void Test()
        {
            CArrayPam cArrayPam = new CArrayPam();

            Console.WriteLine("数组参数测试:");
            Console.WriteLine("\t传入后：Sum = {0}", cArrayPam.GetSum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));

        }
    }

    /// <summary>
    /// 具名、可选（默认形参）参数测试
    /// </summary>
    class CNamedPam
    {
        private string m_strName { get; set; }
        private uint m_unAge { get; set; }

        private List<CNamedPam> m_listNamePam = new List<CNamedPam>();

        public CNamedPam()
        {
            m_strName = "";
            m_unAge = 0;
        }

        public CNamedPam(string _Name, uint _Age)
        {
            m_strName = _Name;
            m_unAge = _Age;
        }

        private void AddData(string _Name, uint _Age = 18)
        {
            CNamedPam cNamedPam = new CNamedPam(_Name, _Age);
            m_listNamePam.Add(cNamedPam);
        }

        /// <summary>
        /// 具名参数的测试字段
        /// </summary>
        public void Test()
        {
            CNamedPam cNamedPam = new CNamedPam();

            Console.WriteLine("具名参数测试:");

            cNamedPam.AddData(_Name:"Meixi", _Age:34);

            foreach (var item in cNamedPam.m_listNamePam)
            {
                Console.WriteLine("\t传入后：Name {0}, Age is {1}.", item.m_strName, item.m_unAge);
            }
        }
    }

    /// <summary>
    /// 扩展方法参数测试
    /// </summary>
    static class DoubleExtension
    {
        public static double Round(this double _Input, int _Digits)
        {
            return Math.Round(_Input, _Digits);
        }


    }
}
