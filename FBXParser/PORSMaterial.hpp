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

#include "PORSObject.hpp"
#include "PORSTexture.hpp"

using namespace std;

class PORSMaterial: public PORSObject
{
public:
    PORSMaterial();
    ~PORSMaterial();
public:
    
    PORSTexture *mTexture;
    
};

#endif /* PORSMaterial_hpp */
