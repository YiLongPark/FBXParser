//
//  PORSMaterial.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/13.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSMaterial_hpp
#define PORSMaterial_hpp

#include <stdio.h>
#include <iostream>
#include <map>

//#include "PORSObject.hpp"
#include "PORSTexture.hpp"

using namespace std;

typedef map<string, const PORSTexture*> TextureMap;

class PORSMaterial: public PORSObject
{
public:
    PORSMaterial(uint64_t uid, const PORSElement &element);
    ~PORSMaterial();
public:
    
    ColorValue mAmbientColor;
    ColorValue mDiffuseColor;
    ColorValue mSpecularColor;
    TextureMap mTexture;
    
};

#endif /* PORSMaterial_hpp */
