//
//  PORSGeometry.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/8.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSGeometry_hpp
#define PORSGeometry_hpp

#include <stdio.h>
#include <iostream>

#include "PORSObject.hpp"
#include "PORSElement.hpp"
#include "PORSScene.hpp"
#include "PORSUtil.hpp"
#include "PORSSkin.hpp"

using namespace std;

class PORSGeometry : public PORSObject
{
public:
    PORSGeometry(const PORSScene &scene, const PORSElement &element);
    
    static const int UV_MAX = 4;
    
    virtual const Vector3D *getVertices() const = 0;
    virtual int getVertexCount() const = 0;
//    virtual const Vec3 *getNormals() const = 0;
//    virtual const Vec2 *getUVs(int index = 0) const = 0;
//    virtual const Vec3 *getColors() const = 0;
//    virtual const int* getMaterials() const = 0;
    
};

enum VertexDataMapping
{
    BY_POLYGON_VERTEX,
    BY_POLYGON,
    BY_VERTEX
};

class PORSMeshGeometry : public PORSGeometry
{
public:
    
    PORSMeshGeometry(const PORSScene &scene, const PORSElement &element);
    
    int getVertexCount() const override
    {
        return (int)mVertices.size();
    }
    
    const Vector3D *getVertices() const override
    {
        return &mVertices[0];
    }
    
public:
    
    vector<Vector3D> mVertices;
    vector<Vector3D> mNormals;
    vector<Vector2D> mUVs[UV_MAX];
    vector<Vector4D> mColors;
    vector<Vector3D> mTangents;
    vector<int>  mMertials;
    
    const PORSSkin *mSkin = nullptr;
    
    vector<unsigned int> mFaces;
    vector<unsigned int> mMappingCounts;
    vector<unsigned int> mMappingOffsets;
    vector<unsigned int> mMappings;
    
};
#endif /* PORSGeometry_hpp */
