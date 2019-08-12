//
//  PORSUtil.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/12.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSUtil_hpp
#define PORSUtil_hpp

#include <stdio.h>
#include <iostream>

#include "miniz.h"
#include "PORSElement.hpp"

using namespace std;

class PORSUtil
{
public:
    static const PORSElement* getRequiredElement(const PORSElement &element, const string id)
    {
        PORSElement* const *iter = &element.mChild;
        
        while(*iter)
        {
            const string temp = string((*iter)->mIDToken.mBegin, (*iter)->mIDToken.mEnd);
            if(!temp.compare(id))
            {
                return *iter;
            }
            
            iter = &(*iter)->mSibling;
        }
        
        return nullptr;
    }
    
    static bool  decompress(const unsigned char* in, size_t in_size, unsigned char* out, size_t out_size)
    {
        mz_stream stream = {};
        mz_inflateInit(&stream);
        
        stream.avail_in = (int)in_size;
        stream.next_in = in;
        stream.avail_out = (int)out_size;
        stream.next_out = out;
        
        int status = mz_inflate(&stream, Z_SYNC_FLUSH);
        
        if (status != Z_STREAM_END) return false;
        
        return mz_inflateEnd(&stream) == Z_OK;
    }
    
    template <typename T> static bool parseArrayRaw(const PORSProperty &property, T *out, int max_size)
    {
        assert(out);
        
        int elementSize = 1;
        switch (property.mType)
        {
            case 'l':
                elementSize = 8;
                break;
            case 'd':
                elementSize = 8;
                break;
            case 'f':
                elementSize = 4;
                break;
            case 'i':
                elementSize = 4;
                break;
                
            default:
                break;
        }
        
        const unsigned char *data = property.mToken.mBegin + sizeof(uint32_t) * 3;
        if(data > property.mToken.mEnd)
        {
            return false;
        }
        
        uint32_t count = int(*(uint32_t*)property.mToken.mBegin);
        uint32_t encode = *(const uint32_t *)(property.mToken.mBegin + 4);
        uint32_t length = *(const uint32_t *)(property.mToken.mBegin + 8);
        
        if(0 == encode)
        {
            if(length > max_size)
            {
                return false;
            }
            if(data + length > property.mToken.mEnd)
            {
                return false;
                
            }
            memcpy(out, data, length);
            return true;
            
        }
        else if (1 == encode)
        {
            if(int (elementSize * count) > max_size)
            {
                return false;
            }
            
            return decompress(data, length, (unsigned char*)out, elementSize * count);
            //return true;
        }
        
        return false;
    }
    
    template <typename T> static bool parserBinaryArray(const PORSProperty &property, vector<T> *out)
    {
        assert(out);
        uint32_t count = int(*(uint32_t*)property.mToken.mBegin);
        int elementSize = 1;
        switch (property.mType)
        {
            case 'd':
                elementSize = 8;
                break;
            case 'f':
                elementSize = 4;
                break;
            case 'i':
                elementSize = 4;
                break;
                
            default:
                break;
        }
        
        int elementCount = sizeof(T) / elementSize;
        out->resize(count / elementCount);
        
        if (0 == count)
        {
            return true;
        }
        
        return parseArrayRaw(property, &(*out)[0], int (sizeof((*out)[0]) * out->size()));
        
    }
    
    template <typename T> static bool parseDoubleVecData(PORSProperty &property, vector<T> *outVector)
    {
        assert(outVector);
        
        if(property.mType == 'd')
        {
            return parserBinaryArray(property, outVector);
        }
        
        return false;
    }
    
};

#endif /* PORSUtil_hpp */
