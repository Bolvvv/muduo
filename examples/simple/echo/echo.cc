#include "examples/simple/echo/echo.h"

#include "muduo/base/Logging.h"

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

EchoServer::EchoServer(muduo::net::EventLoop* loop,
                       const muduo::net::InetAddress& listenAddr)
    : server_(loop, listenAddr, "EchoServer")
{
    server_.setConnectionCallback(
        std::bind(&EchoServer::onConnection, this, _1)
    );
    server_.setMessageCallback(
        std::bind(&EchoServer::onMessage, this, _1, _2, _3)
    );
}

void EchoServer::start(){
    server_.start();
}

void EchoServer::onConnection(const muduo::net::TcpConnectionPtr& conn){
    LOG_INFO << "EchoServer - "<<conn->peerAddress().toIpPort() << " -> "
             << conn->localAddress().toIpPort() << " is "
             << (conn->connected() ? "UP":"DOWN");
             //peerAddress()返回对方的地址
             //localAddress()返回本地的地址
}

void EchoServer::onMessage(const muduo::net::TcpConnectionPtr& conn,
                           muduo::net::Buffer* buf,
                           muduo::Timestamp time)
{
  muduo::string msg(buf->retrieveAllAsString());
  LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
           << "data received at " << time.toString();
  conn->send(msg);
}