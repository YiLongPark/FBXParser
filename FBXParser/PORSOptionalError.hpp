//
//  PORSOptionalError.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/5.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSOptionalError_hpp
#define PORSOptionalError_hpp

#include <stdio.h>

struct PORSError
{
    PORSError() {}
    PORSError(const char* msg) { s_message = msg; }
    
    static const char* s_message;
};

template <typename T>
class PORSOptionalError {

public:
    PORSOptionalError(PORSError error):mIsError(true)
    {
        
    }
    
    PORSOptionalError(T value):mValue(value), mIsError(false)
    {
        
    }
    
    T getmValue()
    {
        return mValue;
    }
    
    bool getmIsError()
    {
        return mIsError;
    }
    
    ~PORSOptionalError()
    {
        
    }
    
private:
    T mValue;
    bool mIsError;
    
};

#endif /* PORSOptionalError_hpp */
