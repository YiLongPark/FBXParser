//
//  PORSRootNode.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/16.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSRootNode_hpp
#define PORSRootNode_hpp

#include <stdio.h>
#include <iostream>

//#include "PORSScene.hpp"
#include "PORSObject.hpp"
#include "PORSElement.hpp"

using namespace std;

class PORSRootNode :public PORSObject
{
public:
    PORSRootNode(uint64_t uid, const PORSElement &element);
    
    ~PORSRootNode();
    
};

#endif /* PORSRootNode_hpp */
