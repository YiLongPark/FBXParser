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

using namespace std;


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
};
#endif /* PORSScene_hpp */
