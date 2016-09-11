//
//  T18Thread.cpp
//  T0818
//
//  Created by 薛国良 on 15/11/4.
//
//

#include "T18Thread.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/fcntl.h>

#include "../external/json/rapidjson.h"
#include "../external/json/document.h"
#include "../external/json/stringbuffer.h"
#include "../external/json/writer.h"


void* thread_main(void* arg)
{
    /* 不停得向服务器发送请求，得到最新的数据，得到数据放到T18Thread::_pos */
    T18Thread* p = (T18Thread*)arg;
    
    while(1)
    {
        usleep(1000*16);
        
        send(p->sock, "1", 1, 0);
        char buf[1024];
        
        CCLOG("prepare to recv");
        recv(p->sock, buf, sizeof(buf), 0);
        CCLOG("recv data ok");
    
        rapidjson::Document doc;
        doc.Parse<0>(buf);
        if(doc.GetType() != rapidjson::kObjectType)
        {
            CCLOG("doc error");
            continue;
        }
        
    
        rapidjson::Value& x = doc["x"];
        rapidjson::Value& y = doc["y"];
        if(x.GetType() != rapidjson::kNumberType
           || y.GetType() != rapidjson::kNumberType)
        {
            CCLOG("x y error");
            continue;
        }
    
        pthread_mutex_lock(&p->_mutex);
        p->_pos.x = x.GetInt()+50;
        p->_pos.y = y.GetInt()+50;
        pthread_mutex_unlock(&p->_mutex);
        
        // 修改渲染树。。。
        // p->_sp2->setPosition(const cocos2d::Vec2 &pos);
    }
    return nullptr;
}

void T18Thread::update(float)
{
    pthread_mutex_lock(&_mutex);
    _sp2->setPosition(_pos);
    pthread_mutex_unlock(&_mutex);
}

bool T18Thread::init()
{
    Layer::init();
    
    // Thread，一个新的执行序列
    // 线程之间的资源是共享的, IOS, MAC, Android
    
    /*
        1. pthread_create 创建线程
        2. pthread_join 等待线程结束，回收线程
        3. pthread_self 获得调用该函数的执行线程信息
     
        4. pthread_mutex_init
        5. pthread_mutex_lock
        6. pthread_mutex_unlock
        7. pthread_mutex_destroy

        类型
        pthread_t
        pthread_mutex_t
     
        线程等待
        pthread_cond_wait
        sem_wait // semaphore 信号量
     */
    
    /* 线程数量多少比较合适 */
    
    _sp1 = Sprite::create("Images/blocks.png");
    addChild(_sp1);
    _sp1->setPosition(200, 200);
    
    _sp2 = Sprite::create("Images/blocks.png");
    addChild(_sp2);
    _sp2->setPosition(200, 200);
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.46.43");
    addr.sin_port = htons(9988);
    
    int flag = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flag|O_NONBLOCK);
    
    /* UDP的connect跟服务器没关系 */
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    
    auto ev = EventListenerTouchOneByOne::create();
    ev->onTouchBegan = [](Touch*, Event*){return true;};
    ev->onTouchMoved = [&](Touch* t, Event*){
        Vec2 pos = t->getLocation();
        _sp1->setPosition(pos);
        
        rapidjson::Document doc;
        doc.SetObject();
        
        doc.AddMember("x", (int)pos.x, doc.GetAllocator());
        doc.AddMember("y", (int)pos.y, doc.GetAllocator());
        
        // 将json格式文档打包
        rapidjson::StringBuffer buf;
        rapidjson::Writer<rapidjson::StringBuffer> w(buf);
        doc.Accept(w);
        
        const char* str = buf.GetString();
        
        send(sock, str, strlen(str)+1, 0);
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    
    // 启动定时器
    scheduleUpdate();
    
    // 线程
    pthread_mutex_init(&_mutex, NULL);
    pthread_t tid;
    pthread_create(&tid, nullptr, thread_main, this);
    
#if 0
    pthread_t tid;
    void*p;
    int ret = pthread_create(&tid, nullptr, thread_main, p);
    if(ret == 0)
    {
        CCLOG("thread create success");
    }
    for(int i=0; i<10000; ++i)
        CCLOG("main = %d", i);
#endif
    return true;
}