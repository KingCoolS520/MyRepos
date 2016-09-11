//
//  T16IO.cpp
//  T0818
//
//  Created by 薛国良 on 15/11/1.
//
//

#include "T16IO.h"
#include "../external/tinyxml2/tinyxml2.h"
#include "../external/json/rapidjson.h"
#include "../external/json/document.h"
#include "../external/json/stringbuffer.h"
#include "../external/json/writer.h"

#include "sqlite3.h"

using namespace tinyxml2;

bool T16IO::init()
{
    Layer::init();
    
    // 在cocos中，基本不怎么用fopen
    // 文件操作封装在FileUtils类中
#if 0
    // 1.将ValueMap数据结构写入文件
    FileUtils* f = FileUtils::getInstance();
    std::string fullPath = f->getWritablePath();
    fullPath += "aaa.txt";
    
    CCLOG("fullpath is %s", fullPath.c_str());
  //  f->addSearchPath(const std::string &path)
    
   
   // fwrite(const void *, size_t, size_t, FILE *)
    
    ValueMap m;
    m["age"] = 18;
    m["name"] = "guniang";
    m["sexy"] = "x";
    
    f->writeToFile(m, fullPath);
    
    //
    // 将文本文件的内容读入到std::string对象中
    // std::string str = f->getStringFromFile(filename);
#endif
    
#if 0
    // 容器，数组结构，内存中
    Vector 只能装cocos对象，只能是Ref子类对象
    std::vector 随便
    ValueMap
    
    // 文件格式（也是网络传输格式）
    plist文件（特殊的xml文件）
    xml文件
    json文件
#endif
    
#if 0
    // 数组
    Sprite* p;
    Vector<Sprite*> v;
    v.pushBack(Sprite::create());
    
    v.popBack(); // 删除最后一个
    v.eraseObject(p);
    v.erase(0);
    v.erase(it);
    
    v.at(5);
    v[5];
    
    for (int i=0; i<v.size(); ++i) {
        v[i];
    }
    
    // 有时候需要边遍历边删除
    for (int i=v.size() - 1; i>=0; --i) {
        v[i];
    }
    
    for(auto it = v.begin(); it != v.end(); )
    {
        Sprite* p = *it;
        if(p)
            it = v.erase(it);
        else
            ++it;
    }
#endif
    
#if 0
    // ValueMap，键值对，映射表
    ValueMap vm;
    //vm.insert("key1", 1);
    // 很难看
    vm.insert(std::pair<std::string, Value>("key1", Value(1)));
    // 很简单
    vm["key2"] = 2;
    
    // 可以使用key或者迭代器来删除
    vm.erase("key1");
    vm.erase(vm.begin());
    
    // 访问，这种访问是有缺陷的，如果key对应的Value不存在
    // 会自动增加一个空对象
    if (vm.find("key1") != vm.end()) {
        Value v = vm["key1"];
    }
    else
    {
        
    }
    
    // 遍历
    for (auto it = vm.begin(); it!=vm.end(); )
    {
        if (condition) {
            it = vm.erase(it);
        }
        else{
            ++it;
        }
    }
#endif
    
#if 0
    // PLIST解析
    // 一般plist文件只用于程序配置，不用于网络通信
    
    // Value封装的类型支持plist里的所有类型
    
    //解析Plist文件
    ValueMap vm = FileUtils::getInstance()->getValueMapFromFile("animations/animations-2.plist");
    
    ValueMap& vm1 = vm["animations"].asValueMap();
    ValueMap& vm2 = vm1["dance_1"].asValueMap();
    ValueVector& vv = vm2["frames"].asValueVector();
    
    ValueMap& vm3 = vv[0].asValueMap();
    std::string str = vm3["spriteframe"].asString();
    CCLOG("frame name is %s", str.c_str());
#endif
    
#if 0
    // XML解析
    XMLDocument doc;
    std::string data1 = FileUtils::getInstance()->getStringFromFile("Skill.xml");
    
    XMLError err = doc.Parse(data1.c_str());
    if(XML_SUCCESS != err)
    {
        CCLOG("parse error");
        return true;
    }
    
    XMLElement* root = doc.RootElement();
    
    XMLElement* data = root->FirstChildElement();
    
    while(data)
    {
        XMLElement* child = data->FirstChildElement();
        while(child)
        {
            if(strcmp(child->Value(), "skillId") == 0)
            {
                const char* att1 = child->Attribute("type");
                const char* att2 = child->Attribute("multiLanguage");
                CCLOG("att1 = %s, att2 = %s", att1, att2);
                
                // 30001在哪里
                XMLNode* value = child->FirstChild();
                CCLOG("skillId is %s", value->Value());
                break;
            }
        
            child = child->NextSiblingElement();
        }
        data = data->NextSiblingElement();
        // data = data->NextSibling();
    }
#endif
    
    
#if 0
    // 构建XML文件
    // 1. 只有doc需要new和delete，其他对象的内存从Document创建，由Document管理
    // 2. 创建完节点，需要调用LinkEndChild，参数是XMLNode（纯虚类）
    XMLDocument* doc = new XMLDocument;
    
    XMLElement* root = doc->NewElement("root");
    
    // <root> </root>
    // <root "aaa"=1 "bbb"=2 />
    
    // 插入节点， pushBack
    doc->LinkEndChild(root);
    
    // 在root增加值
    // <root>1</root>
    XMLNode* node = doc->NewText("1");
    root->LinkEndChild(node);
    
    // 在root中，增加Element
    XMLElement* e = doc->NewElement("sub");
    root->LinkEndChild(e);
    // 在sub中，增加值
    node = doc->NewText("3");
    e->LinkEndChild(node);
    
    
    // 在Element中，增加属性
    root->SetAttribute("att1", "1");
    root->SetAttribute("att2", "2");
    
    
   // doc->SaveFile("/Users/xueguoliang/aaa.xml");
    
    
    XMLPrinter stream;
    doc->Print( &stream );
    
    const char* p = stream.CStr();
    CCLOG("%s\n", p);
    

    
    delete doc;
#endif

    /*
        {}表示一个Json对象
        在Json对象中，属性都是字符串类型
        值可以是：nil,bool, number, string, Object, 数组
     
        []表示一个Json数组
     
        {
            "age":18,
            "name":"Tom",
            "man" : true,
            "mobile" : 
            {

                "branch": "apple",
                "gen" : 6
            }
     
            "brothers":
            [
                 {"name":"Jack"},
                {"name":"Rose"},
                {"name":"Mario"},
                {"name":"Paulo"}
            ]
        }
     
        Json对象， Json数组，JsonKey，JsonValue
     
        一个Json文档由一个Json对象组成
        或者由Json数组组成
     
        [
            {},
            {},
            {},
        ]
     
        <root>
            <age>18</age>
            <name>Tom</name>
        </root>
     
        <root "name"=Tom, "age" =18 />
     */

    // 使用代码来解析Json
    // rapidjson
#if 0
    // JSON解析演示
    std::string str = FileUtils::getInstance()->getStringFromFile("config.json");
    
    rapidjson::Document doc;
    
    doc.Parse<0>(str.c_str());
    // doc解析完毕
    
    rapidjson::Type type = doc.GetType();
    
    CCASSERT(type == rapidjson::kObjectType, "config is object");
    
    rapidjson::Value& init_cfg = doc["init_cfg"];
    if( init_cfg.GetType() == rapidjson::kObjectType)
    {
        rapidjson::Value& entry = init_cfg["entry"];
        CCLOG("entry is %s\n", entry.GetString());
    }
    
    rapidjson::Value& simulator_screen_size = doc["simulator_screen_size"];
    rapidjson::Value& title0 = simulator_screen_size[(unsigned int)0]["title"];
    
    CCLOG("title0 is %s\n", title0.GetString());
#endif
    
    // json写文件
#if 0
    {
        "age":18,
        "name":"Tom",
        "mobile" :
        {
            
            "branch": "apple",
            "gen" : 6
        }
        
        "brothers":
        [
         {"name":"Jack"},
         {"name":"Rose"}
        ]
    }
#endif
    
#if 0
    rapidjson::Document doc;
    doc.SetObject();
    
    doc.AddMember("age", 18, doc.GetAllocator());
    doc.AddMember("name", "Tom", doc.GetAllocator());
    
    rapidjson::Value mobile;
    mobile.SetObject();
    mobile.AddMember("branch", "apple", doc.GetAllocator());
    mobile.AddMember("gen", 6, doc.GetAllocator());

    doc.AddMember("mobile", mobile, doc.GetAllocator());
    
    rapidjson::Value brothers;
    brothers.SetArray();
    rapidjson::Value bro1;
    bro1.SetObject();
    bro1.AddMember("name", "jack", doc.GetAllocator());
        brothers.PushBack(bro1,doc.GetAllocator());
    
    rapidjson::Value bro2;
    bro2.SetObject();
    bro2.AddMember("name", "rose", doc.GetAllocator());
    brothers.PushBack(bro2, doc.GetAllocator());
    
    doc.AddMember("brothers", brothers , doc.GetAllocator());
    
    // 写入内存
    rapidjson::StringBuffer buf;
    rapidjson::Writer<rapidjson::StringBuffer> w(buf);
    doc.Accept(w);
    
    CCLOG("%s\n", buf.GetString());
#endif
    
#if 0
    // UserDefault适合小游戏，小数据
    // 512K不要用UserDefault
    
    // cocos的文件读写
    // UserDefault是Cosos封装的，简单的文件读写接口
    UserDefault* ud = UserDefault::getInstance();
    ud->setIntegerForKey("life", 10);
    ud->setStringForKey("name", "jack");
    
    int lifeCount = ud->getIntegerForKey("life", 3);
    
    std::string str = UserDefault::getXMLFilePath();
    CCLOG("xml path is: %s, lifeCount=%d\n", str.c_str(), lifeCount);
#endif
    
    // sqlite3
    // 它是一个小型数据库，适用于嵌入式小设备
    // 数据库：文件 database
    // 表: table
    // itemname itemdemage ....
    // knife    5          ....   // 纪录Record
    // 列（field）
    
    // 数据表的操作：查询（读取），插入（写入），修改（update），
    // 数据库的操作：创建表，删除表。。。
    // 都可以通过SQL语句来操作
    
    // [          ][                    ]
    // [          ][                    ]  分区
    
    
    // 操作数据库
    // 1. 创建（连接，打开）数据库 OK
    //    sqlite3_open
    // 2. 创建表 OK
    //    create table {表名} (列名 类型 [列的属性], 列名 类型 [列的属性]， 列名 类型 [列的属性])
    //    primary key  主键
    //    autoincrement 该字段自动增长
    //    unique        这个字段要求唯一
    // 3. 插入数据 OK
    //    insert into {表名} (字段列表) values (值列表)
    // 4. 查询数据 OK
    //    select {字段列表} from {表名} [where子句] [order by ..]
    //    select name, age from tt;
    // 5. 修改数据 OK
    //    update {表名} set 字段=值, 字段=值 [where子句]
    // 6. 删除数据 OK
    //    delete from {表名} [where子句]
    // 7. 删除表
    //    drop table {表明}
    // 8. 关闭数据库 OK
    //    sqlite3_close()
    // 9. 错误处理 OK
    //    sqlite3_errmsg();
    
    // 
    
    sqlite3* db;
    int ret = sqlite3_open("/Users/xueguoliang/sqlite3.db", &db);
    if(ret != SQLITE_OK)
    {
        CCLOG("open dabase error");
        return true;
    }
    
    // 创建表: SQL语句
#if 0
    ret = sqlite3_exec(db, "create table tt1 (id integer primary key autoincrement, name varchar, age integer)", nullptr, nullptr, nullptr);
    if(ret != SQLITE_OK)
    {
        CCLOG("create table error: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return true;
    }
#endif
    
#if 0
    ret = sqlite3_exec(db, "insert into tt (id, name, age)values(3, 'bbb', 16)", nullptr, nullptr, nullptr);
    if(ret != SQLITE_OK)
    {
        CCLOG("insert error: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return true;
    }
    else{
        CCLOG("insert success");
    }
    // tt(2条记录) tt1（一条记录）
#endif
    
#if 0
    // 修改数据
    ret = sqlite3_exec(db, "update tt set id=5 where name='bbb' ", nullptr, nullptr, nullptr);
    if(ret != SQLITE_OK)
    {
        CCLOG("update error: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return true;
    }
#endif
    
#if 0
    // 删除记录
    ret = sqlite3_exec(db, "delete from tt where id<>5",
                       nullptr, nullptr, nullptr);
    if(ret != SQLITE_OK)
    {
        CCLOG("delete error: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return true;
    }
#endif
    
    // 删除表
    ret = sqlite3_exec(db, "drop table tt",
                       nullptr, nullptr, nullptr);
    if(ret != SQLITE_OK)
    {
        CCLOG("drop table error: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return true;
    }

    extern int callback(void *, int, char **, char **);
    ret = sqlite3_exec(db, "select * from tt", callback, nullptr, nullptr);
    if(ret != SQLITE_OK)
    {
        CCLOG("select error: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return true;
    }
    
    
    sqlite3_close(db);
    
    return true;
}

// id name age
// "1"  "aaa"  "18"

// 返回0表示继续回调，非0表示停止回调
int callback(void *, int argc, char **argv, char **argvv)
{
    for(int i=0; i<argc; ++i)
    {
        CCLOG("%s=%s", argvv[i], argv[i]);
    }
    
    return 0;
}
