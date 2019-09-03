//
//  PORSTexture.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/13.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSTexture.hpp"

PORSTexture::PORSTexture(uint64_t uid,  const PORSElement &element):PORSObject(uid, element)
{
    mType = TEXTURE;
    
    const PORSElement *textureFileName = PORSUtil::getRequiredElement(element, "FileName");
    
    if(textureFileName && textureFileName->mProperty)
    {
        mFileName = textureFileName->mProperty->mToken.toString();
    }
    
    const PORSElement *textureRelativeFileName = PORSUtil::getRequiredElement(element, "RelativeFilename");
    
    if(textureRelativeFileName && textureRelativeFileName->mProperty)
    {
        mRelativeFileName = textureRelativeFileName->mProperty->mToken.toString();
    }
}

PORSTexture::~PORSTexture()
{
    
}
