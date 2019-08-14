//
//  PORSSkin.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSSkin.hpp"

PORSSkin::PORSSkin(const PORSScene &scene, const PORSElement &element):PORSObject(0, element)
{
      const PORSElement *linkDeformAcuracy = PORSUtil::getRequiredElement(element, "Link_DeformAcuracy");
      mAccracy = linkDeformAcuracy->mProperty->mToken.toFloat();
    
}

PORSSkin::~PORSSkin()
{
    
}
