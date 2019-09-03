//
//  PORSMesh.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/9/3.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSMesh_hpp
#define PORSMesh_hpp

#include <stdio.h>
#include <iostream>

#include "PORSObject.hpp"
#include "PORSGeometry.hpp"
#include "PORSElement.hpp"
#include "PORSMaterial.hpp"

using namespace std;

class PORSMesh: public PORSObject
{
public:
    PORSMesh(uint64_t uid, const PORSElement &element);
    ~PORSMesh();
    
public:
    const PORSMeshGeometry *mGeometry = nullptr;
    vector<const PORSMaterial*> mMaterial;
};

#endif /* PORSMesh_hpp */
