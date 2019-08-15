//
//  PORSCluster.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSCluster.hpp"

PORSCluster::PORSCluster(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
{
    mType = CLUSTER;
    
    const PORSElement *transformLink = PORSUtil::getRequiredElement(element, "TransformLink");
    if(transformLink && transformLink->mProperty)
    {
        PORSUtil::parseArrayRaw(*transformLink->mProperty, &mTransformLinkMatrix, sizeof(mTransformLinkMatrix));
    }
    
    const PORSElement *transform = PORSUtil::getRequiredElement(element, "Transform");
    if(transform && transform->mProperty)
    {
        PORSUtil::parseArrayRaw(*transform->mProperty, &mTransformMatrix, sizeof(mTransformMatrix));
    }
    
   // vector<int> old_indices;
    const PORSElement *indices = PORSUtil::getRequiredElement(element, "Indexes");
    if(indices && indices->mProperty)
    {
        PORSUtil::parserBinaryArray(*indices->mProperty, &mIndices);
    }
    
   // vector<double> old_weights;
    const PORSElement *weights = PORSUtil::getRequiredElement(element, "Weights");
    if(weights &&  weights->mProperty)
    {
        PORSUtil::parserBinaryArray(*weights->mProperty, &mWeights);
    }
    
//    mIndices.reserve(old_indices.size());
//    mWeights.reserve(old_weights.size());

}

PORSCluster::~PORSCluster()
{
    
}
