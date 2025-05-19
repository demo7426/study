using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.OleDb;
using System.Data;

namespace _811集_Excel操作
{
    internal class Program
    {
        static void Test01()
        {
            string strFilePath = "装备信息.xls";
            string strCon = "Provider=Microsoft.Jet.OLEDB.4.0;" + "Data Source=" + strFilePath + ";" + 
                ";Extended Properties=\"Excel 8.0;HDR=YES;IMEX=1\"";

            //这两种strCon对应两种不同版本的excel文件
            /*string strCon = "Provider=Microsoft.ACE.OLEDB.12.0;" + "Data Source=" + strFilePath + ";" + 
                ";Extended Properties=\"Excel 12.0;HDR=YES;IMEX=1\"";*/

            //创建连接到数据源的对象
            OleDbConnection conn = new OleDbConnection(strCon);

            //打开连接
            conn.Open();
            OleDbDataAdapter oleDbDataAdapter = new OleDbDataAdapter("select * from [sheet1$]", conn);

            DataSet dataSet = new DataSet();//用于存放取出的数据
            oleDbDataAdapter.Fill(dataSet);//把取出的oleDbDataAdapter数据填充到dataSet里面

            conn.Close();//释放连接资源

            DataTableCollection dataTableCollection = dataSet.Tables;//获取当前集合中的所有表格
            DataTable dataTable = dataTableCollection[0];//因为该xls文件内部只有一张有数据的表格

            DataRowCollection dataRowCollection = dataTable.Rows;//返回一行数据的集合

            foreach (DataRow item in dataRowCollection)
            {
                for (int i = 0; i < 8; i++)
                {
                    Console.Write(item[i] + " ");
                }
                Console.WriteLine();
            }
        }
        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
