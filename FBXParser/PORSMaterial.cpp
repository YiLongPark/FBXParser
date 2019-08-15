//
//  PORSMaterial.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/13.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSMaterial.hpp"

PORSMaterial::PORSMaterial(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
{
    mType = MATERIAL;
}

PORSMaterial::~PORSMaterial()
{
    
}
