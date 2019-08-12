//
//  PORSGeometry.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/8.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSGeometry.hpp"

PORSGeometry::PORSGeometry(const PORSScene &scene, const PORSElement &element):
PORSObject(0, element) //默认id先传入0
{
    
}

PORSMeshGeometry::PORSMeshGeometry(const PORSScene &scene, const PORSElement &element):
PORSGeometry(scene, element)
{
    assert(element.mProperty);
    
    const PORSElement *vertices_element = PORSUtil::getRequiredElement(element, "Vertices");
    
    const PORSElement *polys_element = PORSUtil::getRequiredElement(element, "PolygonVertexIndex");
    
    //unique_ptr<PORSMeshGeometry> geometry = make_unique<PORSMeshGeometry>(scene, element);
    
    vector<Vector3D> vertices;
    
    PORSUtil::parseDoubleVecData(*vertices_element->mProperty, &vertices);
    
    vector<int> originalIndices;
    PORSUtil::parserBinaryArray(*polys_element->mProperty, &originalIndices);
    
    mVertices.reserve(originalIndices.size());
    mFaces.reserve(originalIndices.size() / 3);
    
    mMappingOffsets.resize(vertices.size());
    mMappingCounts.resize(vertices.size(), 0);
    mMappings.resize(originalIndices.size());
    
    unsigned int count = 0;
    for(int index: originalIndices)
    {
        const int absi = index < 0 ? (-index - 1) : index;
        
        mVertices.push_back(vertices[absi]);
        ++count;
        
        ++mMappingCounts[absi];
        
        if(index < 0 )
        {
            mFaces.push_back(count);
            count = 0;
        }
    }
    
    unsigned int cursor = 0;
    size_t verSize = vertices.size();
    for(size_t i = 0; i < verSize; i++)
    {
        mMappingOffsets[i] = cursor;
        cursor += mMappingCounts[i];
        
        mMappingCounts[i] = 0;
    }
    
    cursor = 0;
    for(int index : originalIndices)
    {
        const int absi = index < 0 ? (-index - 1) : index;
        mMappings[mMappingOffsets[absi] + mMappingCounts[absi]++] = cursor++;
    }
    
    
    const PORSElement *layerMarterialElement = PORSUtil::getRequiredElement(element, "LayerElementMaterial");
    if(layerMarterialElement)
    {
        const PORSElement *mappingElement = PORSUtil::getRequiredElement(*layerMarterialElement, "MappingInformationType");
        
        const PORSElement *referenceElement = PORSUtil::getRequiredElement(*layerMarterialElement, "ReferenceInformationType");
        
        vector<int> tempData;
        
        uint32_t word;
        memcpy(&word,  mappingElement->mProperty->mToken.mBegin, sizeof(uint32_t));
        
        uint32_t word1;
        memcpy(&word1,  referenceElement->mProperty->mToken.mBegin, sizeof(uint32_t));
        string tempStr1 = mappingElement->mProperty->mToken.toString();
        string tempStr2 = referenceElement->mProperty->mToken.toString();
        if(!tempStr1.compare("ByPolygon") && !tempStr2.compare("IndexToDirect"))
        {
            mMertials.resize(mVertices.size() / 3,  -1);
            
            const PORSElement *indicesElement = PORSUtil::getRequiredElement(*layerMarterialElement, "Materials");
            
            PORSUtil::parserBinaryArray(*indicesElement->mProperty, &tempData);
            
            int temp = 0;
            size_t count = tempData.size();
            
            for(size_t i = 0; i < count; i++)
            {
                
            }
            
        }
        else
        {
            //AllSame
        }
    }
    
    const PORSElement *layerUVElement = PORSUtil::getRequiredElement(element, "LayerElementUV");
    
    
}
