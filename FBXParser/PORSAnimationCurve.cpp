//
//  PORSAnimationCurve.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/15.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSAnimationCurve.hpp"

PORSAnimationCurve::PORSAnimationCurve(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
{
    mType = ANIMATION_CURVE;
    
    const PORSElement *keyTime = PORSUtil::getRequiredElement(element, "KeyTime");
    const PORSElement *keyValueFloat = PORSUtil::getRequiredElement(element, "KeyValueFloat");
    const PORSElement *keyAttrDataFloat = PORSUtil::getRequiredElement(element, "KeyAttrDataFloat");
    const PORSElement *keyAttrFlags = PORSUtil::getRequiredElement(element, "KeyAttrFlags");
    
    if(keyTime && keyTime->mProperty)
    {
        PORSUtil::parserBinaryArray(*keyTime->mProperty, &mKeyTimeList);
    }
  
    if(keyValueFloat && keyValueFloat->mProperty)
    {
        PORSUtil::parserBinaryArray(*keyValueFloat->mProperty, &mKeyValueList);
    }
    
    if(keyAttrDataFloat && keyAttrDataFloat->mProperty)
    {
        PORSUtil::parserBinaryArray(*keyAttrDataFloat->mProperty, &mAttributes);
    }
    
    if(keyAttrFlags && keyAttrFlags->mProperty)
    {
        PORSUtil::parserBinaryArray(*keyAttrFlags->mProperty, &mFlags);
    }
}

PORSAnimationCurve::~PORSAnimationCurve()
{
    mType = ANIMATION_CURVE_NODE;
}

PORSAnimationCurveNode::PORSAnimationCurveNode(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
{
    
}

PORSAnimationCurveNode::~PORSAnimationCurveNode()
{
    
}
