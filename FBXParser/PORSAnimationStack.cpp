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
    mLocalStop = 0L;
    mLocalStart = 0L;

    string tempName = mName;
    
    //修正二进制文件的动画名称
    int stringLenght = element.mProperty->mNext->mToken.mLenght;
    for (size_t i = 0; i < stringLenght; ++i)
    {
        if (tempName[i] == 0x0 && tempName[i+1] == 0x1)
        {
            tempName = tempName.substr(i+2) + "::" + tempName.substr(0,i);
            
            printf("--%s\n", tempName.c_str());
        }
    }
    
    if (tempName.substr(0, 16) == "AnimationStack::")
    {
        mAnimationStackName = tempName.substr(16);
    }
    else if (tempName.substr(0, 11) == "AnimStack::")
    {
        mAnimationStackName = tempName.substr(11);
    }
    
    const PORSElement *properties = PORSUtil::getRequiredElement(element, "Properties70");
    
    if(properties)
    {
        PORSElement *iter = properties->mChild;
        
        while(iter)
        {
            string tag = iter->mProperty->mToken.toString();
            
            if(!tag.compare("LocalStop"))
            {
                mLocalStop = iter->mProperty->mNext->mNext->mNext->mNext->mToken.toI64();
            }
            if(!tag.compare("LocalStart"))
            {
                mLocalStart = iter->mProperty->mNext->mNext->mNext->mNext->mToken.toI64();
            }
            
            iter = iter->mSibling;
        }
       
    }
  
}

PORSAnimationStack::~PORSAnimationStack()
{
    
}
