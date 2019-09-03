//
//  PORSAnimationCurve.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/15.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSAnimationCurve_hpp
#define PORSAnimationCurve_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

#include "PORSObject.hpp"
//#include "PORSScene.hpp"
#include "PORSUtil.hpp"

using namespace std;

class PORSAnimationCurve: public PORSObject
{
public:
    PORSAnimationCurve(uint64_t uid, const PORSElement &element);
    ~PORSAnimationCurve();
    
public:
    vector<int64_t> mKeyTimeList;
    vector<float> mKeyValueList;
    vector<float> mAttributes;
    vector<unsigned int> mFlags;
};


typedef map<string, const PORSAnimationCurve*> AnimationCurveMap;

class PORSAnimationCurveNode: public PORSObject
{
public:
    PORSAnimationCurveNode(uint64_t uid, const PORSElement &element);
    ~PORSAnimationCurveNode();
    
public:
    PORSObject *mBone;
    string mBoneLinkProperty;
    
    AnimationCurveMap mAnimationCurve;
};

#endif /* PORSAnimationCurve_hpp */
