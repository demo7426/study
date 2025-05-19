using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Server
{
    internal class Program
    {
        /// <summary>
        /// 创建一个服务器
        /// </summary>
        static void Test01()
        {
            int nFreq = 0;

            //创建Socket
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            IPAddress iPAddress = new IPAddress(new byte[] { 192, 168, 1, 110 });
            EndPoint endPoint = new IPEndPoint(IPAddress.Any, 7788);
            //绑定IP和端口号(端口号在0--60000之间选择空闲的)
            socket.Bind(endPoint);

            //最多连接100个客户端
            socket.Listen(100);

            //阻塞当前线程，直到有一个客户端的连接过来，再执行下面代码
            Socket socket1 = socket.Accept();

            Action action = () =>
            {
                while (true)
                {
                    //lock (socket1)
                    {
                        socket1.Send(Encoding.UTF8.GetBytes("服务器发送第" + ++nFreq + "一条消息"));
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
                    //lock(socket1)
                    {
                        nLength = socket1.Receive(bytes);
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
