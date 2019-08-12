//
//  PORSElement.cpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/8/4.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSElement.hpp"

PORSElement::PORSElement()
{
    mChild = nullptr;
    mSibling = nullptr;
    mProperty = nullptr;
    
    mIDToken.mBegin = nullptr;
    mIDToken.mEnd = nullptr;
}

PORSElement::~PORSElement()
{
    
}


