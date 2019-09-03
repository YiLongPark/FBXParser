//
//  PORSAnimationStack.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/15.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSAnimationStack.hpp"

PORSAnimationLayer::PORSAnimationLayer(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
{
    mType = ANIMATION_LAYER;
}

PORSAnimationLayer::~PORSAnimationLayer()
{
    
}


PORSAnimationStack::PORSAnimationStack(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
{
    mName = element.mProperty->mNext->mToken.toString();
    mType = ANIMATION_STACK;
  
}

PORSAnimationStack::~PORSAnimationStack()
{
    
}
