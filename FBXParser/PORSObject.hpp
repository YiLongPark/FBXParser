//
//  PORSObject.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/6.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSObject_hpp
#define PORSObject_hpp

#include <stdio.h>
#include <iostream>

#include "PORSElement.hpp"
#include "PORSObject.hpp"

using namespace std;

struct Vector3D
{
    double x, y ,z;
};

struct Vector4D
{
    double x, y, z, w;
};

struct Vector2D
{
    double x, y;
};

struct Matrix4x4
{
    double m[16];
};

enum OjectType
{
    ROOTNODE,
    GEOMETRY,
    MATERIAL,
    MESH,
    TEXTURE,
    LIMB_NODE,
    NULL_NODE,
    LIGHT_NODE,
    NODE_ATTRIBUTE,
    CLUSTER,
    SKIN,
    ANIMATION_STACK,
    ANIMATION_LAYER,
    ANIMATION_CURVE,
    ANIMATION_CURVE_NODE
};

class PORSObject
{
public:
    PORSObject(uint64_t id, const PORSElement &element);
    virtual ~PORSObject();
    
    const PORSElement& getSourceElement() const
    {
        return mElement;
    }
    
    const uint64_t getID() const
    {
        return mID;
    }
    
    OjectType getType()
    {
        return mType;
    }
    
public:
    const PORSObject *mNodeAttribute;
    
protected:
    const PORSElement& mElement;
    const uint64_t mID;
    OjectType mType;
   
    
};

#endif /* PORSObject_hpp */
