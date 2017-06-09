//
//  T13UI.h
//  T0818
//
//  Created by 薛国良 on 15/10/30.
//
//

#ifndef __T0818__T13UI__
#define __T0818__T13UI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
#include "../extensions/cocos-ext.h"
USING_NS_CC_EXT;


class T13UI : public Layer, TextFieldDelegate
{
public:
    CREATE_FUNC(T13UI);
    bool init();
    
    /**
     *@brief    If the sender doesn't want to attach to the IME, return true.
     */
    virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender)
    {
        // 先获取软键盘的高度
        MoveBy* move = MoveBy::create(1.0f, Vec2(0, 600));
        this->runAction(move);
        
        CC_UNUSED_PARAM(sender);
        return false;
    }
    
    /**
     *@brief    If the sender doesn't want to detach from the IME, return true.
     */
    virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender)
    {
        MoveBy* move = MoveBy::create(1.0f, Vec2(0, -600));
        this->runAction(move);
        CC_UNUSED_PARAM(sender);
        return false;
    }
};

#endif /* defined(__T0818__T13UI__) */
