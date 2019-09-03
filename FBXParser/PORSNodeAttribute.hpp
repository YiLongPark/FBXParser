//
//  PORSNodeAttribute.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/16.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSNodeAttribute_hpp
#define PORSNodeAttribute_hpp

#include <stdio.h>
#include <iostream>

#include "PORSObject.hpp"
//#include "PORSScene.hpp"
#include "PORSElement.hpp"
#include "PORSUtil.hpp"

using namespace std;

class PORSNodeAttribute : public PORSObject
{
public:
    PORSNodeAttribute(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
    {
        mType = NODE_ATTRIBUTE;
        
        const PORSElement *typeFlags = PORSUtil::getRequiredElement(element, "TypeFlags");
        
        if(typeFlags && typeFlags->mProperty)
        {
            mAttributeType = typeFlags->mProperty->mToken.toString();
        }
      
    }
    
    ~PORSNodeAttribute()
    {
        
    }
    
public:
    string mAttributeType;
    
};


class PORSLimbNode: public PORSObject
{
public:
    PORSLimbNode(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
    {
        mName = element.mProperty->mNext->mToken.toString();
        mType = LIMB_NODE;
        mIsNode = true;
      
    }

    ~PORSLimbNode()
    {
        
    }

};

class PORSLight: public PORSObject
{
public:
    PORSLight(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
    {
        mType = LIGHT_NODE;
        mIsNode = true;
        
    }
    
    ~PORSLight()
    {
        
    }
};


class PORSNullNode: public PORSObject
{
public:
    PORSNullNode(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
    {
        mType = NULL_NODE;
        mIsNode = true;
    }
    
    ~PORSNullNode()
    {
        
    }
};


class PORSMESH: public PORSObject
{
public:
    PORSMESH(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
    {
        mType = MESH;
        mIsNode = true;
    }
    
    ~PORSMESH()
    {
        
    }
    
};



#endif /* PORSNodeAttribute_hpp */
