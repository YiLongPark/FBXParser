//
//  PORSGlobalSettings.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSGlobalSettings_hpp
#define PORSGlobalSettings_hpp

#include <stdio.h>
#include <iostream>

#include "PORSObject.hpp"
#include "PORSElement.hpp"
#include "PORSUtil.hpp"

using namespace std;

enum FrameRate
{
    FrameRate_DEFAULT = 0,
    FrameRate_120 = 1,
    FrameRate_100 = 2,
    FrameRate_60 = 3,
    FrameRate_50 = 4,
    FrameRate_48 = 5,
    FrameRate_30 = 6,
    FrameRate_30_DROP = 7,
    FrameRate_NTSC_DROP_FRAME = 8,
    FrameRate_NTSC_FULL_FRAME = 9,
    FrameRate_PAL = 10,
    FrameRate_CINEMA = 11,
    FrameRate_1000 = 12,
    FrameRate_CINEMA_ND = 13,
    FrameRate_CUSTOM = 14,
};

class PORSGlobalSettings
{
public:
    PORSGlobalSettings(const PORSElement &root);
    ~PORSGlobalSettings();
    
public:
    int UPAxis;
    int UPAxisSign;
    int FrontAxis;
    int FrontAxisSign;
    int CoordAxis;
    int CoordAxisSign;
    int OriginalUpAxis;
    int OriginalUpAxisSign;
    float UnitScaleFactor;
    float OriginalUnitScaleFactor;
    Vector3D AmbientColor;
    string DefaultCamera;
    FrameRate TimeMode;
    uint64_t TimeSpanStart;
    uint64_t TimeSpanStop;
    float CustomFrameRate;
};


#endif /* PORSGlobalSettings_hpp */
