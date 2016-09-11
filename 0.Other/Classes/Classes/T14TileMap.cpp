//
//  T14TileMap.cpp
//  T0818
//
//  Created by 薛国良 on 15/10/30.
//
//

#include "T14TileMap.h"

bool T14TileMap::init()
{
    Layer::init();
#if 0
    // 演示地图的创建
    TMXTiledMap* map = TMXTiledMap::create("TileMaps/orthogonal-test1.tmx");
    addChild(map);
#endif
    
    
    // 研究地图描述文件
    // 瓦片地图的资源由两部分构成：图元（tileSet）对应的是PNG图片，瓦片地图描述文件（XML文件）［地图属性，图元属性，地图层数据］
    
    // 地图可以有多个层，也可以有多个图元
    // 地图为什么要分层：地图本来就有层次需要
    // 多个图元：一个层只能用一个图元
#if 0
    // 通过GL坐标获取地图坐标
    
    // 点击地图，让点到的格子消失
    TMXLayer* lay = map->getLayer("Layer 0");
    auto ev = EventListenerTouchOneByOne::create();
    ev->onTouchBegan = [=](Touch* touch, Event*)
    {
        // getMapSize指地图中有多少格子，其中width指x方向格子数量
        // height是y方向的格子数量
        // getTileSize指一个格子的宽度和高度，以像素为单位。
        
        float gridWidth = map->getTileSize().width;
        float gridHeight = map->getTileSize().height;
        
        int gridYCount = map->getMapSize().height;
        
        Vec2 touchLoc = touch->getLocation();
        Vec2 locInMap = map->convertToNodeSpace(touchLoc);
        
        // 格子地图的坐标一定要整数。。。。。
        int x = locInMap.x / gridWidth;
        int y = locInMap.y / gridHeight;
        y = gridYCount - y - 1;
        
        // 设置x, y的瓦片ID，如果是0，表示该位置要清除瓦片
      //  lay->setTileGID(1, Vec2(int(locInMap.x / gridWidth), y));
        
        Sprite * p = lay->getTileAt(Vec2(x, y));
        if(p)
        {
            
            JumpBy* j = JumpBy::create(5.0f, Vec2(100, 100), 30 , 5);
            p->runAction(j);
        }
        
        
        
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
#endif
    
#if 0
    // 通过格子的地图坐标，获得格子左上角的GL坐标
    float tileWidth = map->getTileSize().width;
    float tileHeight = map->getTileSize().height;
    
    int x = 1, y = 2;
    int x1 = x * tileWidth;
    int y1 = y * tileHeight;
    
    y1 = map->getContentSize().height - y1 - 1;
#endif
    
    // 格子地图的对象层
    // 格子地图可以有对象层，但是没有该对象的图片资源，只有属性
    // 演示地图的创建
    TMXTiledMap* map = TMXTiledMap::create("mytile.tmx");
    addChild(map);
    
    TMXObjectGroup * og = map->getObjectGroup("对象层 1");
    ValueVector& vv = og->getObjects();
    
    for(int i=0; i<vv.size(); ++i)
    {
        Value& v = vv[i];
        ValueMap& vm = v.asValueMap();
        
        vm["name"] = "123";
        Value& name = vm["name"];
        CCLOG("%s", name.asString().c_str());
        
        if(name.asString() == "enemy")
        {
            Sprite* sprite = Sprite::create("enemy.png");
            sprite->setPosition(vm["x"].asInt(), vm["y"].asInt());
        }
        else if(name.asString() == "hero")
        {
            
        }
    }
    
    
    return true;
}