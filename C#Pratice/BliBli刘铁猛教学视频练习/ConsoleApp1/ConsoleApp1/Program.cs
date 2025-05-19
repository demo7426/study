using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ConsoleApp1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            //Form form = new Form();
            //form.Text = "A Title!";
            //form.ShowDialog();
            
            CCaculator cCaculator = new CCaculator();
            Console.WriteLine(cCaculator.Add(2, 3));

            Console.WriteLine(cCaculator.SumFormXToY(1, 100));

            Console.WriteLine("");

            
            
            dynamic Value = 100;//C#对弱类型语言的模仿
            Console.WriteLine(Value);
            Value = "一个字符串";
            Console.WriteLine(Value);

            CClassInfo cClassInfo = new CClassInfo();
            cClassInfo.GetClassAttribute();
            cClassInfo.GetClassMethod();
        }
    }
   
    /// <summary>
    /// 动态访问一个类的相关信息
    /// </summary>
    class CClassInfo
    {
        //获取类属性
        public void GetClassAttribute()
        {
            Type type = typeof(Form);
            PropertyInfo[] propertyInfo = type.GetProperties();
            
            foreach (PropertyInfo property in propertyInfo)
            {
                Console.WriteLine(property.Name);
            }
            
            Console.WriteLine("");
        }

        //获取类方法
        public void GetClassMethod()
        {
            Type type = typeof(Form);
            MethodInfo[] methodInfos = type.GetMethods();

           foreach (MethodInfo method in methodInfos)
           {
                Console.WriteLine(method.Name);
           }
           Console.WriteLine("");
        }
       
    }

    class CCaculator
    {
        public int Add(int _a, int _b)
        {
            return _a + _b;
        }

        /// <summary>
        /// 返回程序当前日期
        /// </summary>
        /// <returns></returns>
        public string Today()
        {
            int nDay = DateTime.Now.Day;
            return nDay.ToString();
        }

        /// <summary>
        /// 等差数列为1的计算
        /// </summary>
        /// <param name="_Value1"></param>
        /// <param name="_Value2"></param>
        /// <returns></returns>
        public int SumFormXToY(int _Value1, int _Value2)
        {
            if (_Value1 > _Value2)//保证_Value1小于_Value2,后续程序一样可以使用
            {
                _Value1 = _Value1 + _Value2;
                _Value2 = _Value1 - _Value2;
                _Value1 = _Value1 - _Value2;
            }

            if (_Value1 == _Value2)
                return _Value1;
            else
               return _Value1 + SumFormXToY(_Value1 + 1, _Value2);
        }
    }
}
