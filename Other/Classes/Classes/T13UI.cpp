//
//  T13UI.cpp
//  T0818
//
//  Created by 薛国良 on 15/10/30.
//
//

#include "T13UI.h"

bool T13UI::init()
{
    Layer::init();
    
    // 文本显示, SystemFont, BMFont, CharMap, TTF
    // SystemFont：使用系统字体，不容易跨平台，字体也太简单
    // BMFont
    // CharMap
    // TTF :true type font
#if 0
    Label* _label = Label::createWithBMFont();
    Label::createWithCharMap(<#const std::string &charMapFile#>, <#int itemWidth#>, <#int itemHeight#>, <#int startCharMap#>);
    Label::createWithSystemFont(<#const std::string &text#>, <#const std::string &font#>, <#float fontSize#>);
    Label::createWithTTF(<#const std::string &text#>, <#const std::string &fontFilePath#>, <#float fontSize#>)
#endif
    
#if 0
    // 文本显示演示
    {
    Label* label = Label::createWithSystemFont("abc", "Arial", 80);
    addChild(label);
    label->setPosition(200, 200);
    }
    
    {
        Label* label = Label::createWithTTF("TTF text", "fonts/Marker Felt.ttf", 80);
        addChild(label);
        label->setPosition(300, 300);
        
        label->enableOutline(Color4B::YELLOW, 2);
    }
    
    {
        Label* label = Label::createWithCharMap(
                                            "fps_images.png",//字体图片
                                                12,// 每个文字的宽度
                                                32,// 每个文字的高度
                                                '.'); //第一个字符的acsii值
        label->setString("123.9a8b00");
        addChild(label);
        label->setPosition(400, 400);
        label->setScale(5);
    }
    
    {
        Label* label = Label::createWithBMFont("hd/fonts/markerFelt.fnt", "B$p");
        addChild(label);
        label->setPosition(500, 500);
        label->setScale(5);
        
        // 演示文字的效果
      //  label->setColor(Color3B::RED);
        
        label->setString("abc");
        
        // 取出一个文字来修改
        Sprite* sp = label->getLetter(1);
        JumpBy* j = JumpBy::create(1.0f, Vec2(0, 0), 30, 2);
        sp->runAction(RepeatForever::create(j));
        
    }
#endif
    
    // 文本输入
    //TextFieldTTF;
    //ui::EditBox;
    auto size = Director::getInstance()->getWinSize();
#if 0
    
    
    {
        TextFieldTTF* textEdit = TextFieldTTF::textFieldWithPlaceHolder("Please input your name:", Size(400, 80), TextHAlignment::CENTER, "Arial", 75);
        addChild(textEdit);
        textEdit->setPosition(size.width/2, 200);
        
      //  TextFieldDelegate* p = new TextFieldDelegate;
      //  textEdit->setDelegate(p);
        textEdit->setDelegate(this);
        
        {
        EventListenerTouchOneByOne* ev = EventListenerTouchOneByOne::create();
        ev->onTouchBegan = [=](Touch* touch, Event*)
        {
            Rect rc = textEdit->getBoundingBox();
            Vec2 touchLoc = touch->getLocation();
            if (rc.containsPoint(touchLoc)) {
                
                textEdit->attachWithIME();
            }
            //textEdit->getBoundingBox().
            return false;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
        }
        
        // 跟Label一样
        textEdit->getString();
    }
#endif
    
#if 0
    ui::Scale9Sprite * sprite = ui::Scale9Sprite::create("extensions/green_edit.png");
    ui::EditBox* editBox = ui::EditBox::create(Size(800, 80), sprite);
    addChild(editBox);
    editBox->setPosition(Vec2(size.width/2, 100));
    
    // 获取内容
    const char* value = editBox->getText();
    
    editBox->setPlaceHolder("Please input your name:");
    editBox->setPlaceholderFontColor(Color4B::RED);
    editBox->setFontColor(Color4B::RED);
#endif
    
#if 1
    // ui::Button
    ui::Button* btn = ui::Button::create("Images/b1.png", "Images/b2.png");
    addChild(btn);
    btn->setPosition(Vec2(400, 400));
    
  //  typedef std::function<void(Ref*,Widget::TouchEventType)>
    //ccWidgetTouchCallback;
    
    auto callback = [](Ref* sender,ui::Widget::TouchEventType type)
    {
        if(type == ui::Widget::TouchEventType::BEGAN)
        {
            CCLOG("Button Touch Began");
        }
        else if(type == ui::Widget::TouchEventType::ENDED)
        {
            CCLOG("Button Touch ENDED");
        }
    };
    btn->addTouchEventListener(callback);
    btn->setTitleText("abc");
    
    btn->setPressedActionEnabled(true);
    btn->setZoomScale(10);
    //btn->setScale(10);
#endif
    
#if 0
    ui::Slider* slider = ui::Slider::create("extensions/sliderProgress.png", "extensions/sliderThumb.png");
    addChild(slider);
    slider->setPosition(Vec2(500, 500));
    slider->setScale(3);
    
    auto callback = [](Ref* sender,ui::Widget::TouchEventType type)
    {
        ui::Slider* s = (ui::Slider*)sender;
        CCLOG("%d", s->getPercent());
    };
    
    slider->addTouchEventListener(callback);
#endif
    
#if 0
    ui::ScrollView* view = ui::ScrollView::create();
    
    
    Sprite* sprite;
    view->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    view->setLayoutType(ui::Layout::Type::HORIZONTAL);
    
    view->addChild(sprite = Sprite::create("Images/background3.jpg"));
//    sprite->setPosition(size.width/2, size.height/2);
    
    view->addChild(sprite = Sprite::create("Images/background3.jpg"));
  //  sprite->setPosition(size.width + size.width/2, size.height/2);
    
    view->addChild(sprite = Sprite::create("Images/background3.jpg"));
  //  sprite->setPosition(size.width*2 + size.width/2, size.height/2);
    
   // view->setInnerContainerSize(Size(size.width*3, size.height));
    addChild(view);
#endif
    
#if 0
    {
    // 普通的触摸处理和被注册的对象没有关系，只要触摸屏幕，回调函数就会被调用
    Sprite* sprite = Sprite::create("Images/blocks.png");
    addChild(sprite);
    auto ev =EventListenerTouchOneByOne::create();
    ev->onTouchBegan = [](Touch*, Event*){
        CCLOG("Spirte Touch");
        return true;};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(ev, sprite);
    }
#endif
    
    
#if 0
    // Widget演示
    auto winSize = Director::getInstance()->getWinSize();
    
    // UI::Widget是所有UI控件的父累
    /*
        它提供了三个触摸处理回调函数
     */
    ui::Widget* widget = ui::Widget::create();
    addChild(widget);
    
    // 设置TouchEnable
    widget->setTouchEnabled(true);
    // 其次要告诉程序窗口的尺寸
    widget->setContentSize(winSize);
    
    size = widget->getContentSize();
    
    // 当手指滑过窗口时
    widget->addTouchEventListener([](Ref*, ui::Widget::TouchEventType){
        CCLOG("TouchEvent");
    });
    
    // 当手指点击时
    widget->addClickEventListener([](Ref*){
        CCLOG("ClickedEvent");
    });
    
    // cocosEvent，
    widget->addCCSEventListener([](Ref*, int){
        CCLOG("CCSEvent");
    });
#endif
    
#if 0
    auto winSize = Director::getInstance()->getWinSize();
    ui::ImageView* image = ui::ImageView::create("Images/blocks.png");
    addChild(image);
    image->setTouchEnabled(true);
    
    image->setPosition(Vec2(winSize.width/2, winSize.height/2));
    // 当手指点击时
    image->addClickEventListener([](Ref*){
        CCLOG("Image View ClickedEvent");
    });
    
    // 当手指滑过窗口时
    image->addTouchEventListener([](Ref* sender, ui::Widget::TouchEventType type){
        ui::ImageView* p = (ui::ImageView*)sender;
        
        if(type == ui::Widget::TouchEventType::MOVED)
        {
            CCLOG("%g, %g",p->getTouchMovePosition().x, p->getTouchMovePosition().y);;
            // 想得到手指位置
        }
        CCLOG("TouchEvent");
    });
#endif
    
#if 0
    ui::Layout;
        ui::HBox;
        ui::VBox;
        ui::RelativeBox;
    ui::ScrollView;
    ui::ListView;
    ui::PageView;
#endif
    
#if 0
    // Layout
    auto winSize = Director::getInstance()->getWinSize();
    ui::Layout* lay = ui::Layout::create();
    addChild(lay);
    
    lay->setLayoutType(ui::Layout::Type::VERTICAL);
    lay->setContentSize(Size(winSize.width/2, winSize.height/2));
    
    lay->setPosition(Vec2(winSize.width/2, winSize.height/2));
    
    ui::Text* text = ui::Text::create("This is text", "Arial", 30);
    /* 如果addChild参数不是Widget子类对象，那么就不对它进行布局布置，只是简单的调用Node::addChild */
    lay->addChild(text);
    
    ui::ImageView* image = ui::ImageView::create("Images/blocks.png");
    lay->addChild(image);
    
    ui::Button* button  =ui::Button::create("Images/b1.png", "Images/b2.png");
    lay->addChild(button);
#endif
    
#if 0
    
#define MARGIN_X 10
#define MARGIN_Y 40
    
    auto winSize = Director::getInstance()->getWinSize();
    ui::ScrollView* view = ui::ScrollView::create();
    view->setLayoutType(ui::Layout::Type::VERTICAL);
    
    view->setContentSize(Size(winSize.width-MARGIN_X*2, winSize.height-MARGIN_Y*2));
    view->setInnerContainerSize(Size(winSize.width-MARGIN_X*2, 690));
  //  view->setDirection(ui::ScrollView::Direction::BOTH);
    
    view->setPosition(Vec2(MARGIN_X, MARGIN_Y));
    
    // 增加弹性效果
    view->setBounceEnabled(true);
    
    for(int i=0; i<20; ++i)
    {
        char buf[111];
        sprintf(buf, "This is text %d", i);
        ui::Text* text = ui::Text::create(buf, "Arial", 30);
        view->addChild(text);
        text->setTag(i);
        text->setTouchEnabled(true);
        text->addClickEventListener([](Ref* sender){
            ui::Text* p = (ui::Text*)sender;
            CCLOG("click item is %d", p->getTag());
        });
    }
    
    addChild(view);
    
    // 换背景
    // view->setBackGroundImage("Images/background3.jpg");
    view->setBackGroundColor(Color3B::RED, Color3B::GREEN);
   // view->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    
    view->setBackGroundColorType(ui::Layout::BackGroundColorType::GRADIENT);
    // 0 透明，255表示不透明
    view->setBackGroundColorOpacity(128);
#endif
    
#if 0
    // ScrollView 2.2.6
    auto winSize = Director::getInstance()->getWinSize();
    
    // 创建ScrollView的参数，指这个ScrollView能见到的尺寸
    ScrollView* view = ScrollView::create(winSize);
    addChild(view);
    // 内部尺寸
    view->setContentSize(Size(winSize.width*5, winSize.height
                              ));
    // 往ScrollView内部放置内容
    // 先取得container，然后再往container中放置
    Node* container = view->getContainer();
    for(int i=0; i<5; ++i)
    {
        Sprite* sprite = Sprite::create("Images/background.png");
        sprite->setTag(i);
        sprite->setScale(0.5f);
        container->addChild(sprite);
        sprite->setPosition(winSize.width/2 + i*winSize.width,
                            winSize.height/2);
        
    }
    
    // 设置方向
    view->setDirection(ScrollView::Direction::HORIZONTAL);
    
    // 触摸处理
    auto ev = EventListenerTouchOneByOne::create();
    
    ev->onTouchBegan = [](Touch*touch, Event*){
        // 判断是否点中了图片
        // 切换场景
        return true;
    };
    ev->onTouchEnded = [=](Touch*touch, Event*){
        Vec2 posEnd = touch->getLocation();
        Vec2 posBegin = touch->getStartLocation();
       // if(posEnd == posBegin)
        if(posEnd.getDistance(posBegin) < 5)
        {
            Vec2 ptInContainer = container->convertToNodeSpace(posEnd);
            for(int i=0; i<5; ++i)
            {
                Node* node = container->getChildByTag(i);
                Rect rc = node->getBoundingBox();
                
                if(rc.containsPoint(ptInContainer))
                {
                    CCLOG("page i=%d, clicked", i);
                    // 进入场景
                    break;
                }
            }
        }
    };
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(ev, this);
    
#endif
    
 //   TableView* table = TableView::create();
 //   addChild(table);
    
    
    return true;
}