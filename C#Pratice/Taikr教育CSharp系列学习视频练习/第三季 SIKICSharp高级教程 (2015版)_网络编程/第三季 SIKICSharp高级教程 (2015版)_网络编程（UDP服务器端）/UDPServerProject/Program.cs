using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace UDPServerProject
{
    internal class Program
    {
        private static Socket _UdpServerSocket { get; set; }
        /// <summary>
        /// 创建UDP服务器端
        /// </summary>
        static void CreateUDPServer()
        {
            _UdpServerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

            _UdpServerSocket.Bind(new IPEndPoint(IPAddress.Parse("192.168.1.110"), 7788));

            Thread thread = new Thread(ReciveMsg);
            thread.Start();
        }

        static void ReciveMsg()
        {
            byte[] bytes = new byte[1024];
            EndPoint endPoint = new IPEndPoint(IPAddress.Any, 0);
            int nLength = 0;

            while (true)
            {
                nLength = _UdpServerSocket.ReceiveFrom(bytes, ref endPoint);

                if (nLength > 0)
                {
                    if (Encoding.UTF8.GetString(bytes, 0, nLength).ToLower() == "close server")//提供给客户端一个指令，可以关闭服务器
                    {
                        _UdpServerSocket.Close();
                        break;
                    }

                    Console.WriteLine("从IP：{0}, 端口号：{1}, 接收到：{2}", (endPoint as IPEndPoint).Address.ToString(),
                        (endPoint as IPEndPoint).Port.ToString(), Encoding.UTF8.GetString(bytes, 0, nLength));
                }
            }
        }

        static void Main(string[] args)
        {
            CreateUDPServer();
        }
    }
}
