//
//  PORSAnimationStack.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/15.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSAnimationStack.hpp"

PORSAnimationLayer::PORSAnimationLayer(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
{
    mType = ANIMATION_LAYER;
}

PORSAnimationLayer::~PORSAnimationLayer()
{
    
}


PORSAnimationStack::PORSAnimationStack(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
{
    mType = ANIMATION_STACK;
}

PORSAnimationStack::~PORSAnimationStack()
{
    
}
