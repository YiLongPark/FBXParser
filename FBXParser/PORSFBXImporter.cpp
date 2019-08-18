//
//  PORSFBXImporter.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/1.
//  Copyright © 2019 Park. All rights reserved.
//


#include "PORSFBXImporter.hpp"


PORSFBXImporter::PORSFBXImporter()
{
    
}

PORSFBXImporter::~PORSFBXImporter()
{
    
}

//===================================工具函数  Start==================================//
//将字符转换成大写  from assimp libary
char ToLower(char in ) {
    return (in >= (char)'A' && in <= (char)'Z') ? (char)(in+0x20) : in;
}

// Get file extension from path  from assimp libary
std::string GetExtension( const std::string& file ) {
    std::string::size_type pos = file.find_last_of('.');
    
    // no file extension at all
    if (pos == std::string::npos) {
        return "";
    }
    
    // thanks to Andy Maloney for the hint
    std::string ret = file.substr( pos + 1 );
    std::transform( ret.begin(), ret.end(), ret.begin(), ToLower);
    
    return ret;
}
//===================================工具函数  End====================================//


bool PORSFBXImporter::IsFBXFormat(const string &pFile)  //通过文件拓展后缀，判断是否为FBX格式
{
    const string &extension = GetExtension(pFile);
    if(extension == "fbx")
    {
        return true;
    }
    
    return false;
}

PORSScene* ReadFile(const unsigned char *data, int size)
{
    std::unique_ptr<PORSScene> scene = std::make_unique<PORSScene>();
    
    //读取二进制fbx文件元素信息
    PORSTokenizer tokenizer;
    PORSOptionalError<PORSElement *> root = tokenizer.TokenizeBinary(data, size);
    
    PORSParser parser(*root.getmValue(), scene.get());
    
    return nullptr;
}

PORSScene* PORSFBXImporter::LoadFBXFile(const char* filePath)  //加载解析FBX文件
{
    FILE *fp = fopen(filePath, "rb");
    if(!fp)
    {
        return NULL;
    }
    
    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    unsigned char *contents = new unsigned char[fileSize];
    fread(contents, 1, fileSize, fp);
    
    ReadFile(contents, (int)fileSize);
    delete[] contents;
    
    return NULL;
    
}

