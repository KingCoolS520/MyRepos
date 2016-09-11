//
//  T30Dijkstra.h
//  
//
//  Created by 薛国良 on 15/11/23.
//
//

#ifndef ____T30Dijkstra__
#define ____T30Dijkstra__

#include <stdio.h>
#include "cocos2d.h"
#include "Graph.h"

USING_NS_CC;
class T30Dijkstra: public Layer
{
public:
    CREATE_FUNC(T30Dijkstra);
    bool init();
    
    class MyGraphNode
    {
    public:
        bool _addOpen;
        bool _alreadyWalk;
        GraphNode* _from;
        int _dist;  // 还是表示从原点到该点距离
        int _distToEnd; //从该点到目标的距离（估值）
    };
    
    std::vector<GraphNode*> _open;
    std::map<std::string, MyGraphNode*> _info;
    
    void addOpen(GraphNode* node, GraphNode* from, GraphLine* line)
    {
        // node是否已经加入过了，如果已经加入过，或者已经遍历过，就不再加入
        std::string name = node->_name;
        if(_info.find(name) == _info.end())
        {
            // 计算from到开始点的距离
            int distFromToStart = 0;
            if(from)
            {
                MyGraphNode* info = _info[from->_name];
                distFromToStart = info->_dist;
            }
            
            int curDist = 0;
            if(line)
                curDist = line->_dist;
            
            // 计算估值距离
            int dx = node->_x - _nodeEnd->_x;
            int dy = node->_y - _nodeEnd->_y;
           // int distToEnd = (int)sqrt(dx*dx + dy*dy);
            int distToEnd = abs(dx) + abs(dy);
            
            // 加入
            MyGraphNode* info = new MyGraphNode;
            info->_from = from;
            info->_addOpen = true;
            info->_alreadyWalk = false;
            info->_dist = distFromToStart + curDist; //记录了到开始点的距离
            info->_distToEnd = distToEnd;
            
            // 加入信息
            _info.insert(std::pair<std::string, MyGraphNode*>(node->_name, info));
            
            // 将node插入_open，这里要插入
            auto it = _open.begin();
            for(; it!=_open.end(); ++it)
            {
                GraphNode* pos = *it;
                MyGraphNode* posInfo = _info[pos->_name];
                
                if(info->_dist + info->_distToEnd
                   < posInfo->_dist + posInfo->_distToEnd)
                {
                    break;
                }
            }
            
            _open.insert(it, node);
        }
        else // 在信息表里，找到了这个节点
        {
            MyGraphNode* info= _info[node->_name];
            if(!info->_alreadyWalk)
            {
               // info->_dist; 要和现在这个方向过来的dist比较
                
                // 计算from到开始点的距离
                int distFromToStart = 0;
                if(from)
                {
                    MyGraphNode* info = _info[from->_name];
                    distFromToStart = info->_dist;
                }
                
                int curDist = 0;
                if(line)
                    curDist = line->_dist;
                
                if(distFromToStart + curDist < info->_dist)
                {
                    info->_dist = distFromToStart + curDist;
                    info->_from = from;
                    
                    auto it = std::find(_open.begin(), _open.end(), node);
                    _open.erase(it);
                    
                    
                    // 将node插入_open，这里要插入
                    it = _open.begin();
                    for(; it!=_open.end(); ++it)
                    {
                        GraphNode* pos = *it;
                        MyGraphNode* posInfo = _info[pos->_name];
                        
                        if(info->_dist + info->_distToEnd < posInfo->_dist + posInfo->_distToEnd)
                        {
                            break;
                        }
                    }
                    
                    _open.insert(it, node);
                    
                }
            }
        }
    }
    
    void update1(float);
    
    GraphNode* _nodeStart;
    GraphNode* _nodeEnd;
    
    void findPath();
    
    Graph _g;
    void loadGraph();
};

#endif /* defined(____T30Dijkstra__) */
