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
#include "PORSScene.hpp"
#include "PORSElement.hpp"
#include "PORSUtil.hpp"

using namespace std;

class PORSNodeAttribute : public PORSObject
{
public:
    PORSNodeAttribute(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
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
    PORSLimbNode(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
    {
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
    PORSLight(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
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
    PORSNullNode(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
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
    PORSMESH(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
    {
        mType = MESH;
        mIsNode = true;
    }
    
    ~PORSMESH()
    {
        
    }
    
};



#endif /* PORSNodeAttribute_hpp */
