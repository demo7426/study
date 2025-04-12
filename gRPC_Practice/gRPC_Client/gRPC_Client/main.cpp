/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.12
描  述: 实现一个基于gRPC的简单客户端
备  注:
修改记录:

  1.  日期: 2025.04.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <iostream>

#include "greeter.grpc.pb.h"
#include "grpcpp/grpcpp.h"

static void RunClient(void)
{
    //构建远程链接通道
    std::shared_ptr<grpc::Channel> pcChannel = grpc::CreateChannel("127.0.0.1:32888", grpc::InsecureChannelCredentials());

    //创建远程调用代理
    std::unique_ptr< Greeter::Stub> pcStub = Greeter::NewStub(pcChannel);

    Request cRequest;
    Response cResponse;

    cRequest.set_name("张三");
    cRequest.set_age(18);
     
    for (int i = 0; i < 100000; i++)
    {
        grpc::ClientContext cClientContext;     //grpc::ClientContext 是一次性使用对象，不能在多个 RPC 调用中复用

        cRequest.set_age(i);

        std::cout << "i = " << i << ", ";
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        grpc::Status cStatus = pcStub->sayHello(&cClientContext, cRequest, &cResponse);
        if (cStatus.ok())
        {
            std::cout << "Call success:" << cResponse.message() << std::endl;
        }
        else
        {
            std::cout << "Call failure:" << cStatus.error_code() << ", " << cStatus.error_message() << std::endl;
        }
    }
}

int main()
{
    RunClient();

    return 0;
}

