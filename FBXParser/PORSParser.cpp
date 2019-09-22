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
        
//        uint32_t word;
//        memcpy(&word, coChild->mProperty->mToken.mBegin, sizeof(uint32_t));
//        //uint32_t rr= (uint32_t)coChild->mProperty->mToken.mBegin;
//        string t = string(coChild->mProperty->mToken.mBegin, coChild->mProperty->mToken.mEnd);
//        printf("from = %llu\n", tempConnection.mFrom);
//        printf("to = %llu\n", tempConnection.mTo);
        
        if(coChild->mProperty->mToken.compareWithString("OO"))
        {
            tempConnection.mType = ConnectionType::OBJECT_OBJECT;
        }
        else if (coChild->mProperty->mToken.compareWithString("OP"))
        {
            tempConnection.mType = ConnectionType::OBJECT_PROPERTY;
            tempConnection.mProperty = *coChild->mProperty->mNext->mNext->mNext;
            
//            string temp = tempConnection.mProperty.mToken.toString();
//            printf("%s\n", temp.c_str());
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

void debugTag(ObjectType type)
{
    switch (type) {
        case ROOTNODE:
            printf("ROOTNODE\n");
            break;
        case GEOMETRY:
            printf("GEOMETRY\n");
            break;
        case MATERIAL:
            printf("MATERIAL\n");
            break;
        case MESH:
            printf("MESH\n");
            break;
        case TEXTURE:
            printf("TEXTURE\n");
            break;
        case LIMB_NODE:
            printf("LIMB_NODE\n");
            break;
        case NULL_NODE:
            printf("NULL_NODE\n");
            break;
        case LIGHT_NODE:
            printf("LIGHT_NODE\n");
            break;
        case NODE_ATTRIBUTE:
            printf("NODE_ATTRIBUTE\n");
            break;
        case CLUSTER:
            printf("CLUSTER\n");
            break;
        case SKIN:
            printf("SKIN\n");
            break;
        case ANIMATION_STACK:
            printf("ANIMATION_STACK\n");
            break;
        case ANIMATION_LAYER:
            printf("ANIMATION_LAYER\n");
            break;
        case ANIMATION_CURVE:
            printf("ANIMATION_CURVE\n");
            break;
        case ANIMATION_CURVE_NODE:
            printf("ANIMATION_CURVE_NODE\n");
            break;
        default:
            printf("Error！！！！！！！\n");
            break;
    }
}

bool parseObjects(const PORSElement &root, PORSScene *scene)
{
    const PORSElement *objsElement = PORSUtil::getRequiredElement(root, "Objects");
    
   // const PORSElement *definitionsElement = PORSUtil::getRequiredElement(root, "Definitions");
    
    if(!objsElement)
    {
        return false;
    }
    
    const PORSElement *object = objsElement->mChild;
    int count = 0;
    while (object)
    {
        uint64_t id = object->mProperty->mToken.toU64();
        scene->mObjectMap[id] = {object, nullptr};
        object = object->mSibling;
        count++;
    }
    
    for(auto iter : scene->mObjectMap)
    {
       // const PORSObject *obj = nullptr;
        //std::unique_ptr<const PORSObject> obj;
        PORSObject *obj = NULL;
        
        PORSToken token = iter.second.mElement->mIDToken;
        string str = token.toString();
//        printf("this tag = %s\n", str.c_str());
//        printf("this id = %llu\n", iter.first);
        
        uint64_t UID = iter.first;
        
        if(!str.compare("Geometry"))
        {
            PORSProperty *lastProperty = iter.second.mElement->mProperty;
            while(lastProperty->mNext)
            {
                lastProperty = lastProperty->mNext;
            }
            
            if(lastProperty && lastProperty->mToken.compareWithString("Mesh"))
            {
                obj = new PORSMeshGeometry(UID, *iter.second.mElement);
            }
            
        }
        else if(!str.compare("Texture"))
        {
            obj = new PORSTexture(UID, *iter.second.mElement);
        }
        else if(!str.compare("Material"))
        {
            obj = new PORSMaterial(UID, *iter.second.mElement);
        }
        else if(!str.compare("AnimationStack"))
        {
            obj = new PORSAnimationStack(UID, *iter.second.mElement);
        }
        else if(!str.compare("AnimationLayer"))
        {
            obj = new PORSAnimationLayer(UID, *iter.second.mElement);
        }
        else if(!str.compare("AnimationCurve"))
        {
            obj = new PORSAnimationCurve(UID, *iter.second.mElement);
        }
        else if(!str.compare("AnimationCurveNode"))
        {
            obj = new PORSAnimationCurveNode(UID, *iter.second.mElement);
        }
        else if(!str.compare("NodeAttribute"))
        {
            obj = new PORSNodeAttribute(UID, *iter.second.mElement);
            
        }
        else if(!str.compare("Model"))
        {
           // obj.reset(new PORSModel(*scene, *iter.second.mElement));
            PORSProperty *classTag = iter.second.mElement->getProperty(2);
            
            if(classTag->mToken.compareWithString("Mesh"))
            {
                obj = new PORSMesh(UID, *iter.second.mElement);
            }
            else if(classTag->mToken.compareWithString("Null"))
            {
                obj=new PORSNullNode(UID, *iter.second.mElement);
            }
            else if(classTag->mToken.compareWithString("LimbNode"))
            {
                obj=new PORSLimbNode(UID, *iter.second.mElement);
            }
        
        }
        else if(!str.compare("Deformer"))
        {
            PORSProperty *classTag = iter.second.mElement->getProperty(2);
            if(classTag->mToken.compareWithString("Cluster"))
            {
                obj=new PORSCluster(UID, *iter.second.mElement);
            }
            else if(classTag->mToken.compareWithString("Skin"))
            {
                obj=new PORSSkin(UID, *iter.second.mElement);
            }
        }
        else
        {
            continue;
        }
        
        if(obj != NULL)
        {
            scene->mObjectMap[iter.first].mObject = (PORSObject *)obj;
        }
    
    }
    
    uint64_t root_UID = 0;   //添加 root node
    PORSRootNode *rootNode =  new PORSRootNode(root_UID, root);
    scene->mObjectMap[root_UID] ={&root, rootNode} ;
    
    for(const PORSConnection &con : scene->mConnection)
    {
        PORSObject *parent = scene->mObjectMap[con.mTo].mObject;
        PORSObject *child = scene->mObjectMap[con.mFrom].mObject;
        
        if(!parent || !child)
        {
            continue;
        }

        debugTag(parent->getType());
        
        switch (child->getType())
        {
            case ANIMATION_CURVE_NODE:
            {
                if(parent->mIsNode)
                {
                    PORSAnimationCurveNode *node = (PORSAnimationCurveNode *)child;
                    node->mBone = parent;
                    
                    node->mBoneLinkProperty = string(con.mProperty.mToken.mBegin, con.mProperty.mToken.mEnd);
                    
                   // printf("===%s\n", node->mBoneLinkProperty.c_str());
                }
              
            }
            break;
            case NODE_ATTRIBUTE:
            {
               // parent->mNodeAttribute = (PORSAnimationCurveNode *)child;
            }
            break;

            default:
                break;
        }

        switch (parent->getType())
        {
            case MESH:
            {
                PORSMesh *mesh = (PORSMesh *)parent;
                switch (child->getType())
                {
                    case GEOMETRY:

                        mesh->mGeometry = (PORSMeshGeometry *)child;
                        
                        scene->mMeshes.push_back(mesh);
                        break;
                    case MATERIAL:

                        mesh->mMaterial.push_back((const PORSMaterial *) child);
                        break;

                        //是否少了一个AnimCurveNode？
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
                    
                    scene->mSkin.push_back(skin);
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
                    
                    scene->mMaterial.push_back(material);

                }
                
            }
            break;

            case GEOMETRY:
            {
                PORSMeshGeometry *geometry = (PORSMeshGeometry *)parent;
                if(child->getType() == SKIN)
                {
                    geometry->mSkin = (PORSSkin *)child;
                    
                    scene->mGeometry.push_back(geometry);
                }
            }
            break;

            case CLUSTER:
            {
                PORSCluster *cluster = (PORSCluster *)parent;
                if(child->getType() == LIMB_NODE || child->getType() == MESH || child->getType() == NULL_NODE)
                {
                    cluster->mLink = child;
                    
                    scene->mCluster.push_back(cluster);
                }

            }
            break;

            case ANIMATION_LAYER:
            {
                if(child->getType() == ANIMATION_CURVE_NODE)
                {
                    ((PORSAnimationLayer *)parent)->mCurveNode.push_back((PORSAnimationCurveNode*)child);
                    
                    scene->mAnimationLayer.push_back((PORSAnimationLayer *)parent);
                }

            }
            break;

            case ANIMATION_CURVE_NODE:
            {
                PORSAnimationCurveNode *node = (PORSAnimationCurveNode *)parent;
                if(child->getType() == ANIMATION_CURVE)
                {
                    string curveTag = string(con.mProperty.mToken.mBegin, con.mProperty.mToken.mEnd);
                    node->mAnimationCurve[curveTag] = (PORSAnimationCurve *)child;

                    printf("+++%s\n", curveTag.c_str());
                    
                    scene->mAnimationCurveNode.push_back(node);
                }
            }
            break;
            case ANIMATION_STACK:
            {
                PORSAnimationStack *stack = (PORSAnimationStack *)parent;
                if(child->getType() == ANIMATION_LAYER)
                {
                    stack->mAnimationLayerList.push_back((PORSAnimationLayer *) child);
                    scene->mAnimationStack.push_back(stack);
                }
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
    
    //解析Animation相关信息
    PORSConverter converter(scene);
}


PORSParser::~PORSParser()
{
    
}


