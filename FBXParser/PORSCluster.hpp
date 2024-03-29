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
#include <vector>

#include "PORSObject.hpp"
#include "PORSUtil.hpp"
#include "Math/Matrix4x4t.hpp"

using namespace std;

class PORSCluster: public PORSObject
{
public:
    PORSCluster(uint64_t uid, const PORSElement &element);
    ~PORSCluster();
    
public:
    PORSObject *mLink;

    vector<int> mIndices;
    vector<double> mWeights;
    Matrix4x4 mTransformMatrix;
    Matrix4x4 mTransformLinkMatrix;
};

#endif /* PORSCluster_hpp */
