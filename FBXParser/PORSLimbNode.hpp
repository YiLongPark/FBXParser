//
//  PORSLimbNode.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSLimbNode_hpp
#define PORSLimbNode_hpp

#include <stdio.h>
#include <iostream>

#include "PORSObject.hpp"
#include "PORSScene.hpp"

using namespace std;

class PORSLimbNode: public PORSObject
{
public:
    PORSLimbNode(const PORSScene &scene, const PORSElement &element);
    ~PORSLimbNode();
    
public:
    
};

#endif /* PORSLimbNode_hpp */
