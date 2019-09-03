//
//  PORSGeometry.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/8.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSGeometry.hpp"
#include "PORSUtil.hpp"


template <typename T>
void resolveVertexDataArray(const PORSElement &element,vector<T> &dataOut, const char *dataElementName, const char *indexDataElementName, size_t vertexCount, const vector<uint32_t>& mappingCounts, const vector<uint32_t>& mappingOffsets, vector<uint32_t>& mappings)
{
    const PORSElement *dataElement = PORSUtil::getRequiredElement(element, dataElementName);
  
    const PORSElement *mappingElement = PORSUtil::getRequiredElement(element, "MappingInformationType");
    const PORSElement *referenceElement = PORSUtil::getRequiredElement(element, "ReferenceInformationType");
    
    bool isDirect = referenceElement->mProperty->mToken.compareWithString("Direct");
    bool isIndexToDirect = referenceElement->mProperty->mToken.compareWithString("IndexToDirect");
    
    const PORSElement *indicesElement = PORSUtil::getRequiredElement(element, indexDataElementName);
    
    if(mappingElement->mProperty->mToken.compareWithString("ByVertice") && isDirect)
    {
        vector<T> tempData;
        PORSUtil::parseDoubleVecData(*dataElement->mProperty, &tempData);
        
        dataOut.resize(vertexCount);
        
        int dataSize = (int)tempData.size();
        for(int i = 0; i < dataSize; i++)
        {
            const unsigned int istart = mappingOffsets[i];
            const unsigned int iend = istart + mappingCounts[i];
            
            for(unsigned int j = istart; j < iend; j++)
            {
                dataOut[mappings[j]] = tempData[i];
            }
        }
    }
    else if(mappingElement->mProperty->mToken.compareWithString("ByVertice") && isIndexToDirect)
    {
        vector<T> tempData;
        PORSUtil::parseDoubleVecData(*dataElement->mProperty, &tempData);
        
        dataOut.resize(vertexCount);
        
        vector<int> uvIndices;
        PORSUtil::parserBinaryArray(*indicesElement->mProperty, &uvIndices);
        
        int dataSize = (int)uvIndices.size();
        for(int i = 0; i < dataSize; i++)
        {
            const unsigned int istart = mappingOffsets[i];
            const unsigned int iend = istart + mappingCounts[i];
            
            for(unsigned int j = istart; j < iend; j++)
            {
                dataOut[mappings[i]] = tempData[uvIndices[i]];
            }
        }
    }
    else if(mappingElement->mProperty->mToken.compareWithString("ByPolygonVertex") && isDirect)
    {
        vector<T>tempData;
        PORSUtil::parseDoubleVecData(*dataElement->mProperty, &tempData);
        
        dataOut.swap(tempData);
    }
    else if(mappingElement->mProperty->mToken.compareWithString("ByPolygonVertex") && isIndexToDirect)
    {
        vector<T>tempData;
        PORSUtil::parseDoubleVecData(*dataElement->mProperty, &tempData);
        
        dataOut.resize(vertexCount);
        
        vector<int> uvIndices;
        PORSUtil::parserBinaryArray(*indicesElement->mProperty, &uvIndices);
        
        const T empty{};
        unsigned int next = 0;
        for(int i: uvIndices)
        {
            if(-1 == i)
            {
                dataOut[next++] = empty;
                continue;
            }
            
            dataOut[next++] = tempData[i];
        }
    }
   
    
}

int getTriCountFromPoly(const vector<int>& indices, int *index)
{
    int count = 1;
    while(indices[*index + 1 + count] >= 0)
    {
        count++;
    }
    
    *index += 2 + count;
    return count;
}


PORSGeometry::PORSGeometry(uint64_t uid, const PORSElement &element):
PORSObject(uid, element) //默认id先传入0
{
    
}

PORSMeshGeometry::PORSMeshGeometry(uint64_t uid, const PORSElement &element):
PORSGeometry(uid, element)
{
    assert(element.mProperty);
    mType = GEOMETRY;
    
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
    
    //LayerElementMaterial
    const PORSElement *layerMarterialElement = PORSUtil::getRequiredElement(element, "LayerElementMaterial");
    if(layerMarterialElement)
    {
//        vector<int> tempMaterials;
//        resolveVertexDataArray(*layerMarterialElement, tempMaterials, "UV", "UVIndex", mVertices.size(), mMappingCounts, mMappingOffsets, mMappings);
        
        const PORSElement *mappingElement = PORSUtil::getRequiredElement(*layerMarterialElement, "MappingInformationType");

        const PORSElement *referenceElement = PORSUtil::getRequiredElement(*layerMarterialElement, "ReferenceInformationType");

        vector<int> tempData;

        string tempStr1 = mappingElement->mProperty->mToken.toString();
        string tempStr2 = referenceElement->mProperty->mToken.toString();
        if(mappingElement->mProperty->mToken.compareWithString("ByPolygon") && referenceElement->mProperty->mToken.compareWithString("IndexToDirect"))
        {
            mMertials.resize(mVertices.size() / 3,  -1);

            const PORSElement *indicesElement = PORSUtil::getRequiredElement(*layerMarterialElement, "Materials");

            PORSUtil::parserBinaryArray(*indicesElement->mProperty, &tempData);

            int temp = 0;
            size_t count = tempData.size();

            for(size_t i = 0; i < count; i++)
            {
                int tri_count = getTriCountFromPoly(originalIndices, &temp);
                
                for(int j = 0; j < tri_count; j++)
                {
                    mMertials.push_back(tempData[j]);
                }
            }

        }
        else
        {
            //AllSame
        }
    }
    
    //LayerElementUV
    const PORSElement *layerUVElement = PORSUtil::getRequiredElement(element, "LayerElementUV");

    while (layerUVElement)
    {
        const int uvIndex = layerUVElement->mProperty ? layerUVElement->mProperty->mToken.toInt() : 0;

        if(uvIndex >= 0 && uvIndex < UV_MAX)
        {
            //vector<Vector2D> &UVs = mUVs[uvIndex];

            resolveVertexDataArray(*layerUVElement, mUVs[uvIndex], "UV", "UVIndex", mVertices.size(), mMappingCounts, mMappingOffsets, mMappings);
        }

        string tempStr;
        do
        {
            layerUVElement = layerUVElement->mSibling;
            
        }while (layerUVElement &&  string(layerUVElement->mIDToken.mBegin, layerUVElement->mIDToken.mEnd).compare("LayerElementUV"));

    }


    //LayerElementNormal
    const PORSElement *layerNormalElement = PORSUtil::getRequiredElement(element, "LayerElementNormal");
    if(layerNormalElement)
    {
        resolveVertexDataArray(*layerNormalElement, mNormals, "Normals",
                               "NormalsIndex", mVertices.size(), mMappingCounts, mMappingOffsets, mMappings);
    }

    //LayerElementTangent
    const PORSElement *layerTangentsElement = PORSUtil::getRequiredElement(element, "LayerElementTangent");
    if(layerTangentsElement)
    {
        if(PORSUtil::getRequiredElement(*layerTangentsElement, "Tangents"))
        {
            resolveVertexDataArray(*layerTangentsElement, mTangents, "Tangents", "TangentsIndex", mVertices.size(), mMappingCounts, mMappingOffsets, mMappings);
        }
        else
        {
            resolveVertexDataArray(*layerTangentsElement, mTangents, "Tangent", "TangentIndex", mVertices.size(), mMappingCounts, mMappingOffsets, mMappings);
        }

    }

    //LayerElementColor
    const PORSElement *layerColorElement = PORSUtil::getRequiredElement(element, "LayerElementColor");
    if(layerColorElement)
    {
        resolveVertexDataArray(*layerColorElement, mColors, "Colors",
                               "ColorIndex", mVertices.size(), mMappingCounts, mMappingOffsets, mMappings);
    }
    
    //LayerElementBinormal

}


