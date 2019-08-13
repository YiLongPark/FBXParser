//
//  PORSParser.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/12.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSParser_hpp
#define PORSParser_hpp

#include <stdio.h>
#include <iostream>

#include "PORSElement.hpp"
#include "PORSTakeInfo.hpp"
#include "PORSScene.hpp"
#include "PORSGeometry.hpp"
#include "PORSUtil.hpp"
#include "PORSTexture.hpp"

using namespace std;
//using namespace Util;

class PORSParser
{
public:
    PORSParser(const PORSElement &root, PORSScene *scene);
    ~PORSParser();
    
    
};
#endif /* PORSParser_hpp */
