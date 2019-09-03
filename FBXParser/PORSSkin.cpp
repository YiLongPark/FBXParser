//
//  PORSSkin.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSSkin.hpp"

PORSSkin::PORSSkin(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
{
     mType = SKIN;
    
//     const PORSElement *linkDeformAcuracy = PORSUtil::getRequiredElement(element, "Link_DeformAcuracy");
    // mAccracy = linkDeformAcuracy->mProperty->mToken.toFloat();
    
     //目前这里的精度信息没有获取到，还没有找到问题的原因。
    
}

PORSSkin::~PORSSkin()
{
    
}
