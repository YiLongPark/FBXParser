//
//  PORSTakeInfo.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/5.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSTakeInfo_hpp
#define PORSTakeInfo_hpp

#include <stdio.h>
#include <iostream>
#include "PORSToken.hpp"

using namespace std;

class PORSTakeInfo
{
public:
    PORSTakeInfo();
    ~PORSTakeInfo();
    
public:
    
    string mName;
    string mFileName;
    double mLocalTimeFrom;
    double mLocalTImeTo;
    double mReferenceTimeFrom;
    double mReferenceTimeTo;
    
};

#endif /* PORSTakeInfo_hpp */
