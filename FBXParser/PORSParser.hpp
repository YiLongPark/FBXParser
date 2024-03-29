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
#include "PORSConverter.hpp"


using namespace std;
//using namespace Util;

class PORSParser
{
public:
    PORSParser(const PORSElement &root, PORSScene *scene);
    ~PORSParser();
    
    
};
#endif /* PORSParser_hpp */
