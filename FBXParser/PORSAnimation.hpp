//
//  PORSAnimation.hpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/9/21.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSAnimation_hpp
#define PORSAnimation_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

#include "PORSNodeAnimation.hpp"

class PORSAnimation
{
public:
    PORSAnimation();
    ~PORSAnimation();
    
public:
    string mAnimationName;
    double mDuration;
    double mTicksPerSecond;
    unsigned int mNumChannel;
    PORSNodeAnimation **mNodeAnimationChannels;
    
};

#endif /* PORSAnimation_hpp */
