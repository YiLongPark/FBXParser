//
//  PORSCluster.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSCluster.hpp"

Matrix4x4 ReadMatrix(const PORSElement &element)
{
    double m[16];
    PORSUtil::parseArrayRaw(*element.mProperty, &m, sizeof(double) * 16);
    
    Matrix4x4 result;
    
    result.a1 = m[0];
    result.a2 = m[1];
    result.a3 = m[2];
    result.a4 = m[3];
    
    result.b1 = m[4];
    result.b2 = m[5];
    result.b3 = m[6];
    result.b4 = m[7];
    
    result.c1 = m[8];
    result.c2 = m[9];
    result.c3 = m[10];
    result.c4 = m[11];
    
    result.d1 = m[12];
    result.d2 = m[13];
    result.d3 = m[14];
    result.d4 = m[15];
    
    result.Transpose();
    return result;
}


PORSCluster::PORSCluster(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
{
    mType = CLUSTER;
    
    const PORSElement *transformLink = PORSUtil::getRequiredElement(element, "TransformLink");
    if(transformLink && transformLink->mProperty)
    {
//        double m[16];
//        PORSUtil::parseArrayRaw(*transformLink->mProperty, &m, sizeof(double) * 16);
        mTransformLinkMatrix = ReadMatrix(*transformLink);
    }
    
    const PORSElement *transform = PORSUtil::getRequiredElement(element, "Transform");
    if(transform && transform->mProperty)
    {
//        PORSUtil::parseArrayRaw(*transform->mProperty, &mTransformMatrix, sizeof(mTransformMatrix));
        mTransformMatrix = ReadMatrix(*transform);
    }
    
    const PORSElement *indices = PORSUtil::getRequiredElement(element, "Indexes");
    if(indices && indices->mProperty)
    {
        PORSUtil::parserBinaryArray(*indices->mProperty, &mIndices);
    }

    const PORSElement *weights = PORSUtil::getRequiredElement(element, "Weights");
    if(weights &&  weights->mProperty)
    {
        PORSUtil::parserBinaryArray(*weights->mProperty, &mWeights);
    }
    
}

PORSCluster::~PORSCluster()
{
    
}
