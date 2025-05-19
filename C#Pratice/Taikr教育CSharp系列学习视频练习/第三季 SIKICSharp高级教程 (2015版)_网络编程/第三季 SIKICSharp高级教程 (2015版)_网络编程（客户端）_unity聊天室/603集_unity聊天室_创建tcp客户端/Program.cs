using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace _603集_unity聊天室_创建tcp客户端
{
    internal class Program
    {
        private static Socket clientSocket { get; set; }
        static void ReciveMsg()
        {
            int nlength = 0;
            byte[] bytes = new byte[1024];
            while (true)
            {
                nlength = clientSocket.Receive(bytes);

                if (nlength > 0)
                {
                    Console.WriteLine(Encoding.UTF8.GetString(bytes, 0, nlength));
                }

                nlength = 0;
            }
        }
        static void CreateClient()
        {
            string strContext = "";
            clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            clientSocket.Connect(new IPEndPoint(IPAddress.Parse("192.168.1.110"), 7788));

            Task task = new Task(ReciveMsg);
            task.Start();

            while (true)
            {
                strContext = Console.ReadLine();

                if (strContext.ToLower().CompareTo("eof") == 0)
                {
                    //关闭与服务器之间的连接
                    clientSocket.Shutdown(SocketShutdown.Both);
                    clientSocket.Close();
                    break;
                }

                clientSocket.Send(Encoding.UTF8.GetBytes(strContext));
            }
        }
        static void Main(string[] args)
        {
            CreateClient();
        }
    }
}
