//
//  PORSTokenizer.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/12.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSTokenizer.hpp"

#pragma mark read single word functions

uint32_t Read32bitWords(Cursor* cursor)
{
    
    uint32_t word;
    memcpy(&word, cursor->currentPosition, sizeof(uint32_t));
    
    cursor->currentPosition += sizeof(uint32_t);
    return word;
}

uint64_t Read64bitWords(Cursor* cursor)
{
    uint64_t word;
    memcpy(&word, cursor->currentPosition, sizeof(uint64_t));
    cursor->currentPosition += sizeof(uint64_t);
    
    return word;
}

uint8_t ReadByteWords(Cursor *cursor)
{
    uint8_t word;
    memcpy(&word, cursor->currentPosition, sizeof(uint8_t));
    cursor->currentPosition += sizeof(uint8_t);
    
    return word;
}

const PORSToken ReadString(Cursor *cursor, bool isLongString)
{
    //length 读取单个字节
    const uint32_t keyLength = isLongString? Read32bitWords(cursor) : ReadByteWords(cursor);
    
    PORSToken token;
    
    const unsigned char *stringBegin = cursor->currentPosition;
    token.mBegin = stringBegin;
    
    cursor->currentPosition += keyLength;
    const unsigned char *stringEnd = cursor->currentPosition;
    token.mEnd = stringEnd;
    
    const string keyString = string(token.mBegin, token.mEnd);
    
    return token;
}

uint32_t Offset(const unsigned char *begin, const unsigned char *end)
{
    assert(begin <= end);
    
    return static_cast<uint32_t>(end - begin);
}

void deleteElement(PORSElement *element)
{
    if(!element)
    {
        return;
    }
    
    delete element->mProperty;
    deleteElement(element->mChild);
    
    PORSElement *iter = element;
    
    do
    {
        PORSElement *next = iter->mSibling;
        delete iter;
        iter = next;
    }while (iter);
}

#pragma mark read property and elements functions

PORSProperty* ReadPropertyData(Cursor *cursor)
{
    const char propertyType = ReadByteWords(cursor);
    
    PORSProperty *property = new PORSProperty();
    property->mToken.mBegin = cursor->currentPosition;
    
    property->mType = propertyType;
    switch (propertyType)
    {
        case 'Y':  // 16 bit int
            cursor->currentPosition += 2;
            break;
        case 'C':  // 1 bit bool flag (yes/no)
            cursor->currentPosition += 1;
            break;
        case 'I':  // 32 bit int
            cursor->currentPosition += 4;
            break;
        case 'F':  // float
            cursor->currentPosition += 4;
            break;
        case 'D':  // double
            cursor->currentPosition += 8;
            break;
        case 'L':  // 64 bit int
            cursor->currentPosition += 8;
            break;
        case 'R':  // raw binary data
        {
            const uint32_t keyLength = Read32bitWords(cursor);
            cursor->currentPosition += keyLength;
            break;
        }
        case 'S':  //string
        {
            const PORSToken tempToken = ReadString(cursor, true);   //long string
            //property->mToken.mBegin = tempToken.mBegin;
            property->mToken.mBegin = tempToken.mBegin;
            property->mToken.type = 333;
            break;
        }
        // array of
        case 'b':
        case 'f':
        case 'd':
        case 'l':
        case 'i':
        {
            const uint32_t lenghth = Read32bitWords(cursor);
            const uint32_t encoding = Read32bitWords(cursor);
            const uint32_t complength = Read32bitWords(cursor);
            
            cursor->currentPosition += complength;
            break;
        }
        default:
            printf("this is error!!!!!!!");
            break;
    }
    
    property->mToken.mEnd = cursor->currentPosition;
    
    return property;
}

PORSOptionalError<PORSElement*> ReadElement(Cursor* cursor, bool is64bit)
{
    const uint64_t end_offset = is64bit ? Read64bitWords(cursor) : Read32bitWords(cursor);
    
    if(0 == end_offset)
    {
        return nullptr;
    }
    
    if(end_offset > Offset(cursor->beginPosition, cursor->endPosition))
    {
        //error
        return PORSError();
    }
    else if(end_offset < Offset(cursor->beginPosition, cursor->currentPosition))
    {
        //error
        return PORSError();
    }
    
    const uint64_t prop_count = is64bit? Read64bitWords(cursor) : Read32bitWords(cursor);
    
    const uint64_t prop_length = is64bit? Read64bitWords(cursor) : Read32bitWords(cursor);
    
    //const string &stringOut = ReadString(cursor);
    PORSToken token = ReadString(cursor, false);  //short string
    PORSElement *element = new PORSElement();
    element->mIDToken = token;
    PORSProperty **propLink = &element->mProperty;
    
    //读取属性数据
    for(uint32_t i = 0; i < prop_count; i++)
    {
        PORSProperty *property = ReadPropertyData(cursor);
        
        if(property == nullptr)
        {
            deleteElement(element);
        }
        *propLink = property;
        propLink = &(*propLink)->mNext;
        
    }
    
    const int sentinelBlockLength = is64bit? sizeof(uint64_t) * 3 + 1 : sizeof(uint32_t) * 3 + 1;
    
    if((cursor->currentPosition - cursor->beginPosition) < end_offset)
    {
        
        PORSElement **link = &element->mChild;
        while ((cursor->currentPosition - cursor->beginPosition) < ((ptrdiff_t)end_offset - sentinelBlockLength))
        {
            PORSOptionalError<PORSElement *> child = ReadElement(cursor, is64bit);
            
            if(child.getmIsError())
            {
                deleteElement(element);
            }
            *link = child.getmValue();
            link = &(*link)->mSibling;
        }
        
        cursor->currentPosition += sentinelBlockLength;
    }
    
    return element;
}

#pragma mark class member functions

PORSTokenizer::PORSTokenizer()
{
    
}

PORSTokenizer::~PORSTokenizer()
{
    
}

PORSElement* PORSTokenizer::TokenizeBinary(const unsigned char *data, int size)
{
    Cursor cursor;
    cursor.beginPosition = data;
    cursor.currentPosition = data;
    cursor.endPosition = data + size;
    
    const Header *header = (const Header*)cursor.currentPosition;
    cursor.currentPosition += sizeof(*header);
    
    unsigned int version;
    std::memcpy(&version, cursor.currentPosition, 4);     //获取FBX文件的版本信息
    
    cursor.currentPosition += sizeof(unsigned int);
    
    const bool is64Bit = version >= 7500;
    
    PORSElement *root = new PORSElement();
    
    PORSElement **element = &root->mChild;
    while(cursor.currentPosition < cursor.endPosition)
    {
        PORSOptionalError<PORSElement *> child = ReadElement(&cursor, is64Bit);
        if(child.getmIsError())
        {
            deleteElement(root);
            return nullptr;
            // break;
        }
        
        *element = child.getmValue();
        if(!(*element))
        {
            return root;  //返回主要的结果
        }
        
        element = &(*element)->mSibling;
        
    }
    
    return NULL;
}



