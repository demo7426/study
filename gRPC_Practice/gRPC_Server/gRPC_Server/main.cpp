/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.12
描  述: 实现一个基于gRPC的简单服务端
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

class CMyGreeterService : public Greeter::Service
{
public:
    CMyGreeterService() = default;
	~CMyGreeterService() = default;

    ::grpc::Status sayHello(::grpc::ServerContext* context, const ::Request* request, ::Response* response) override
    {
        std::ostringstream cStrStream;
        std::cout << "name = " << request->name() << ", age = " << request->age() << std::endl;

        cStrStream << "sayHello name = " << request->name() << ", age = " << request->age();
        response->set_message(cStrStream.str());

        return ::grpc::Status::OK;
    }

private:

};

static void RunServer(void)
{
    //设置服务器参数
    grpc::ServerBuilder cServerBuilder;

    //设置网络参数
    cServerBuilder.AddListeningPort("0.0.0.0:32888", grpc::InsecureServerCredentials());

    CMyGreeterService cMyGreeterService;    //设置服务函数
    cServerBuilder.RegisterService(&cMyGreeterService);

    //创建服务器
    std::unique_ptr<grpc::Server> pServer = cServerBuilder.BuildAndStart();
    pServer->Wait();
}

int main()
{
    RunServer();

    return 0;
}

