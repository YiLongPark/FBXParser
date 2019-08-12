//
//  PORSConnection.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/5.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSConnection_hpp
#define PORSConnection_hpp

#include <stdio.h>
#include <iostream>
#include "PORSProperty.hpp"

enum ConnectionType
{
    OBJECT_OBJECT,
    OBJECT_PROPERTY
};

class PORSConnection
{
public:
    PORSConnection();
    ~PORSConnection();
public:
    ConnectionType mType;
    uint64_t mFrom;
    uint64_t mTo;
    PORSProperty mProperty;
    
};
#endif /* PORSConnection_hpp */
