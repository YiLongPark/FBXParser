//
//  PORSFBXImporter.hpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/1.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSFBXImporter_hpp
#define PORSFBXImporter_hpp

#include <stdio.h>
#include <string>
#include <iostream>

#include "PORSScene.hpp"
#include "PORSElement.hpp"
#include "PORSProperty.hpp"
#include "PORSTokenizer.hpp"
#include "PORSParser.hpp"

using namespace std;

class PORSFBXImporter
{
public:
    PORSFBXImporter();
    ~PORSFBXImporter();
    
    bool IsFBXFormat(const string &pFile);  //通过文件拓展后缀，判断是否为FBX格式
    PORSScene* LoadFBXFile(const char* filePath);  //加载解析FBX文件
};


#endif /* PORSFBXImporter_hpp */
