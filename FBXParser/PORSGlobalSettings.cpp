//
//  PORSGlobalSettings.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/14.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSGlobalSettings.hpp"

PORSGlobalSettings::PORSGlobalSettings(const PORSElement &root)
{
    for(PORSElement *setting = root.mChild; setting; setting = setting->mSibling)
    {
        if(setting->mIDToken.compareWithString("GlobalSettings") )
        {
            for(PORSElement *props70 = setting->mChild; props70; props70 = props70->mSibling)
            {
                if(props70->mIDToken.compareWithString("Properties70"))
                {
                    for(PORSElement *node = props70->mChild; node; node = node->mSibling)
                    {
                        if(!node->mProperty)
                        {
                            continue;
                        }
                        
                        #define get_property(name, field, type)   if(node->mProperty->mToken.compareWithString(name))\
                        {\
                            PORSProperty *prop = node->getProperty(4);\
                            if(prop)\
                            {\
                                field = *(type*)prop->mToken.mBegin;\
                            }\
                        }\

                        get_property("UpAxis", UPAxis, int);
                        get_property("UpAxisSign", UPAxisSign, int);
                        get_property("FrontAxis", FrontAxis, int);
                        get_property("FrontAxisSign", FrontAxisSign, int);
                        get_property("CoordAxis", CoordAxis, int);
                        get_property("CoordAxisSign", CoordAxisSign, int);
                        get_property("OriginalUpAxis", OriginalUpAxis, int);
                        get_property("OriginalUpAxisSign", OriginalUpAxisSign, int);
                        get_property("UnitScaleFactor", UnitScaleFactor, float);
                        get_property("OriginalUnitScaleFactor", OriginalUnitScaleFactor, float);
                        get_property("TimeSpanStart", TimeSpanStart, uint64_t);
                        get_property("TimeSpanStop", TimeSpanStop, uint64_t);
                        get_property("TimeMode", TimeMode, FrameRate);
                        get_property("CustomFrameRate", CustomFrameRate, float);
                    }
                    break;
                }
            }
            break;
        }
        
    }
    
}

PORSGlobalSettings::~PORSGlobalSettings()
{
    
}
