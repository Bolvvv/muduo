#include "examples/simple/echo/echo.h"

#include "muduo/base/Logging.h"
#include "muduo/net/EventLoop.h"

#include <unistd.h>

int main()
{
    LOG_INFO << "pid = " << getpid();//记录日志
    muduo::net::EventLoop loop;//初始化loop事件
    muduo::net::InetAddress listenAddr(2007);//监听2007端口
    EchoServer server(&loop, listenAddr);//创建服务器，绑定loop和监听地址
    server.start();//启动服务器
    loop.loop();//启动循环监听
}