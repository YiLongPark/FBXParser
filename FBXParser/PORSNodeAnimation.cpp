//
//  PORSNodeAnimation.cpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/9/21.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSNodeAnimation.hpp"

PORSNodeAnimation::PORSNodeAnimation()
{
    mNumScalingKey = 0;
    mNumPositionKey = 0;
    mNumRotationKey = 0;
    
    mPositionKeys = NULL;
    mRotationKey = NULL;
    mScalingKey = NULL;
}

PORSNodeAnimation::~PORSNodeAnimation()
{
    delete [] mPositionKeys;
    delete [] mRotationKey;
    delete [] mScalingKey;
}
