using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace OperatorProject_01
{
    internal class Program
    {
        static void Main(string[] args)
        {
           
            //CPerson.Test01();
            //COperator_02.Test01();

            CStone cStone = new CStone();
            cStone.m_unAge = 5000;

            CMonkey cMonkey = (CMonkey)cStone;
            Console.WriteLine(cMonkey.m_unAge);
        }
    }

    /// <summary>
    /// 操作符是方法的一种简化
    /// </summary>
    class CPerson
    {
        /// <summary>
        /// 该类的测试方法
        /// </summary>
        public static void Test01()
        {
            CPerson cPerson_01 = new CPerson();
            cPerson_01.m_strName = "Meixi";

            CPerson cPerson_02 = new CPerson();
            cPerson_02.m_strName = cPerson_01.m_strName + "'s wife";

            List<CPerson> list = cPerson_01.GetMarry(cPerson_01, cPerson_02);

            foreach (var item in list)
            {
                Console.WriteLine(item.m_strName);
            }


            cPerson_01.m_strName = "Cristiano";
            cPerson_02.m_strName = cPerson_01.m_strName + "'s wife";

            list = cPerson_01 + cPerson_02;

            Console.WriteLine("");
            foreach (var item in list)
            {
                Console.WriteLine(item.m_strName);
            }
        }

        /// <summary>
        /// 名称     
        /// </summary>
        public string m_strName;

        public List<CPerson> GetMarry(CPerson _Person_01, CPerson _Person_02)
        {
            List<CPerson> list = new List<CPerson>();
            list.Add(_Person_01);
            list.Add(_Person_02);

            for (int i = 0; i < 10; i++)
            {
                CPerson cPerson = new CPerson();
                cPerson.m_strName = _Person_01.m_strName + "&" + _Person_02.m_strName + "的第" + (i + 1) + "个孩子";
                list.Add(cPerson);
            }

            return list;
        }

        public static List<CPerson> operator +(CPerson _Person_01, CPerson _Person_02)
        {
            List<CPerson> list = new List<CPerson>();
            list.Add(_Person_01);
            list.Add(_Person_02);

            for (int i = 0; i < 10; i++)
            {
                CPerson cPerson = new CPerson();
                cPerson.m_strName = _Person_01.m_strName + "&" + _Person_02.m_strName + "的第" + (i + 1) + "个孩子";
                list.Add(cPerson);
            }

            return list;
        }
    }

    class COperator_02
    {
        public static void Test01()
        {
            Console.WriteLine("");
            foreach (var c in typeof(Form).GetMethods())
            {
                Console.WriteLine(c.Name);
            }

            new Form() { Text = "Hello", FormBorderStyle = FormBorderStyle.SizableToolWindow }.ShowDialog();

            object value = default(int);//default默认值

            int nValue = int.MinValue;
            nValue = checked(-nValue);//checked()检测数据是否越界    
            nValue = unchecked(-nValue);//unchecked()不检测数据是否越界    
        }
    }

    class CMonkey
    {
        /// <summary>
        /// 年龄
        /// </summary>
        public UInt32 m_unAge;
    }

    class CStone
    {
        /// <summary>
        /// 年龄
        /// </summary>
        public UInt32 m_unAge;

        //public static implicit operator CMonkey(CStone cStone)隐式类型转换
        public static explicit operator CMonkey(CStone cStone)//显示类型转换
        {
            CMonkey cMonkey = new CMonkey();
            cMonkey.m_unAge = cStone.m_unAge / 100;
            return cMonkey;
        }
    }

}
