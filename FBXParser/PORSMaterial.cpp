//
//  PORSMaterial.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/13.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSMaterial.hpp"

PORSMaterial::PORSMaterial(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
{
    mType = MATERIAL;
}

PORSMaterial::~PORSMaterial()
{
    
}
