//
//  PORSProperty.cpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/8/4.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSProperty.hpp"


PORSProperty::PORSProperty()
{
    mToken.mBegin = nullptr;
    mToken.mEnd = nullptr;
    
    mNext = nullptr;
    
}

PORSProperty::~PORSProperty()
{
    
}
