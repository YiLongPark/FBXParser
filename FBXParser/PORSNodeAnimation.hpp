//
//  PORSNodeAnimation.hpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/9/21.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSNodeAnimation_hpp
#define PORSNodeAnimation_hpp

#include <stdio.h>
#include <iostream>

#include "PORSObject.hpp"

using namespace std;

class PORSNodeAnimation
{
public:
    PORSNodeAnimation();
    ~PORSNodeAnimation();
    
public:
    string mNodeName;
    
    unsigned int mNumPositionKey;
    VectorKey *mPositionKeys;
    unsigned int mNumRotationKey;
    QuatKey *mRotationKey;
    unsigned int mNumScalingKey;
    VectorKey *mScalingKey;

};


#endif /* PORSNodeAnimation_hpp */
