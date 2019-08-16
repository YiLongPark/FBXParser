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
            tempConnection.mProperty = *coChild->mProperty->mNext->mNext->mNext;
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
    const PORSElement *objsElement = PORSUtil::getRequiredElement(root, "Objects");
    
    if(!objsElement)
    {
        return false;
    }
    
    uint64_t UID = 0;   //root node
    PORSRootNode *rootNode =  new PORSRootNode(*scene, root);
    scene->mObjectMap[UID] ={&root, rootNode} ;
    
    const PORSElement *object = objsElement->mChild;
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
            obj.reset(new PORSMaterial(*scene, *iter.second.mElement));
        }
        else if(!str.compare("AnimationStack"))
        {
            obj.reset(new PORSAnimationStack(*scene, *iter.second.mElement));
        }
        else if(!str.compare("AnimationLayer"))
        {
            obj.reset(new PORSAnimationLayer(*scene, *iter.second.mElement));
        }
        else if(!str.compare("AnimationCurve"))
        {
            obj.reset(new PORSAnimationCurve(*scene, *iter.second.mElement));
        }
        else if(!str.compare("AnimationCurveNode"))
        {
            obj.reset(new PORSAnimationCurveNode(*scene, *iter.second.mElement));
        }
        else if(!str.compare("NodeAttribute"))
        {
            obj.reset(new PORSNodeAttribute(*scene, *iter.second.mElement));
            
        }
        else if(!str.compare("Model"))
        {
           // obj.reset(new PORSModel(*scene, *iter.second.mElement));
            PORSProperty *classTag = iter.second.mElement->getProperty(2);
            
            if(classTag->mToken.compareWithString("Mesh"))
            {
                obj.reset(new PORSMESH(*scene, *iter.second.mElement));
            }
            else if(classTag->mToken.compareWithString("Null"))
            {
                obj.reset(new PORSNullNode(*scene, *iter.second.mElement));
            }
            else if(classTag->mToken.compareWithString("LimbNode"))
            {
                obj.reset(new PORSLimbNode(*scene, *iter.second.mElement));
            }
            
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
                obj.reset(new PORSSkin(*scene, *iter.second.mElement));
            }
            
        }
        
        scene->mObjectMap[iter.first].mObject = (PORSObject *)obj.get();
    
    }
    
    for(const PORSConnection &con : scene->mConnection)
    {
        PORSObject *parent = scene->mObjectMap[con.mTo].mObject;
        PORSObject *child = scene->mObjectMap[con.mFrom].mObject;
        
        if(!parent || !child)
        {
            continue;
        }
        
        switch (child->getType())
        {
            case ANIMATION_CURVE_NODE:
            {
                PORSAnimationCurveNode *node = (PORSAnimationCurveNode *)child;
                node->mBone = parent;
                
                node->mBoneLinkProperty = string(con.mProperty.mToken.mBegin, con.mProperty.mToken.mEnd);
            }
            break;
            case NODE_ATTRIBUTE:
            {
                parent->mNodeAttribute = (PORSAnimationCurveNode *)child;
            }
            break;
                
            default:
                break;
        }
        
        
        switch (parent->getType())
        {
            case MESH:
            {
                PORSModel *mesh = (PORSModel *)parent;
                switch (child->getType())
                {
                    case GEOMETRY:
                        
                        mesh->mGeometry = (PORSMeshGeometry *)child;
                        break;
                    case MATERIAL:
                        
                        mesh->mMaterial.push_back((PORSMaterial *) child);
                        break;
                        
                    default:
                        break;
                }
                
            }
            break;
                
            case SKIN:
            {
                PORSSkin *skin = (PORSSkin *)parent;
                if(child->getType() == CLUSTER)
                {
                    PORSCluster *cluster = (PORSCluster *)child;
                    skin->mCluster.push_back(cluster);
                }
                
            }
            break;
                
            case MATERIAL:
            {
                PORSMaterial *material = (PORSMaterial *)parent;
                if(child->getType() == TEXTURE)
                {
                    string textureTag = string(con.mProperty.mToken.mBegin, con.mProperty.mToken.mEnd);
                    printf("material %s", textureTag.c_str());
                    
                    const PORSTexture *texture = (PORSTexture *)child;
                    material->mTexture[textureTag] = texture;
                    
                }
            }
            break;
                
            case GEOMETRY:
            {
                PORSMeshGeometry *geometry = (PORSMeshGeometry *)parent;
                if(child->getType() == SKIN)
                {
                    geometry->mSkin = (PORSSkin *)child;
                }
            }
            break;
                
            case CLUSTER:
            {
                PORSCluster *cluster = (PORSCluster *)parent;
                if(child->getType() == LIMB_NODE || child->getType() == MESH || child->getType() == NULL_NODE)
                {
                    cluster->mLink = child;
                }

            }
            break;
                
            case ANIMATION_LAYER:
            {
                if(child->getType() == ANIMATION_CURVE_NODE)
                {
                    ((PORSAnimationLayer *)parent)->mCurveNode.push_back((PORSAnimationCurveNode*)child);
                }
                
            }
            break;
                
            case ANIMATION_CURVE_NODE:
            {
                
            }
            break;
            default:
                break;
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
