//
//  T08GridAction.cpp
//  T0818
//
//  Created by 薛国良 on 15/10/29.
//
//

#include "T08GridAction.h"


bool T08GridAction::init()
{
    Layer::init();
    
    auto winSize = Director::getInstance()->getWinSize();
    Sprite* sprite = Sprite::create("Images/background3.jpg");
    
    sprite->setPosition(winSize.width/2, winSize.height/2);
    
    sprite->setScale(winSize.width/sprite->getContentSize().width,
                     winSize.height/sprite->getContentSize().height);
    
  //  TurnOffTiles* turnOff = TurnOffTiles::create(5.0, Size(16,12));
  //  ShakyTiles3D* action = ShakyTiles3D::create(10.0f, Size(16,12), 5, false);
    Twirl* action = Twirl::create(10.0f, Size(16,12), Vec2(200, 200), 30, 20);
    NodeGrid* node = NodeGrid::create();
    node->runAction(action);
    addChild(node);
    
    node->addChild(sprite);
    
    
    
    return true;
}