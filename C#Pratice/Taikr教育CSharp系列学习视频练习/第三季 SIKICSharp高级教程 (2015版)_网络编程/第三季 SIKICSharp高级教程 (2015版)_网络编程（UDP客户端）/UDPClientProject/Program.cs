using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace UDPClientProject
{
    internal class Program
    {
        private static Socket _UdpClientSocket { get; set; }
        static void CreateClient()
        {
            _UdpClientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

            Task task = new Task(SendMsg);
            
            task.Start();
            task.Wait();
        }

        static void SendMsg()
        {
            string strInputContext = "";
            while (true)
            {
                if (strInputContext.ToLower() == "close client")
                {
                    _UdpClientSocket.Shutdown(SocketShutdown.Both);
                    _UdpClientSocket.Close();
                    break;
                }

                strInputContext = Console.ReadLine();

                _UdpClientSocket.SendTo(Encoding.UTF8.GetBytes(strInputContext), 
                    new IPEndPoint(IPAddress.Parse("192.168.1.110"), 7788));
            }
        }
        static void Main(string[] args)
        {
            CreateClient();
        }
    }
}
