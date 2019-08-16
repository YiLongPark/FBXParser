//
//  PORSRootNode.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/16.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSRootNode.hpp"

PORSRootNode::PORSRootNode(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
{
    mType = ROOTNODE;
}

PORSRootNode::~PORSRootNode()
{
    
}
