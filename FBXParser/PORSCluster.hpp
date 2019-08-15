//
//  PORSCluster.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSCluster_hpp
#define PORSCluster_hpp

#include <stdio.h>
#include <iostream>

#include "PORSObject.hpp"
#include "PORSScene.hpp"
#include "PORSUtil.hpp"


using namespace std;

class PORSCluster: public PORSObject
{
public:
    PORSCluster(const PORSScene &scene, const PORSElement &element);
    ~PORSCluster();
    
public:
    PORSObject *mLink;

    vector<int> mIndices;
    vector<double> mWeights;
    Matrix4x4 mTransformMatrix;
    Matrix4x4 mTransformLinkMatrix;
};

#endif /* PORSCluster_hpp */
