//
//  PORSModel.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSModel_hpp
#define PORSModel_hpp

#include <stdio.h>
#include <iostream>

#include "PORSObject.hpp"
#include "PORSGeometry.hpp"
#include "PORSScene.hpp"
#include "PORSElement.hpp"
#include "PORSMaterial.hpp"

using namespace std;

class PORSModel: public PORSObject
{
public:
    PORSModel(const PORSScene &scene, const PORSElement &element);
    ~PORSModel();
    
public:
    const PORSMeshGeometry *mGeometry = nullptr;
    //const PORSScene &mScene;
    vector<const PORSMaterial*> mMaterial;
};

#endif /* PORSModel_hpp */
