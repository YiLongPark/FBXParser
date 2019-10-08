//
//  PORSScene.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/1.
//  Copyright © 2019 Park. All rights reserved.
//

#include "PORSScene.hpp"

PORSScene::PORSScene()
{
    mGolbalSettings = NULL;
}

PORSScene::~PORSScene()
{
    if(mGolbalSettings)
    {
        delete mGolbalSettings;
    }
}

