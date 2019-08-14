//
//  PORSParser.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/12.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSParser.hpp"


double fbxTimeToSeconds(int64_t value)
{
    return double(value) / 46186158000L;
}

bool parseTakes(const PORSElement &root, PORSScene *scene)
{
    const PORSElement *takes = PORSUtil::getRequiredElement(root, "Takes");
    if(!takes)
    {
        return false;
    }
    
    const PORSElement *object = takes->mChild;
    while (object)
    {
        string tempString = string(object->mIDToken.mBegin, object->mIDToken.mEnd);
        
        if(!tempString.compare("Take"))
        {
            PORSTakeInfo take;
            take.mName = object->mProperty->mToken.toString();
            
            const  PORSElement *filename = PORSUtil::getRequiredElement(*object, "FileName");
            if(filename)
            {
                take.mFileName = filename->mProperty->mToken.toString();
            }
            
            const PORSElement *local_time = PORSUtil::getRequiredElement(*object, "LocalTime");
            if(local_time)
            {
                take.mLocalTimeFrom = fbxTimeToSeconds(local_time->mProperty->mToken.toI64());
                take.mLocalTImeTo = fbxTimeToSeconds(local_time->mProperty->mNext->mToken.toI64());
            }
            
            const PORSElement *reference_time = PORSUtil::getRequiredElement(*object, "ReferenceTime");
            if(reference_time)
            {
                take.mReferenceTimeFrom = fbxTimeToSeconds(reference_time->mProperty->mToken.toI64());
                take.mReferenceTimeTo = fbxTimeToSeconds(reference_time->mProperty->mNext->mToken.toI64());
            }
            
            scene->mTakeInfo.push_back(take);
        }
        
        object = object->mSibling;
        
    }
    
    return true;
}

//解析连接的信息
bool parseConnections(const PORSElement &root, PORSScene *sence)
{
    assert(sence);
    
    const PORSElement *connection = PORSUtil::getRequiredElement(root, "Connections");
    
    if(!connection)
    {
        return false;
    }
    
    const PORSElement *coChild = connection->mChild;
    while(coChild)
    {
        PORSConnection tempConnection;
        tempConnection.mFrom = coChild->mProperty->mNext->mToken.toU64();
        tempConnection.mTo = coChild->mProperty->mNext->mNext->mToken.toU64();
        
        uint32_t word;
        memcpy(&word, coChild->mProperty->mToken.mBegin, sizeof(uint32_t));
        //uint32_t rr= (uint32_t)coChild->mProperty->mToken.mBegin;
        string t = string(coChild->mProperty->mToken.mBegin, coChild->mProperty->mToken.mEnd);
        if(coChild->mProperty->mToken.compareWithString("OO"))
        {
            tempConnection.mType = ConnectionType::OBJECT_OBJECT;
        }
        else if (coChild->mProperty->mToken.compareWithString("OP"))
        {
            tempConnection.mType = ConnectionType::OBJECT_PROPERTY;
        }
        else
        {
            return false;
        }
        
        sence->mConnection.push_back(tempConnection);
        
        coChild = coChild->mSibling;
    }
    
    return true;
}

bool parseObjects(const PORSElement &root, PORSScene *scene)
{
    const PORSElement *objs = PORSUtil::getRequiredElement(root, "Objects");
    
    const PORSElement *object = objs->mChild;
    while (object)
    {
        uint64_t id = object->mProperty->mToken.toU64();
        scene->mObjectMap[id] = {object, nullptr};
        object = object->mSibling;
    }
    
    for(auto iter : scene->mObjectMap)
    {
       // const PORSObject *obj = nullptr;
       std::unique_ptr<const PORSObject> obj;
        
        PORSToken token = iter.second.mElement->mIDToken;
        string str = token.toString();
        if(!str.compare("Geometry"))
        {
            PORSProperty *lastProperty = iter.second.mElement->mProperty;
            while(lastProperty->mNext)
            {
                lastProperty = lastProperty->mNext;
            }
            
            if(lastProperty && lastProperty->mToken.compareWithString("Mesh"))
            {
                obj.reset( new PORSMeshGeometry(*scene, *iter.second.mElement));
            }
            
        }
        else if(!str.compare("Texture"))
        {
            obj.reset(new PORSTexture(*scene, *iter.second.mElement));
        }
        else if(!str.compare("Material"))
        {
            
        }
        else if(!str.compare("AnimationStack"))
        {
            
        }
        else if(!str.compare("AnimationLayer"))
        {
            
        }
        else if(!str.compare("AnimationCurve"))
        {
            
        }
        else if(!str.compare("AnimationCurveNode"))
        {
            
        }
        else if(!str.compare("NodeAttribute"))
        {
            PORSProperty *classTag = iter.second.mElement->getProperty(2);
            
            if(classTag)
            {
                if(classTag->mToken.compareWithString("LimbNode"))
                {
                    
                }
            }
        }
        else if(!str.compare("Model"))
        {
            
        }
        else if(!str.compare("Deformer"))
        {
            PORSProperty *classTag = iter.second.mElement->getProperty(2);
            if(classTag->mToken.compareWithString("Cluster"))
            {
                obj.reset(new PORSCluster(*scene, *iter.second.mElement));
            }
            else if(classTag->mToken.compareWithString("Skin"))
            {
                
            }
            
        }
       
    }
    
    return true;
}

void parseGlobalSettings(const PORSElement &root, PORSScene *scene)
{
    scene->mGolbalSettings = new PORSGlobalSettings(root);
}


#pragma mark class member functions

PORSParser::PORSParser(const PORSElement &root, PORSScene *scene)
{
    parseConnections(root, scene);

    parseTakes(root, scene);

    parseObjects(root, scene);
    
    parseGlobalSettings(root, scene);
}


PORSParser::~PORSParser()
{
    
}
