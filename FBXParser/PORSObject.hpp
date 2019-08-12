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
    
protected:
    const PORSElement& mElement;
    const uint64_t mID;
    
};
#endif /* PORSObject_hpp */
