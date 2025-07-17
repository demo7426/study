"""
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	08_Socket客户端开发.py
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.07.17
描  述: Socket客户端开发
备  注:
修改记录:

  1.  日期: 2025.07.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0
"""

import socket

sock_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock_client.connect(('127.0.0.1', 32888))

while True:
    data = input("发送:")

    if data == "exit":
        break

    sock_client.send(data.encode('gb2312'))

    data = sock_client.recv(1024).decode('gb2312')
    print(f"接收：{data}")

sock_client.close()