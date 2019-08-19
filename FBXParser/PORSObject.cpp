//
//  PORSObject.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/6.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSObject.hpp"

PORSObject::PORSObject(uint64_t id, const PORSElement &element)
:mElement(element),
 mID(id),
 mIsNode(false)
{
    
}

PORSObject::~PORSObject()
{
    
}


