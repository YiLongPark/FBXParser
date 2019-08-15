//
//  PORSAnimationStack.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/15.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSAnimationStack_hpp
#define PORSAnimationStack_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PORSObject.hpp"
#include "PORSScene.hpp"
#include "PORSAnimationCurve.hpp"

using namespace std;

class PORSAnimationLayer:public PORSObject
{
    
public:
    PORSAnimationLayer(const PORSScene &scene, const PORSElement &element);
    ~PORSAnimationLayer();
    
public:
    vector<PORSAnimationCurveNode *> mCurveNode;
};

class PORSAnimationStack:public PORSObject
{
public:
    PORSAnimationStack(const PORSScene &scene, const PORSElement &element);
    ~PORSAnimationStack();
    
public:
    std::vector<const PORSAnimationLayer *> mAnimationLayerList;
};

#endif /* PORSAnimationStack_hpp */
