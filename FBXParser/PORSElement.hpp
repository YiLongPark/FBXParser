//
//  PORSElement.hpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/8/4.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSElement_hpp
#define PORSElement_hpp

#include <stdio.h>

#include "PORSToken.hpp"
#include "PORSProperty.hpp"

class PORSElement
{
public:
    PORSElement();
    ~PORSElement();
    
    PORSProperty *getProperty(int index)const
    {
        PORSProperty *property = mProperty;
        for(int i = 0; i < index; i++)
        {
            if(!property)
            {
                return nullptr;
            }
            property = property->mNext;
        }
        return property;
    }
    
public:
    PORSToken mIDToken;
    PORSElement *mChild;
    PORSElement *mSibling;
    PORSProperty *mProperty;
    
};
#endif /* PORSElement_hpp */
