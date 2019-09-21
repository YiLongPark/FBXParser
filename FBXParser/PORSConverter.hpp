//
//  PORSConverter.hpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/9/15.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSConverter_hpp
#define PORSConverter_hpp

#include <stdio.h>

#include "PORSScene.hpp"
#include "PORSNodeAttribute.hpp"
#include "Math/Matrix3x3t.hpp"
#include "Math/Vector3D.hpp"
#include "PORSGlobalSettings.hpp"
#include "PORSAnimation.hpp"

#define CONVERT_FBX_TIME(time) static_cast<double>(time) / 46186158000L

#define AI_DEG_TO_RAD(x) ((x)*(float)0.0174532925)
#define AI_RAD_TO_DEG(x) ((x)*(float)57.2957795)

class PORSConverter
{
public:
    PORSConverter(PORSScene *scene);
    ~PORSConverter();
    
    void FrameRateFromSetting(FrameRate fp, double customFPS);
    void GenerateAnimations(PORSScene *scene);
    void ConverTransformOrder_TRStoSRT(QuatKey *out_quat,
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
                                       const Vector3D &def_rotation);
    
private:
    double mAnimationFPS;
    vector<PORSAnimation *> mAnimations;
    
};

#endif /* PORSConverter_hpp */
