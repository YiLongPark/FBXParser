//
//  PORSMesh.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/9/3.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSMesh.hpp"

PORSMesh::PORSMesh(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
{
    mType = MESH;
}

PORSMesh::~PORSMesh()
{
    
}
