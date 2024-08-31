#pragma once

//////////////////////////////////////////////外部接口//////////////////////////////////////////////

// 创建监听套接字
int InitListenFd(unsigned short _Port);

//启动epoll
int EpollRun(int _ServerFd);

////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////内部接口//////////////////////////////////////////////

//连接客户端
void* AcceptClient(void* _Arg);

//接收客户端的请求
void* RecvHttpRequest(void* _Arg);

//解析http请求行数据
int ParseHttpRequestLine(const char* _Line, int _ClientFd);

//发送目录给指定的文件描述符
int SendDir(const char* _DirPath, int _ClientFd);

//发送文件给指定的文件描述符
int SendFile(const char* _FilePath, int _ClientFd);

//发送http状态行和响应头
int SendHeadMsg(int _ClientFd, int _Status, const char* _Descr, const char* _Type, int _Length);

//根据文件类型获取文件描述信息
const char* AccordFileType_GetFileMsg(const char* _FileType);

//将字符转换为整形数
int HexToDec(char _C);

/// <summary>
/// 解码，将http中的汉字数据转换为linux可识别的字符
/// </summary>
/// <param name="_Des">传出字符串</param>
/// <param name="_Src">传入字符串</param>
void DecodeMsg(char* _Des, char* _Src);

////////////////////////////////////////////////////////////////////////////////////////////////////

