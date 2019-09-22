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

//#include "PORSObject.hpp"
//#include "PORSScene.hpp"
#include "PORSAnimationCurve.hpp"

using namespace std;

class PORSAnimationLayer:public PORSObject
{
    
public:
    PORSAnimationLayer(uint64_t uid, const PORSElement &element);
    ~PORSAnimationLayer();
    
public:
    vector<PORSAnimationCurveNode *> mCurveNode;
};

class PORSAnimationStack:public PORSObject
{
public:
    PORSAnimationStack(uint64_t uid, const PORSElement &element);
    ~PORSAnimationStack();
    
public:
    std::vector<const PORSAnimationLayer *> mAnimationLayerList;
    
    string mAnimationStackName;
    int64_t mLocalStart;
    int64_t mLocalStop;
};

#endif /* PORSAnimationStack_hpp */
