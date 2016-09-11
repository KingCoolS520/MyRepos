//
//  T29Graph.h
//  
//
//  Created by 薛国良 on 15/11/23.
//
//

#ifndef ____T29Graph__
#define ____T29Graph__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
#include "Graph.h"

class T29Graph : public Layer
{
public:
    CREATE_FUNC(T29Graph);
    bool init();
    
    class MyGraphNode
    {
    public:
        GraphNode* _node;
        bool _already;
        bool _readyTo;
        GraphNode* _from;
        
        MyGraphNode(GraphNode* node)
        {
            _node = node;
            _already = false;
            _readyTo = false;
        }
    };
    
    Graph _g;
    GraphNode* _nodeStart;
    GraphNode* _nodeEnd;
    
    // 记录将来要遍历的点，开放表
    std::vector<GraphNode*> _record;
    // 记录遍历信息
    std::map<std::string, MyGraphNode*> _info;
    
    void addNodeToRecord(GraphNode* node, GraphNode* from)
    {
        _record.push_back(node);
        MyGraphNode* nodeInfo = new MyGraphNode(node);
        nodeInfo->_readyTo = true;
        nodeInfo->_already = false;
        nodeInfo->_from = from;
        _info.insert(std::pair<std::string, MyGraphNode*>(node->_name, nodeInfo));
    }
    
    void removeNodeFromRecord(GraphNode* node)
    {
        MyGraphNode* nodeInfo = _info[node->_name];
        nodeInfo->_already = true;
    }
    
    bool needToAddRecord(GraphNode* node)
    {
        if(_info.find(node->_name) == _info.end())
            return true;
        
        MyGraphNode* nodeInfo = _info[node->_name];
        if(nodeInfo->_already || nodeInfo->_readyTo)
        {
            return false;
        }
        return true;
    }
    
    
    
    
    void loadGraph();
    void findPath();
};


#endif /* defined(____T29Graph__) */
