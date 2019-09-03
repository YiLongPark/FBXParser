//
//  PORSTexture.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/13.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSTexture_hpp
#define PORSTexture_hpp

#include <stdio.h>
#include <iostream>

#include "PORSObject.hpp"
//#include "PORSScene.hpp"
#include "PORSUtil.hpp"
#include "PORSElement.hpp"

using namespace std;

class PORSTexture : public PORSObject
{
public:
    PORSTexture(uint64_t uid, const PORSElement &element);
    ~PORSTexture();
    
public:
    string mRelativeFileName;
    string mFileName;
};
#endif /* PORSTexture_hpp */
