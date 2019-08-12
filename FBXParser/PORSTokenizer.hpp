//
//  PORSTokenizer.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/12.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSTokenizer_hpp
#define PORSTokenizer_hpp

#include <stdio.h>
#include <iostream>

#include "PORSElement.hpp"
#include "PORSOptionalError.hpp"

using namespace std;

struct Header
{
    unsigned char magic[21];
    unsigned char reserved[2];
    //unsigned int version;
};

struct Cursor
{
    const unsigned char* currentPosition;
    const unsigned char* beginPosition;
    const unsigned char* endPosition;
};

class PORSTokenizer
{
public:
    PORSTokenizer();
    ~PORSTokenizer();
    

    PORSElement *TokenizeBinary(const unsigned char *data, int size);
};
#endif /* PORSTokenizer_hpp */
