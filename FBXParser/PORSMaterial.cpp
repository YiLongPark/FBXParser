//
//  PORSMaterial.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/13.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSMaterial.hpp"

PORSMaterial::PORSMaterial(uint64_t uid, const PORSElement &element):PORSObject(uid, element)
{
    mType = MATERIAL;
    
    const PORSElement *properties = PORSUtil::getRequiredElement(element, "Properties70");
    
    if(properties)
    {
        PORSElement *iter = properties->mChild;
        
        while(iter)
        {
            string tag = iter->mProperty->mToken.toString();
            
            if(!tag.compare("AmbientColor"))
            {
                mAmbientColor.r = iter->getProperty(4)->mToken.toDouble();
                mAmbientColor.g = iter->getProperty(5)->mToken.toDouble();
                mAmbientColor.b = iter->getProperty(6)->mToken.toDouble();
            }
            if(!tag.compare("DiffuseColor"))
            {
                mDiffuseColor.r = iter->getProperty(4)->mToken.toDouble();
                mDiffuseColor.g = iter->getProperty(5)->mToken.toDouble();
                mDiffuseColor.b = iter->getProperty(6)->mToken.toDouble();
            }
            if(!tag.compare("SpecularColor"))
            {
                mSpecularColor.r = iter->getProperty(4)->mToken.toDouble();
                mSpecularColor.g = iter->getProperty(5)->mToken.toDouble();
                mSpecularColor.b = iter->getProperty(6)->mToken.toDouble();
            }
            
            iter = iter->mSibling;
        }
        
    }
}

PORSMaterial::~PORSMaterial()
{
    
}
