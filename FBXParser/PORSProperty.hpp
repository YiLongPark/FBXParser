//
//  PORSProperty.hpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/8/4.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSProperty_hpp
#define PORSProperty_hpp

#include <stdio.h>
#include "PORSToken.hpp"

class PORSProperty
{
public:
    PORSProperty();
    ~PORSProperty();
    
public:
    PORSToken mToken;
    PORSProperty *mNext;
    
    char mType;
};
#endif /* PORSProperty_hpp */
