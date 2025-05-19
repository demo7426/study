using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp_Constructor_1
{
    internal class Program
    {
        static void Main(string[] args)
        {
            CStudent cStudent = new CStudent();
            Console.WriteLine("Id = {0}\t", cStudent.m_nId);
            Console.WriteLine("Name = {0}\t", cStudent.m_nName);

            Console.WriteLine();

            CStudent cStudent2 = new CStudent(1, "Mr Wang");
            Console.WriteLine("Id = {0}\t", cStudent2.m_nId);
            Console.WriteLine("Name = {0}\t", cStudent2.m_nName);
        }
    }

    class CStudent
    {
        public CStudent()
        {

        }

        public CStudent(int _Id, string _Name)
        {
            this.m_nId = _Id;
            this.m_nName = _Name;
        }

        public int m_nId;
        public string m_nName;
        
    }
}
