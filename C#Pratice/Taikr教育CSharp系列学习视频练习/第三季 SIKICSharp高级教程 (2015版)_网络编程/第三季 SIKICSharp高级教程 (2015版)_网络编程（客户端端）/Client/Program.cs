using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Client
{
    internal class Program
    {
        static void Test01()
        {
            int nFreq = 0;

            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            IPAddress iPAddress = new IPAddress(new byte[] { 192, 168, 1, 110 });
            EndPoint endPoint = new IPEndPoint(iPAddress, 7788);
            socket.Connect(endPoint);

            Action action = () =>
            {
                while (true)
                {
                    //lock (socket)
                    {
                        socket.Send(Encoding.UTF8.GetBytes("客户端发送第" + ++nFreq + "一条消息"));
                    }
                    Thread.Sleep(1);
                }
            };

            Action action1 = () =>
            {
                byte[] bytes = new byte[1024];
                int nLength = 0;
                while (true)
                {
                    //lock (socket)
                    {
                        nLength = socket.Receive(bytes);
                        Console.WriteLine(Encoding.UTF8.GetString(bytes, 0, nLength));
                    }
                    Thread.Sleep(1);
                }
            };

            action.BeginInvoke(null, null);
            action1.BeginInvoke(null, null);
        }

        static void Main(string[] args)
        {
            Test01();
            Console.ReadKey();
        }
    }
}
