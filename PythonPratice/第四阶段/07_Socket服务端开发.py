"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	07_Socket服务端开发.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.17
描  述: Socket服务端开发
备  注:
修改记录:

  1.  日期: 2025.07.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import socket

sock_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock_server.bind(('127.0.0.1', 32888))

sock_server.listen(1)

conn, addr = sock_server.accept()

print(f"接收到{addr}客户端的链接")

while True:
    try:
        data = conn.recv(1024)

        print(data.decode("gb2312"))

        if data:
            conn.send(data)

        continue
    except ConnectionResetError as e:
        print(e)
    finally:
        conn.close()
        break

sock_server.close()