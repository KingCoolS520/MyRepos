//
//  T19Http.cpp
//  T0818
//
//  Created by 薛国良 on 15/11/5.
//
//

#include "T19Http.h"


bool T19Http::init()
{
    Layer::init();
    
    /* 单例 */
    HttpClient* client = HttpClient::getInstance();
    
    
   
#if 0
    // HTTPclient第一个用途，下载文件
    
    HttpRequest* req = new HttpRequest;
    
    // 设置请求目标
    req->setUrl("http://192.168.46.43/aaa.html");
    // 设置请求类型
    req->setRequestType(HttpRequest::Type::GET);
    // 设置回调函数
    req->setResponseCallback(CC_CALLBACK_2(T19Http::response, this));
    
    client->send(req);
    
    req->release();
#endif
    
    Sprite* sprite = Sprite::create("btn-a-0.png");
    addChild(sprite);
    sprite->setPosition(200, 200);
    
    HttpRequest* req = new HttpRequest;
    
    // 设置请求目标
    req->setUrl("http://192.168.46.43/cgi-bin/a.out?name=aaa.png");
    // 设置请求类型
    req->setRequestType(HttpRequest::Type::POST);
    // 设置回调函数
    req->setResponseCallback(CC_CALLBACK_2(T19Http::response, this));
   // req->setHeaders(std::vector<std::string> pHeaders)
  //  req->setTag(<#const char *tag#>)
    
    // 如果是POST方法，还可以通过setRequestData将额外的数据发送的网络
    long fileSize = FileUtils::getInstance()->getFileSize("Hello.png");
    char* p = new char[fileSize];
    
    FILE* file = fopen(FileUtils::getInstance()->fullPathForFilename("Hello.png").c_str(), "r");
    
    fread(p, fileSize, 1, file);
    
    req->setRequestData(p, fileSize);
    fclose(file);
    
    client->send(req);
    
    req->release();
    
    pthread_t id = pthread_self();
    CCLOG("req :%d", (int)(intptr_t)id);
    
    return true;
}

void T19Http::response(cocos2d::network::HttpClient *client,
                       cocos2d::network::HttpResponse *resp)
{
  //  resp->getHttpRequest()->getTag();
    
    pthread_t id = pthread_self();
    CCLOG("resp: %d", (int)(intptr_t)id);

    long code = resp->getResponseCode();
    CCLOG("response error code is %d", (int)code);

#if 0
    std::vector<char>* data = resp->getResponseData();
    std::string str;
    str.resize(data->size());
    std::copy(data->begin(), data->end(), str.begin());
    CCLOG("%s\n", str.c_str());
#endif
    
  //  CCLOG("%s\n", resp->getResponseDataString());
    
#if 0
    // 下载文件的响应
    // 数据
    std::vector<char>* data = resp->getResponseData();
   // const char* data = resp->getResponseDataString();
    
    FILE* f = fopen("/Users/xueguoliang/aaa.html", "wb+");
    for(auto it = data->begin(); it!= data->end(); ++it)
    {
        char ch = *it;
        fwrite(&ch, 1, 1, f);
    }
    fclose(f);
#endif
    
}



