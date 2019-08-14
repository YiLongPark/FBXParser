//
//  PORSSkin.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSSkin_hpp
#define PORSSkin_hpp

#include <stdio.h>
#include <iostream>

#include "PORSObject.hpp"
#include "PORSCluster.hpp"

using namespace std;
class PORSSkin: public PORSObject
{
public:
    PORSSkin(const PORSScene &scene, const PORSElement &element);
    ~PORSSkin();
    
public:
    
    float mAccracy;
    vector<const PORSCluster*> mCluster;
};

#endif /* PORSSkin_hpp */
