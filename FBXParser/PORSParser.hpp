//
//  PORSParser.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/12.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSParser_hpp
#define PORSParser_hpp

#include <stdio.h>
#include <iostream>

#include "PORSElement.hpp"
#include "PORSTakeInfo.hpp"
#include "PORSScene.hpp"
#include "PORSGeometry.hpp"
#include "PORSUtil.hpp"
#include "PORSTexture.hpp"
#include "PORSCluster.hpp"
#include "PORSSkin.hpp"
#include "PORSMaterial.hpp"
#include "PORSAnimationCurve.hpp"
#include "PORSAnimationStack.hpp"
#include "PORSNodeAttribute.hpp"
#include "PORSMesh.hpp"
#include "PORSToken.hpp"
#include "PORSRootNode.hpp"
#include "Math/Matrix4x4t.hpp"
#include "Math/Matrix3x3t.hpp"


#define CONVERT_FBX_TIME(time) static_cast<double>(time) / 46186158000L

#define AI_DEG_TO_RAD(x) ((x)*(float)0.0174532925)
#define AI_RAD_TO_DEG(x) ((x)*(float)57.2957795)

using namespace std;
//using namespace Util;

class PORSParser
{
public:
    PORSParser(const PORSElement &root, PORSScene *scene);
    ~PORSParser();
    
    
};
#endif /* PORSParser_hpp */
