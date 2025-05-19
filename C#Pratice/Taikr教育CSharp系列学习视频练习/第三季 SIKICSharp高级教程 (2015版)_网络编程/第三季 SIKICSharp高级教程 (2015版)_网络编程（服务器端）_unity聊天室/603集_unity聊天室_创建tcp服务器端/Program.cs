using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace _603集_unity聊天室_创建tcp服务器端
{
    internal class Program
    {
        

        static void CreateServer()
        {
            Socket serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            IPAddress iPAddress = new IPAddress(new byte[] { 192, 168, 1, 110 });
            EndPoint endPoint = new IPEndPoint(iPAddress, 7788);
            serverSocket.Bind(endPoint);

            serverSocket.Listen(100);

            while (true)
            {
                Socket clientSocket = serverSocket.Accept();

                CClient cClient = new CClient(clientSocket);
                
            }
        }
        static void Main(string[] args)
        {
            CreateServer();
        }
    }
}
