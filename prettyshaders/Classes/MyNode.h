//
//  MyNode.h
//  prettyshaders
//
//  Created by chenliang on 14-1-7.
//
//

#ifndef prettyshaders_MyNode_h
#define prettyshaders_MyNode_h

#include "cocos2d.h"

USING_NS_CC;

class MyNode : public CCNode
{
public:
    MyNode(float x, float y);
    virtual void draw(void);
    
    ccV3F_C4B_T2F_Quad m_sQuad;
    CCPoint p;
};

#endif
