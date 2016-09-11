//
//  Graph.cpp
//  
//
//  Created by 薛国良 on 15/11/23.
//
//

#include "Graph.h"

Graph::~Graph()
{
    clear();
}

bool Graph::addLine(std::string nameA, std::string nameB, int dist)
{
    GraphNode* nodeA = nullptr;
    if(this->_nodes.find(nameA) != this->_nodes.end())
        nodeA = this->_nodes[nameA];
    
    GraphNode* nodeB = nullptr;
    if (this->_nodes.find(nameB) != this->_nodes.end())
        nodeB = this->_nodes[nameB];
    
    
    if(nodeA == nullptr || nodeB == nullptr)
    {
        return false;
    }
    
    GraphLine* line = new GraphLine;
    line->_nodeA = nodeA;
    line->_nodeB = nodeB;
    line->_dist = dist;
    
    this->_lines.push_back(line);
    
    return true;
}

void Graph::addNode(std::string name, int x, int y)
{
    if(_nodes.find(name) == _nodes.end())
    {
        GraphNode* node = new GraphNode;
        node->_name = name;
        node->_x = x;
        node->_y = y;
        _nodes.insert(std::pair<std::string, GraphNode*>(name, node));
    }
    else
    {
        GraphNode* node = _nodes[name];
        node->_x = x;
        node->_y = y;
    }
#if 0
    GraphNode* node = _nodes[name];
    if (node == nullptr) {
        node = new GraphNode;
        node->_name = name;
        _nodes.insert(std::pair<std::string, GraphNode*>(name, node));
    }
    
    node->_x = x;
    node->_y = y;
#endif
}

void Graph::removeLine(std::string nodeA, std::string nodeB)
{
    for (auto it = _lines.begin(); it!=_lines.end(); ++it) {
        GraphLine* line = *it;
        if(isLine(line, nodeA, nodeB))
        {
            _lines.erase(it);
            delete line;
            break;
        }
    }
}

void Graph::removeLine(std::string name)
{
    for (auto it = _lines.begin(); it!=_lines.end();) {
        GraphLine* line = *it;
        if(line->_nodeA->_name == name || line->_nodeB->_name == name)
        {
            it = _lines.erase(it);
            delete line;
        }
        else
        {
            ++it;
        }
    }
}

void Graph::removeNode(std::string name)
{
    GraphNode* node = nullptr;
    if (_nodes.find(name) != _nodes.end())
    {
        node = _nodes[name];
        _nodes.erase(name);
        delete node;
        
        removeLine(name);
    }
}

void Graph::clear()
{
    while(_nodes.size())
    {
        auto it = _nodes.begin();
        delete it->second;
        _nodes.erase(it);
    }
    
    while(_lines.size() > 0)
    {
        auto it = _lines.begin();
        delete *it;
        _lines.erase(it);
    }
}

/* 文件格式 
    {
        lines:
        [
            {nameA:xxx, nameB:yyy, dist:100},
            {},
        ]
        nodes:
        [
            {name:xxx, x:100, y:100},
            {},
        ]
    }
 */
void Graph::save(std::string filename)
{
    rapidjson::Document doc;
    doc.SetObject();
    
    rapidjson::Value lines;
    // 初始化lines
    lines.SetArray();
    for(auto it = _lines.begin(); it!=_lines.end(); ++it)
    {
        GraphLine* line = *it;
        
        // 初始化Line对象节点
        rapidjson::Value value;
        value.SetObject();
        value.AddMember("nameA", line->_nodeA->_name.c_str(), doc.GetAllocator());
        value.AddMember("nameB", line->_nodeB->_name.c_str(), doc.GetAllocator());
        value.AddMember("dist", line->_dist, doc.GetAllocator());
        
        // 加入到Lines
        lines.PushBack(value, doc.GetAllocator());
    }
    
    
    rapidjson::Value nodes;
    // 初始化Nodes
    nodes.SetArray();
    for(auto it = _nodes.begin(); it != _nodes.end(); ++it)
    {
        GraphNode* node = it->second;
        // 初始化Node对象节点
        rapidjson::Value value;
        value.SetObject();
        value.AddMember("name", node->_name.c_str(), doc.GetAllocator());
        value.AddMember("x", node->_x, doc.GetAllocator());
        value.AddMember("y", node->_y, doc.GetAllocator());
        
        nodes.PushBack(value, doc.GetAllocator());
    }
    
    doc.AddMember("lines", lines, doc.GetAllocator());
    doc.AddMember("nodes", nodes, doc.GetAllocator());
    
    // doc保存到Buf
    rapidjson::StringBuffer buf;
    rapidjson::Writer<rapidjson::StringBuffer> w(buf);
    doc.Accept(w);
    
    // 把buf保存到文件
    const char* p = buf.GetString();
    FILE* file = fopen(filename.c_str(), "w+");
    if(file)
    {
        fwrite(p, strlen(p)+1, 1, file);
        fclose(file);
    }
}

void Graph::load(std::string filename)
{
    clear();
    
    FILE* file = fopen(filename.c_str(), "r+");
    if(!file)
    {
        CCLOG("open file error");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    
    char* buf = new char[size+1];
    buf[size] = 0;
    
    fseek(file, 0, SEEK_SET);
    fread(buf, size, 1, file);
    
    fclose(file);
    
    // 读文件结束
    rapidjson::Document doc;
    doc.Parse<0>(buf);
    delete []buf;
    
    if(doc.GetType() != rapidjson::kObjectType)
    {
        CCLOG("doc is not object error");
        return;
    }
    
    rapidjson::Value& lines = doc["lines"];
    if (lines.GetType() != rapidjson::kArrayType) {
        CCLOG("lines error");
        return;
    }
    
    rapidjson::Value& nodes = doc["nodes"];
    if(nodes.GetType() != rapidjson::kArrayType)
    {
        CCLOG("nodes error");
        return;
    }
    
    for (int i=0; ; ++i)
    {
        rapidjson::Value& node = nodes[i];
        if(node.GetType() != rapidjson::kObjectType)
        {
            break;
        }
        
        this->addNode(node["name"].GetString(),
                      node["x"].GetInt(),
                      node["y"].GetInt());
    }
    
    for (int i=0; ; ++i)
    {
        rapidjson::Value& line = lines[i];
        if(line.GetType() != rapidjson::kObjectType)
        {
            break;
        }
        
        this->addLine(line["nodeA"].GetString(),
                      line["nodeB"].GetString(),
                      line["dist"].GetInt());
    }
}










