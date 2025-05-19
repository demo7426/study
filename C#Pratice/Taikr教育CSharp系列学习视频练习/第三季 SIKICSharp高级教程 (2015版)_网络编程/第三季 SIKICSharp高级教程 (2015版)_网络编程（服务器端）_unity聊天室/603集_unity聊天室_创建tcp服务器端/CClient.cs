using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace _603集_unity聊天室_创建tcp服务器端
{
    internal class CClient
    {
        private static List<Socket> socketList = new List<Socket>();
        private Socket _Socket { get; set; }
        public CClient(Socket socket)
        {
            this._Socket = socket;

            socketList.Add(socket);
            Action action = new Action(ReciveMsg);
            action.BeginInvoke(null, null);
        }

        /// <summary>
        /// 接受客户端发过来的消息
        /// </summary>
        private void ReciveMsg()
        {
            byte[] bytes = new byte[1024];
            while (true)
            {
                //判定客户端是否断开连接
                if (_Socket.Poll(10, SelectMode.SelectRead))
                {
                    socketList.Remove(_Socket);
                    _Socket.Close();
                    break;
                }

                try
                {
                    int length = _Socket.Receive(bytes);

                    //向各个客户端分发消息
                    if (length > 0)
                    {
                        foreach (var item in socketList)
                        {
                            if (item != _Socket)
                            {
                                byte[] bytes1 = new byte[length];
                                Buffer.BlockCopy(bytes, 0, bytes1, 0, length);
                                item.Send(bytes1);
                            }
                                
                        }
                    }

                    Console.WriteLine(Encoding.UTF8.GetString(bytes, 0, length));
                }
                catch (Exception)
                {
                    socketList.Remove(_Socket);
                    Console.WriteLine("客户端强行断开连接.");
                }
            }

        }

    }
}
