//
//  PORSException.cpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/8/11.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSException.hpp"


PORSException::PORSException(ExceptionCode errorCode, const string &description, const string &source, const char * type, const char *file, long line)
{
    mLine = line;
    mTypeName = type;
    mDescription = description;
    mSource = source;
    mFile = file;
    
    //printf("%s", getFullDescription().c_str());
}


const string& PORSException::getFullDescription () const
{
    if(mFullDescription.empty())
    {
        stringstream desc;
        desc << mTypeName << ": " << mDescription << " in (function)"<< mSource;
        
        if(mLine > 0)
        {
            desc<< " at " << mFile << " (line " << mLine << ")";
        }
        
        mFullDescription = desc.str();
    }
    
    return mFullDescription;
}
