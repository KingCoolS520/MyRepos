//
//  T29Graph.cpp
//  
//
//  Created by 薛国良 on 15/11/23.
//
//

#include "T29Graph.h"

bool T29Graph::init()
{
    Layer::init();
    // 960, 640
    _g.addNode("北京", 800, 550);
    _g.addNode("上海", 850, 320);
    _g.addNode("广州", 480, 200);
    _g.addNode("深圳", 490, 50);
    _g.addNode("天津", 900, 480);
    _g.addNode("石家庄", 600, 500);
    _g.addNode("南京", 800, 400);
    _g.addNode("成都", 380, 320);
   // _g.addNode("东京", 200, 200);
    _g.addNode("西安", 540, 380);
    _g.addNode("银川", 300, 580);
    
    _g.addLine("北京", "天津", 151);
    _g.addLine("北京", "石家庄", 199);
    _g.addLine("天津", "南京", 299);
    _g.addLine("南京", "上海", 246);
    _g.addLine("上海", "广州", 1378);
    _g.addLine("广州", "深圳", 250);
    _g.addLine("广州", "成都", 1201);
    _g.addLine("成都", "西安", 352);
    
    _g.addLine("成都", "银川", 1222);
    _g.addLine("银川", "西安", 1001);
    _g.addLine("石家庄", "西安", 891);
    
    loadGraph();
    
    auto ev= EventListenerTouchOneByOne::create();
    
    ev->onTouchBegan = [&](Touch*, Event*){
        
        _nodeStart = _g._nodes["北京"];
        _nodeEnd = _g._nodes["深圳"];
        
        findPath();
        
        return true;
    };
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    
    return true;
}

void T29Graph::findPath()
{
  //  _record.push_back(this->_nodeStart);
    addNodeToRecord(this->_nodeStart, nullptr);
    
    // _record.size大于0，说明有岔路口没有被遍历到
    while(_record.size() > 0)
    {
        GraphNode* node = *_record.begin();
        _record.erase(_record.begin());
        removeNodeFromRecord(node);
        
        if(node == this->_nodeEnd)
        {
            CCLOG("---------------------");
            
            while (node) {
                CCLOG("%s", node->_name.c_str());
                node = _info[node->_name]->_from;
            }
            
            
            break;
        }
        else
        {
            CCLOG("%s", node->_name.c_str());
        }
        
        std::vector<GraphLine*> lines = _g.getLine(node);
        for(auto it=lines.begin(); it!=lines.end(); ++it)
        {
            GraphLine* line=*it;
            if(line->_nodeA == node)
            {
                if(needToAddRecord(line->_nodeB))
                {
                    addNodeToRecord(line->_nodeB, node);
                }
            }
            else
            {
                if(needToAddRecord(line->_nodeA))
                {
                    addNodeToRecord(line->_nodeA, node);
                }
            }
        }
    }
    
    _record.clear();
}

void T29Graph::loadGraph()
{
    for (auto it = _g._nodes.begin(); it!=_g._nodes.end(); ++it) {
        GraphNode* node = it->second;
        std::string key = it->first;
        
        Sprite* sprite = Sprite::create("CloseNormal.png");
        addChild(sprite);
        sprite->setPosition(node->_x, node->_y);
        
        Label* label = Label::createWithSystemFont(node->_name, "Arial", 30);
        addChild(label);
        label->setPosition(node->_x, node->_y);
    }
    
    for (auto it = _g._lines.begin(); it!=_g._lines.end(); it++) {
        GraphLine* line = *it;
        GraphNode* nodeA = line->_nodeA;
        GraphNode* nodeB = line->_nodeB;
        
        Vec2 posA = Vec2(nodeA->_x, nodeA->_y);
        Vec2 posB = Vec2(nodeB->_x, nodeB->_y);
        
        DrawNode* node = DrawNode::create();
        addChild(node);
        node->drawLine(posA, posB, Color4F::RED);
        
        char buf[128];
        sprintf(buf, "%d", line->_dist);
        Label* label = Label::createWithSystemFont(buf, "Arial", 30);
        addChild(label);
        label->setPosition((posA + posB) / 2);
    }
}



