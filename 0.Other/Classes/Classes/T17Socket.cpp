//
//  T17Socket.cpp
//  T0818
//
//  Created by 薛国良 on 15/11/2.
//
//

#include "T17Socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../external/json/rapidjson.h"
#include "../external/json/document.h"
#include "../external/json/stringbuffer.h"
#include "../external/json/writer.h"

bool T17Socket::init()
{
    Layer::init();
    /*
      网络：理论七层，实际四层
     
     1.物理层   物理链路层
     2.链路（驱动）
     3.网络     网络层（ip）获取一个网络链路，通过ioctl写数据
     4.传输     传输层 (TCP, UDP)
     5.会话     应用层
     6.表示
     7.应用
     
     Socket究竟是什么
     
     EndPoint -> EndPoint
     Point -> Point
    */
    
    /* 服务器端 
        C10K connection 10K 1万
     
        1. 创建了Socket
           注意：返回值是一个int，如果返回－1表示失败(Linux直接用－1,windows下用宏INVALID_SOCKET)
        2. 将该socket绑定到端口
           注意：bind(sock, &addr, sizeof(addr))
                a.也可能失败，最可能失败是，该端口被其他Socket占用
                b.地址中，使用INADDR_ANY表示监听所有网口
        3. 监听 listen(256)
           注意：基本上不太可能失败
                参数是设置缓冲区大小的
        4. 尝试接受连接 int newSock = accept(sock, NULL, NULL);
           注意: 这个函数可能阻塞
                后两个参数指示连接的socket的ip地址和端口
                虽然这个函数是阻塞的，但是也有些情况下，该函数不阻塞并且返回－1
        5. 接收成功后返回新的socket，用新的socket通信
           recv和send
           通信：这两个函数也是阻塞的  10 10 0 send(3)
                这两个函数的返回值：
                >0 表示已经发送或者已经接受的数量
                    char buf[1024]
                    int ret = recv(sock, buf, sizeof(buf), 0);
                    int ret = send(sock, buf, sizeof(buf), 0);
                <0 表示有问题
                ==0 send不会返回这个值，
                    recv返回这个值表示对方关闭了socket
        6.任何时候，socket操作返回－1时，可以通过全局变量errno获得错误码
          int ret = accept(sock, NULL, NULL);
          if( ret == -1)
          {
            printf("%d", errno); //  linux、mac、ios、android
            WSAGetLastError // windows平台的错误码
          }
     */
    /*
     
     客户端：
     1.创建socket
       注意：创建的socket但是没有绑定时，它也是占端口的
     2.连接服务器
     3.通信（发送，接收）
     */
#if 0
    //创建
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // 发数据之前要连接服务器
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9988);
    addr.sin_addr.s_addr = inet_addr("42.121.13.248");
    
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    
    send(sock, "Hello, this is itcast", sizeof("Hello, this is itcast"), 0);
   
    char buf[1024];
    recv(sock, buf, 1024, 0);
    CCLOG("%s\n", buf);
#endif
    
#if 0
    _sprite = Sprite::create("Images/blocks.png");
    addChild(_sprite);
    _sprite->setPosition(Vec2(200, 200));
    
    auto ev = EventListenerTouchOneByOne::create();
    ev->onTouchBegan = [](Touch*, Event*){return true;};
    ev->onTouchMoved = [&](Touch* touch, Event*){
        
        Vec2 pos =touch->getLocation();
        _sprite->setPosition(pos);
        
        // 把坐标变成json格式
        rapidjson::Document doc;
        doc.SetObject();
        
        doc.AddMember("x", (int)pos.x, doc.GetAllocator());
        doc.AddMember("y", (int)pos.y, doc.GetAllocator());
        
        rapidjson::StringBuffer buf;
        rapidjson::Writer<rapidjson::StringBuffer> w(buf);
        doc.Accept(w);
        
        const char* data = buf.GetString();
        
        // 将数据发送到网络
        //创建
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        // 发数据之前要连接服务器
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9988);
        addr.sin_addr.s_addr = inet_addr("192.168.46.43");
        
        connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        
        send(sock, data, strlen(data)+1, 0);
        
        // 检测对方是否关闭服务器
        char a;
        recv(sock, &a, 1, 0);
        close(sock);
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
#endif
    
    _sprite = Sprite::create("Images/blocks.png");
    addChild(_sprite);
    _sprite->setPosition(Vec2(200, 200));
    
    _sprite2 = Sprite::create("CloseNormal.png");
    addChild(_sprite2);
    _sprite2->setPosition(Vec2(200, 200));
    
    /* 创建UDP SOCKET */
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9988);
    addr.sin_addr.s_addr = inet_addr("192.168.46.43");
    
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    
    scheduleUpdate();
    
    auto ev = EventListenerTouchOneByOne::create();
    ev->onTouchBegan = [](Touch*, Event*){return true;};
    ev->onTouchMoved = [&](Touch* touch, Event*){
        
        Vec2 pos =touch->getLocation();
        _sprite->setPosition(pos);
        
        // 把坐标变成json格式
        rapidjson::Document doc;
        doc.SetObject();
        
        doc.AddMember("x", (int)pos.x, doc.GetAllocator());
        doc.AddMember("y", (int)pos.y, doc.GetAllocator());
        
        rapidjson::StringBuffer buf;
        rapidjson::Writer<rapidjson::StringBuffer> w(buf);
        doc.Accept(w);
        
        const char* data = buf.GetString();
        
        
        // 发数据之前要连接服务器
#if 0
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9988);
        addr.sin_addr.s_addr = inet_addr("192.168.46.43");
#endif
        
      //  sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
        
      //  int ret = sendto(sock, data, (size_t)(strlen(data)+1), 0,
      //         (struct sockaddr*)&addr, (socklen_t)sizeof(addr));
        int ret = send(sock, data, strlen(data)+1, 0);
        if(ret  < 0)
        {
            CCLOG("send error");
        }
        else
        {
            CCLOG("send success");
        }
     //   sendto(sock, data, strlen(data)+1, 0);
        
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    
    return true;
}

void T17Socket::update(float)
{
    // 发数据之前要连接服务器
#if 0
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9988);
    addr.sin_addr.s_addr = inet_addr("192.168.46.43");
    
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
#endif
    
    send(sock, "1", 1, 0);
    
    char buf[1024];
    recv(sock, buf, sizeof(buf), 0);
    
    rapidjson::Document doc;
    doc.Parse<0>(buf);
    
    if(doc.GetType() != rapidjson::kArrayType &&
       doc.GetType() != rapidjson::kObjectType)
    {
        CCLOG("parse error");
        return;
    }
    
    rapidjson::Value& x = doc["x"];
    rapidjson::Value& y = doc["y"];
    if(x.GetType() != rapidjson::kNumberType
       || y.GetType() != rapidjson::kNumberType)
    {
        CCLOG("no x or no y");
        return;
    }
    
    _sprite2->setPosition(doc["x"].GetInt()+50, doc["y"].GetInt()+50);
    
    
}