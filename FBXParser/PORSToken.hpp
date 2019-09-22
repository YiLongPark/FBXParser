//
//  PORSToken.hpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/8/4.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSToken_hpp
#define PORSToken_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class PORSToken
{
public:
    PORSToken();
    ~PORSToken();
   
    uint64_t toU64();
    int64_t toI64();
    float toFloat();
    int toInt();
    double toDouble();
    bool compareWithString(const string str);
    string toString();
    
public:
    const unsigned char *mBegin;
    const unsigned char *mEnd;
    int mLenght;     //为string类型存储长度
};
#endif /* PORSToken_hpp */
