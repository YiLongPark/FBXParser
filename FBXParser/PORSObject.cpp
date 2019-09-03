//
//  PORSObject.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/6.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSObject.hpp"

PORSObject::PORSObject(uint64_t id, const PORSElement &element)
:mElement(element),
 mUID(id),
 mIsNode(false)
{
    
}

PORSObject::~PORSObject()
{
    
}

PORSElement* PORSObject::resolveProperty(const char *mark)
{
    const PORSElement *props = PORSUtil::getRequiredElement(mElement, "Properties70");
    if(!props)
    {
        return nullptr;
    }
    
    PORSElement *prop = props->mChild;
    
    while (prop) {
        if(prop->mProperty && prop->mProperty->mToken.compareWithString(mark))
        {
            return prop;
        }
        
        prop = prop->mSibling;
    }
    
    return nullptr;
}

Vector3D PORSObject::resolveVec3DProperty(const char* mark, const Vector3D &defaultValue)
{
    PORSElement *element = resolveProperty(mark);
    if(!element)
    {
        return defaultValue;
    }
    
    PORSProperty *value = element->getProperty(4);
    if(!value || !value->mNext || !value->mNext->mNext)
    {
        return defaultValue;
    }
    
    Vector3D vector;
    vector.x = value->mToken.toDouble();
    vector.y = value->mNext->mToken.toDouble();
    vector.z = value->mNext->mNext->mToken.toDouble();
    
    return vector;

}

Vector3D PORSObject::getLocalScaling()
{
    //Vector3D defaultValue = {0,0,0};
    return resolveVec3DProperty("Lcl Scaling", {0, 0, 0});
}

Vector3D PORSObject::getLocalRotation()
{
    return resolveVec3DProperty("Lcl Rotation", {0, 0, 0});

}
Vector3D PORSObject::getLocalTranslation()
{
    return resolveVec3DProperty("Lcl Translation", {1, 1, 1});
}


