//
//  PORSScene.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/1.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSScene_hpp
#define PORSScene_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "PORSConnection.hpp"
#include "PORSTakeInfo.hpp"
#include "PORSElement.hpp"
#include "PORSObject.hpp"
#include "PORSGlobalSettings.hpp"

#include "PORSMesh.hpp"
#include "PORSSkin.hpp"
#include "PORSMaterial.hpp"
#include "PORSGeometry.hpp"
#include "PORSCluster.hpp"
#include "PORSAnimationStack.hpp"
#include "PORSAnimationCurve.hpp"
#include "PORSAnimation.hpp"


using namespace std;

typedef vector<int64_t> keyTimeList;
typedef vector<float> keyValueList;

 // key (time), value, mapto (component index)
typedef tuple<std::shared_ptr<keyTimeList>, std::shared_ptr<keyValueList>, unsigned int> keyFrameList;
typedef vector<keyFrameList> keyFrameArrayList;

struct LazyObject
{
    const PORSElement *mElement;
    PORSObject *mObject;
    
};

class PORSScene
{
public:
    PORSScene();
    ~PORSScene();
    
public:
    
    vector<PORSConnection> mConnection;
    vector<PORSTakeInfo> mTakeInfo;
    unordered_map<uint64_t, LazyObject> mObjectMap;
    PORSGlobalSettings *mGolbalSettings;
    
    //将解析出来的数据临时分类存储（为组合之前）
    vector<PORSMesh *> mMeshes;
    vector<PORSSkin *> mSkin;
    vector<PORSMaterial *> mMaterial;
    vector<PORSMeshGeometry *> mGeometry;
    vector<PORSCluster* > mCluster;
    vector<PORSAnimationLayer *> mAnimationLayer;
    vector<PORSAnimationCurveNode *> mAnimationCurveNode;
    vector<PORSAnimationStack *> mAnimationStack;
    
    vector<PORSAnimation *> mAnimations;
    
};
#endif /* PORSScene_hpp */
