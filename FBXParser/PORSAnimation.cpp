//
//  PORSAnimation.cpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/9/21.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSAnimation.hpp"


PORSAnimation::PORSAnimation()
{
    mDuration = -1.0;
    mTicksPerSecond = 0.0;
    mNumChannel = 0;
    mNodeAnimationChannels = nullptr;
}

PORSAnimation::~PORSAnimation()
{
    if(mNumChannel > 0 && mNodeAnimationChannels)
    {
        for(unsigned int i = 0; i < mNumChannel; i++)
        {
            delete mNodeAnimationChannels[i];
        }
        
        delete [] mNodeAnimationChannels;
    }
}

