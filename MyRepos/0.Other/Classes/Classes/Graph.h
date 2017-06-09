//
//  Graph.h
//  
//
//  Created by 薛国良 on 15/11/23.
//
//

#ifndef ____Graph__
#define ____Graph__

#include <stdio.h>
#include "../external/json/rapidjson.h"
#include "../external/json/document.h"
#include "../external/json/stringbuffer.h"
#include "../external/json/writer.h"

class GraphNode
{
public:
    int _x;
    int _y;
    std::string _name;
};

class GraphLine
{
public:
    GraphNode* _nodeA;
    GraphNode* _nodeB;
    int _dist;
};

class Graph
{
public:
    // 点的集合和线的集合
    std::map<std::string, GraphNode*> _nodes;
    std::list<GraphLine*> _lines;
    
    bool addLine(std::string nodeA, std::string nodeB, int dist);
    void addNode(std::string name, int x, int y);
    
    void removeLine(std::string nodeA, std::string nodeB);
    void removeLine(std::string name);
    
    void removeNode(std::string name);
    
    std::vector<GraphLine*> getLine(GraphNode* node)
    {
        std::vector<GraphLine*> ret;
        for(auto it = _lines.begin(); it!=_lines.end(); it++)
        {
            GraphLine* line = *it;
            if(line->_nodeA == node || line->_nodeB == node)
            {
                ret.push_back(line);
            }
        }
        return ret;
    }
    
    
    
    void save(std::string filename);
    void load(std::string filename);
    
    bool isLine(GraphLine* line, std::string nodeA, std::string nodeB)
    {
        bool b1 = line->_nodeA->_name == nodeA && line->_nodeB->_name == nodeB;
        bool b2 =line->_nodeA->_name == nodeB && line->_nodeB->_name == nodeA;
        return b1 || b2;
    }
    
    void clear();
    
    ~Graph();
};

#endif /* defined(____Graph__) */
