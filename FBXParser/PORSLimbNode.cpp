//
//  PORSLimbNode.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSLimbNode.hpp"

PORSLimbNode::PORSLimbNode(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
{
    mType = LIMB_NODE;
}

PORSLimbNode::~PORSLimbNode()
{
    
}

