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

#include "PORSObject.hpp"
#include "PORSScene.hpp"
#include "PORSUtil.hpp"

using namespace std;

class PORSAnimationCurve: public PORSObject
{
public:
    PORSAnimationCurve(const PORSScene &scene, const PORSElement &element);
    ~PORSAnimationCurve();
    
public:
    vector<int64_t> mKeyTimeList;
    vector<float> mKeyValueList;
    vector<float> mAttributes;
    vector<unsigned int> mFlags;
};

class PORSAnimationCurveNode: public PORSObject
{
public:
    PORSAnimationCurveNode(const PORSScene &scene, const PORSElement &element);
    ~PORSAnimationCurveNode();
    
public:
    PORSObject *mBone;
    string mBoneLinkProperty;
};

#endif /* PORSAnimationCurve_hpp */
