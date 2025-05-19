using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 字段_属性_索引器_常量
{
    internal class Program
    {
        static void Main(string[] args)
        {
            for (uint i = 0; i < 100; i++)
            {
                new CStudent(18 + i % 10, 60 + i % 40);
            }

            CStudent.ReportAverageAge();
            CStudent.ReportAverageScore();

            Console.WriteLine();

            CTeacher cTeacher = new CTeacher();
            try
            {
                cTeacher.M_nAge = 18;
                Console.WriteLine(cTeacher.M_nAge);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                throw;
            }


            CStudentDictionary cStudentDictionary = new CStudentDictionary();
            try
            {
                cStudentDictionary["math"] = 80;
                cStudentDictionary["math"] = 90;
                Console.WriteLine(cStudentDictionary["math"]);

                cStudentDictionary["english"] = null;          
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                throw;
            }
        }
    }

    class CStudent//字段
    {
        public uint m_unAge = 0;//年龄
        public uint m_unScore = 0;//分数

        private static uint m_unTotalAge = 0;//总年龄 
        private static uint m_unTotalScore = 0;//总分数
        private static uint m_unStudentCount = 0;//学生总人数

        public CStudent()
        {
            m_unStudentCount++;
        }

        public CStudent(uint nAge, uint nScore)
        {
            m_unAge = nAge;
            m_unScore = nScore;

            m_unTotalAge += m_unAge;
            m_unTotalScore += m_unScore;

            m_unStudentCount++;
        }

        public static void ReportAverageAge()//获取平均年龄
        {
            Console.WriteLine(m_unTotalAge / m_unStudentCount);
        }

        public static void ReportAverageScore()//获取平均分数
        {
            Console.WriteLine(m_unTotalScore / m_unStudentCount);
        }
    }

    class CTeacher//属性
    {
        private int m_nAge;

        public int M_nAge
        {
            get { return m_nAge; }
            set 
            {
                if (value >= 0 && value <= 150)
                    m_nAge = value;
                else
                {
                    throw new Exception("Teacher's age overflow!");
                }
            }
        }

    }

    class CStudentDictionary
    {
        /// <summary>
        /// 学科分数
        /// </summary>
        private Dictionary<string, int> m_dicSubjectScore  = new Dictionary<string, int>();

        public int? this[string SubjectScore]
        {
            get 
            {
                if (this.m_dicSubjectScore.ContainsKey(SubjectScore))//判断字典内部是否已经有该键值
                {
                    return this.m_dicSubjectScore[SubjectScore];
                }
                else
                {
                    return null;
                }
            }
            set 
            {
                if (value.HasValue == false)//判断传入的参数是否为空
                {
                    throw new Exception(SubjectScore + "'s score cannot be null.");
                }

                if (this.m_dicSubjectScore.ContainsKey(SubjectScore))//判断字典内部是否已经有该键值
                {
                    this.m_dicSubjectScore[SubjectScore] = value.Value;
                }
                else
                {
                    m_dicSubjectScore.Add(SubjectScore, value.Value);
                }
            }
        }



    }
}
