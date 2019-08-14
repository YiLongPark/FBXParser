//
//  PORSToken.cpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/8/4.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSToken.hpp"

PORSToken::PORSToken()
{
    mBegin = nullptr;
    mEnd = nullptr;
}

PORSToken::~PORSToken()
{
    
}


uint64_t PORSToken::toU64()
{
    assert(mEnd - mBegin == sizeof(uint64_t));
    return *(uint64_t *)mBegin;
}

int64_t PORSToken::toI64()
{
    assert(mEnd - mBegin == sizeof(int64_t));
    return *(int64_t *)mBegin;
}

int PORSToken::toInt()
{
    assert(mEnd - mBegin == sizeof(int));
    return *(int*)mBegin;
}

float PORSToken::toFloat()
{
    assert(mEnd - mBegin == sizeof(float));
    return *(float*)mBegin;
}

bool PORSToken::compareWithString(const string str)
{
    const string temp = string(mBegin, mEnd);
    if(!temp.compare(str))
    {
        return true;
    }
    else
    {
        return false;
    }
}

string PORSToken::toString()
{
    const string temp = string(mBegin, mEnd);
    return temp;
}
