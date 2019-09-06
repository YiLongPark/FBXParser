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
        printf("from = %llu\n", tempConnection.mFrom);
        printf("to = %llu\n", tempConnection.mTo);
        
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
        printf("this tag = %s\n", str.c_str());
        printf("this id = %llu\n", iter.first);
        
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
                    
                    printf("===%s\n", node->mBoneLinkProperty.c_str());
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


keyTimeList getKeyTimeList(const keyFrameArrayList &inputs)
{
    assert(!inputs.empty());
    
    keyTimeList keys;
    
    size_t estimate = 0;
    for(const keyFrameList &kf1 : inputs)
    {
        estimate = std::max(estimate, std::get<0>(kf1)->size());
    }
    
    keys.reserve(estimate);
    
    vector <unsigned int> next_pos;
    next_pos.resize(inputs.size(), 0);
    
    const size_t count = inputs.size();
    while(true)
    {
        int64_t min_tick = std::numeric_limits<int64_t>::max();
        for(size_t i = 0; i < count; i++)
        {
            const keyFrameList &kf1 = inputs[i];
            if(std::get<0>(kf1)->size() > next_pos[i] && std::get<0>(kf1)->at(next_pos[i]) < min_tick)
            {
                min_tick = std::get<0>(kf1)->at(next_pos[i]);
            }
        }
        
        if(min_tick == std::numeric_limits<int64_t>::max())
        {
            break;
        }
        
        keys.push_back(min_tick);
        
        for(size_t i = 0; i <  count ; i++)
        {
            const keyFrameList &kf1 = inputs[i];
            
            while (std::get<0>(kf1)->size() > next_pos[i] && std::get<0>(kf1)->at(next_pos[i]) == min_tick) {
                ++next_pos[i];
            }
        }
    }
    
    return keys;
}

keyFrameArrayList getKeyFrameList(const PORSAnimationCurveNode *node)
{
    keyFrameArrayList inputs;
    inputs.reserve(3);   //临时设置
    
    const AnimationCurveMap &curves = node->mAnimationCurve;
    for(const AnimationCurveMap::value_type &kv : curves)
    {
        unsigned int mapto;
        if(!kv.first.compare("d|X"))
        {
            mapto = 0;
        }
        else if(!kv.first.compare("d|Y"))
        {
            mapto = 1;
        }
        else if(!kv.first.compare("d|Z"))
        {
            mapto = 2;
        }
        else
        {
            //warning
        }
        
        const PORSAnimationCurve* curve = kv.second;
        
        shared_ptr<keyTimeList> keyTime(new keyTimeList());
        shared_ptr<keyValueList> keyValue(new keyValueList());
        
        const size_t count = curve->mKeyTimeList.size();
        
        keyTime->reserve(count);
        keyValue->reserve(count);
        
        for(int i = 0; i < count; i++)
        {
            int64_t time = curve->mKeyTimeList.at(i);
            float value = curve->mKeyValueList.at(i);
            
            keyTime->push_back(time);
            keyValue->push_back(value);
        }
        
        inputs.push_back(make_tuple(keyTime, keyValue, mapto));
        
    }
    
    return inputs;
}


void InterpolateKeys(VectorKey *valOut,
                     const keyTimeList &keys,
                     const keyFrameArrayList &inputs,
                     const Vector3D &def_value,
                     double &max_time,
                     double &min_time)
{
    assert(!keys.empty());
    assert(nullptr != valOut);
    
    vector<unsigned int> next_pos;
    const size_t count(inputs.size());
    next_pos.resize(inputs.size(), 0);
    
    for(keyTimeList::value_type time : keys)
    {
        double result[3] = {def_value.x, def_value.y, def_value.z};
        
        for(int i = 0; i < count; i++)
        {
            const keyFrameList &kfl = inputs[i];
            
            const size_t ksize = std::get<0>(kfl)->size();
            if(0 == ksize)
            {
                continue;
            }
            
            if(ksize > next_pos[i] && std::get<0>(kfl)->at(next_pos[i]) == time)
            {
                ++next_pos[i];
            }
            
            const size_t id0 = next_pos[i] > 0 ? next_pos[i] - 1 : 0;
            const size_t id1 = next_pos[i] == ksize ?  ksize - 1 : next_pos[i];
            
            // use lerp for interpolation
            const keyValueList::value_type valueA = std::get<1>(kfl)->at(id0);
            const keyValueList::value_type valueB = std::get<1>(kfl)->at(id1);
            
            const keyTimeList::value_type timeA = std::get<0>(kfl)->at(id0);
            const keyTimeList::value_type timeB = std::get<0>(kfl)->at(id1);
            
            const double factor = timeB == timeA ? double(0.) : static_cast<double>((time - timeA)) / (timeB - timeA);
            const double interpValue = static_cast<double>(valueA + (valueB - valueA) * factor);
            
            result[std::get<2>(kfl)] = interpValue;
        }
        
        // magic value to convert fbx times to seconds
        int anim_fps = 30;
        valOut->mTime = CONVERT_FBX_TIME(time) * anim_fps;
        
        min_time = std::min(min_time, valOut->mTime);
        max_time = std::max(max_time, valOut->mTime);
        
        valOut->mValue.x = result[0];
        valOut->mValue.y = result[1];
        valOut->mValue.z = result[2];
        
        ++valOut;
    }

}

void GetRotationMatrix(const Vector3D& rotation, Matrix4x4& out)
{
//    if (mode == Model::RotOrder_SphericXYZ) {
//        FBXImporter::LogError("Unsupported RotationMode: SphericXYZ");
//        out = aiMatrix4x4();
//        return;
//    }
    
    const float angle_epsilon = 1e-6f;
    
    out = Matrix4x4();
    
    bool is_id[3] = { true, true, true };
    
    Matrix4x4 temp[3];
    if (std::fabs(rotation.z) > angle_epsilon) {
        Matrix4x4::RotationZ(AI_DEG_TO_RAD(rotation.z), temp[2]);
        is_id[2] = false;
    }
    if (std::fabs(rotation.y) > angle_epsilon) {
        Matrix4x4::RotationY(AI_DEG_TO_RAD(rotation.y), temp[1]);
        is_id[1] = false;
    }
    if (std::fabs(rotation.x) > angle_epsilon) {
        Matrix4x4::RotationX(AI_DEG_TO_RAD(rotation.x), temp[0]);
        is_id[0] = false;
    }
    
    int order[3] = { -1, -1, -1 };
    
    // note: rotation order is inverted since we're left multiplying as is usual in assimp
//    switch (mode)
//    {
//        case Model::RotOrder_EulerXYZ:
//            order[0] = 2;
//            order[1] = 1;
//            order[2] = 0;
//            break;
//
//        case Model::RotOrder_EulerXZY:
//            order[0] = 1;
//            order[1] = 2;
//            order[2] = 0;
//            break;
//
//        case Model::RotOrder_EulerYZX:
//            order[0] = 0;
//            order[1] = 2;
//            order[2] = 1;
//            break;
//
//        case Model::RotOrder_EulerYXZ:
//            order[0] = 2;
//            order[1] = 0;
//            order[2] = 1;
//            break;
//
//        case Model::RotOrder_EulerZXY:
//            order[0] = 1;
//            order[1] = 0;
//            order[2] = 2;
//            break;
//
//        case Model::RotOrder_EulerZYX:
//            order[0] = 0;
//            order[1] = 1;
//            order[2] = 2;
//            break;
//
//        default:
//            ai_assert(false);
//            break;
//    }
    
    order[0] = 2;
    order[1] = 1;
    order[2] = 0;
    
    assert(order[0] >= 0);
    assert(order[0] <= 2);
    assert(order[1] >= 0);
    assert(order[1] <= 2);
    assert(order[2] >= 0);
    assert(order[2] <= 2);
    
    if (!is_id[order[0]]) {
        out = temp[order[0]];
    }
    
    if (!is_id[order[1]]) {
        out = out * temp[order[1]];
    }
    
    if (!is_id[order[2]]) {
        out = out * temp[order[2]];
    }
}

void InterpolateKeys(QuatKey* valOut,
                     const keyTimeList& keys,
                     const keyFrameArrayList& inputs,
                     const Vector3D& def_value,
                     double& maxTime,
                     double& minTime)
{
    assert(!keys.empty());
    assert(nullptr != valOut);
    
    std::unique_ptr<VectorKey[]> temp(new VectorKey[keys.size()]);
    InterpolateKeys(temp.get(), keys, inputs, def_value, maxTime, minTime);
    
    Matrix4x4 m;
    
    Quaternion lastq;
    
    for (size_t i = 0, c = keys.size(); i < c; ++i) {
        
        valOut[i].mTime = temp[i].mTime;
        
        GetRotationMatrix(temp[i].mValue, m);
        Quaternion quat = Quaternion(Matrix3x3(m));
        
        // take shortest path by checking the inner product
        // http://www.3dkingdoms.com/weekly/weekly.php?a=36
        if (quat.x * lastq.x + quat.y * lastq.y + quat.z * lastq.z + quat.w * lastq.w < 0)
        {
            quat.x = -quat.x;
            quat.y = -quat.y;
            quat.z = -quat.z;
            quat.w = -quat.w;
        }
        lastq = quat;
        
        valOut[i].mValue = quat;
    }
}


void InterpolateKeys(QuatKey *valOut,
                     const keyTimeList &keys,
                     const keyValueList &inputs,
                     const Vector3D& def_value,
                     double &maxTime,
                     double &minTime)
{
    assert(!keys.empty());
    assert(nullptr != valOut);
    
    std::unique_ptr<VectorKey[]> temp(new VectorKey[keys.size()]);
    
    
    
}

void converTransformOrder_TrstoSRT(QuatKey *out_quat,
                                   VectorKey *out_scale,
                                   VectorKey *out_translation,
                                   const keyFrameArrayList &scaling,
                                   const keyFrameArrayList &translation,
                                   const keyFrameArrayList &rotation,
                                   const keyTimeList &times,
                                   double & maxTime,
                                   double &minTime,
                                   const Vector3D &def_scale,
                                   const Vector3D *def_translate,
                                   const Vector3D &def_rotation)
{
    int anim_fps = 30;   //临时fps为30
    if(rotation.size())
    {
        InterpolateKeys(out_quat, times, rotation, def_rotation, maxTime, minTime);
    }
    else
    {
        for(size_t i = 0; i < times.size(); i++)
        {
            out_quat[i].mTime = CONVERT_FBX_TIME(times[i]) * anim_fps;
        }
    }
    
    if(scaling.size())
    {
        
    }
    else
    {
        
    }
    
    if(translation.size())
    {
        
    }
    else
    {
        
    }
}


void converAnimations(PORSScene *scene)
{
    for(const PORSAnimationStack *stack : scene->mAnimationStack)
    {
        for(const PORSAnimationLayer *layer : stack->mAnimationLayerList)
        {
            for(const PORSAnimationCurveNode *node : layer->mCurveNode)
            {
                PORSLimbNode *bone = (PORSLimbNode *)node->mBone;
                const string boneName = bone->mName;
                
                Vector3D defScale = bone->getLocalScaling();
                Vector3D defTranslate = bone->getLocalTranslation();
                Vector3D defRotation = bone->getLocalRotation();
                
                keyFrameArrayList scaling;
                keyFrameArrayList translation;
                keyFrameArrayList rotation;
                
                if(!node->mBoneLinkProperty.compare("Lcl Rotation") )
                {
                    rotation = getKeyFrameList(node);
                }
                
                keyFrameArrayList joined;
                joined.insert(joined.end(), scaling.begin(), scaling.end());
                joined.insert(joined.end(), translation.begin(), translation.end());
                joined.insert(joined.end(), rotation.begin(), rotation.end());
                
                const keyTimeList &times = getKeyTimeList(joined);
                
                QuatKey *out_quat = new QuatKey[times.size()];
                VectorKey *out_scale = new VectorKey[times.size()];
                VectorKey *out_translation = new VectorKey[times.size()];
                
                if(times.size())
                {
                    
                }
                
            }
        }
    }
}

#pragma mark class member functions

PORSParser::PORSParser(const PORSElement &root, PORSScene *scene)
{
    parseConnections(root, scene);

    parseTakes(root, scene);

    parseObjects(root, scene);
    
    parseGlobalSettings(root, scene);
    
    converAnimations(scene);
}


PORSParser::~PORSParser()
{
    
}


