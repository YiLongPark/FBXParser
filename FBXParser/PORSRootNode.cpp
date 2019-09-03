//
//  PORSRootNode.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/16.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSRootNode.hpp"

PORSRootNode::PORSRootNode(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
{
    mType = ROOTNODE;
    mIsNode = true;
}

PORSRootNode::~PORSRootNode()
{
    
}
