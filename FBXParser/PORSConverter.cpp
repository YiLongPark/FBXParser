//
//  PORSConverter.cpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/9/15.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSConverter.hpp"

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

Quaternion EulerToQuaternion(const Vector3D &rot)
{
    Matrix4x4 m;
    GetRotationMatrix(rot, m);
    
    return Quaternion(Matrix3x3(m));
}

void PORSConverter::ConverTransformOrder_TRStoSRT(QuatKey *out_quat,
                                   VectorKey *out_scale,
                                   VectorKey *out_translation,
                                   const keyFrameArrayList &scaling,
                                   const keyFrameArrayList &translation,
                                   const keyFrameArrayList &rotation,
                                   const keyTimeList &times,
                                   double &maxTime,
                                   double &minTime,
                                   const Vector3D &def_scale,
                                   const Vector3D &def_translate,
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
            out_quat[i].mValue = EulerToQuaternion(def_rotation);
        }
    }
    
    if(scaling.size())
    {
        InterpolateKeys(out_scale, times, scaling, def_scale, maxTime, minTime);
    }
    else
    {
        for(size_t i = 0; i < times.size(); i++)
        {
            out_scale[i].mTime = CONVERT_FBX_TIME(times[i] * anim_fps);
            out_scale[i].mValue = def_scale;
        }
    }
    
    if(translation.size())
    {
        InterpolateKeys(out_translation, times, translation, def_translate, maxTime, minTime);
        
    }
    else
    {
        for(size_t i = 0; i < times.size(); i++)
        {
            out_translation[i].mTime = CONVERT_FBX_TIME(times[i] * anim_fps);
            out_translation[i].mValue = def_translate;
        }
    }
    
    for(size_t i = 0; i < times.size(); i++)
    {
        Quaternion &r = out_quat[i].mValue;
        Vector3D &s = out_scale[i].mValue;
        Vector3D &t = out_translation[i].mValue;
        
        Matrix4x4 mat, temp;
        Matrix4x4::Translation(t, mat);
        
        mat *= Matrix4x4(r.GetMatrix());
        mat *= Matrix4x4::Scaling(s, temp);
        
        mat.Decompose(s, r, t);
    }
}

void PORSConverter::GenerateAnimations(PORSScene *scene)
{
    for(const PORSAnimationStack *stack : scene->mAnimationStack)
    {
        PORSAnimation *animation = new PORSAnimation();
        
        int64_t start_time = stack->mLocalStart;
        int64_t stop_time = stack->mLocalStop;
        bool has_local_startstop = start_time != 0 || stop_time != 0;
        
        double min_time = 1e10;
        double max_time = -1e10;
        
        vector<PORSNodeAnimation *> nodeAnimations;
        
        for(const PORSAnimationLayer *layer : stack->mAnimationLayerList)
        {
            for(const PORSAnimationCurveNode *node : layer->mCurveNode)
            {
                PORSNodeAnimation *node_anim = new PORSNodeAnimation();
                PORSLimbNode *bone = (PORSLimbNode *)node->mBone;
                const string boneName = bone->mName;
                
                node_anim->mNodeName = boneName;
                
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
                if(!node->mBoneLinkProperty.compare("Lcl Translation"))
                {
                    translation = getKeyFrameList(node);
                }
                if(!node->mBoneLinkProperty.compare("Lcl Scaling"))
                {
                    scaling = getKeyFrameList(node);
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
                    ConverTransformOrder_TRStoSRT(out_quat, out_scale, out_translation, scaling, translation, rotation, times, max_time, min_time, defScale, defTranslate, defRotation);
                }
                
                node_anim->mNumRotationKey = static_cast<unsigned int>(times.size());
                node_anim->mNumPositionKey = node_anim->mNumRotationKey;
                node_anim->mNumScalingKey = node_anim->mNumRotationKey;
                
                node_anim->mPositionKeys = out_translation;
                node_anim->mScalingKey = out_scale;
                node_anim->mRotationKey = out_quat;
                
                assert(node_anim);
                if(node_anim->mNumRotationKey > 0)
                {
                    nodeAnimations.push_back(node_anim);
                }
                else
                {
                    delete node_anim;
                }
                
            }
        }
        
        if(nodeAnimations.size() > 0)
        {
            animation->mNumChannel = static_cast<unsigned int>(nodeAnimations.size()) ;
            animation->mNodeAnimationChannels = new PORSNodeAnimation* [nodeAnimations.size()];
            std::swap_ranges(nodeAnimations.begin(), nodeAnimations.end(), animation->mNodeAnimationChannels);
        }
        
        double start_time_fps = has_local_startstop ? (CONVERT_FBX_TIME(start_time) * mAnimationFPS) : min_time;
        double stop_time_fps = has_local_startstop ? (CONVERT_FBX_TIME(stop_time) * mAnimationFPS) : max_time;
        
        for(unsigned int i = 0; i < animation->mNumChannel; i++)
        {
            PORSNodeAnimation *channel = animation->mNodeAnimationChannels[i];
            for(int j = 0; j < channel->mNumPositionKey; j++)
            {
                channel->mPositionKeys[j].mTime -= start_time_fps;
            }
            for(int k = 0; k < channel->mNumScalingKey; k++)
            {
                channel->mScalingKey[k].mTime -= start_time_fps;
            }
            for(int m = 0; m < channel->mNumRotationKey; m++)
            {
                channel->mRotationKey[m].mTime -= start_time_fps;
            }
        }
        
        animation->mDuration = stop_time_fps - start_time_fps;
        animation->mTicksPerSecond = mAnimationFPS;
        animation->mAnimationName = stack->mAnimationStackName;
        
        scene->mAnimations.push_back(animation);
    }

}

#pragma mark class member functions

PORSConverter::PORSConverter(PORSScene *scene)
{
    //解析FPS
    FrameRateFromSetting(scene->mGolbalSettings->TimeMode, scene->mGolbalSettings->CustomFrameRate);
    
    //解析Animation
    GenerateAnimations(scene);
}

PORSConverter::~PORSConverter()
{
    
}

void PORSConverter::FrameRateFromSetting(FrameRate fp, double customFPS)
{
    switch (fp) {
        case FrameRate_DEFAULT:
            mAnimationFPS = 1.0;
            break;
        case FrameRate_120:
            mAnimationFPS = 120.0;
            break;
        case FrameRate_100:
            mAnimationFPS = 100.0;
            break;
        case FrameRate_60:
            mAnimationFPS = 60.0;
            break;
        case FrameRate_50:
            mAnimationFPS = 50.0;
            break;
        case FrameRate_48:
            mAnimationFPS = 48.0;
            break;
        case FrameRate_30:
        case FrameRate_30_DROP:
            mAnimationFPS = 30.0;
            break;
        case FrameRate_NTSC_DROP_FRAME:
            mAnimationFPS = 29.9700262;
            break;
        case FrameRate_PAL:
            mAnimationFPS = 25.0;
            break;
        case FrameRate_CINEMA:
            mAnimationFPS = 24.0;
            break;
        case FrameRate_1000:
            mAnimationFPS = 1000.0;
            break;
        case FrameRate_CINEMA_ND:
            mAnimationFPS = 23.976;
            break;
        case FrameRate_CUSTOM:
            mAnimationFPS = customFPS;
            break;
            
        default:
            mAnimationFPS = -1.0;
            break;
    }
}
