//
//  PORSException.hpp
//  FBXParser
//
//  Created by 朴一龙 on 2019/8/11.
//  Copyright © 2019 Park. All rights reserved.
//

#ifndef PORSException_hpp
#define PORSException_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#define THROW_EXCEPTIOIN(error, desc, src)  ExceptionFactory::throwException(error, desc, src, __FILE__, __LINE__)

enum ExceptionCode
{
    ERROR_FILE_NOT_FOUND,       //文件未找到
    EROOR_INVALID_PARAMETERS,   //参数错误
};

class PORSException : public exception
{
    
public:
    PORSException(ExceptionCode errorCode, const string &description, const string &source, const char * type, const char *file, long line);
    ~PORSException() throw () {}
    
    virtual const string& getFullDescription() const;
    
    //获取异常源函数名称
    const string& getExceptionSource() const { return mSource; }
    //获取异常源文件名称
    const char* getExceptionFileName() const { return mFile; }
    //获取异常源行数位置
    long getExceptionLine() const { return mLine; }
    //获取异常描述信息
    const string& getDescription () const { return mDescription; }
    
    const char* what() const throw() {return getFullDescription().c_str(); }
   
protected:
    long mLine;
    const char *mTypeName;
    string mDescription;
    string mSource;
    const char *mFile;
    mutable string mFullDescription;
    
};


class FileNotFoundException : public PORSException
{
public:
    FileNotFoundException(ExceptionCode errorCode, const string &description, const string &source, const char *file, long line) : PORSException(errorCode, description, source, __FUNCTION__, file, line) {
        
        //printf("yichang  ddd");
    }
};

class InvalidParametersException : public PORSException
{
public:
    InvalidParametersException(ExceptionCode errorCode, const string &description, const string &source, const char *file, long line) : PORSException(errorCode, description, source, __FUNCTION__, file, line) {}
};

class ExceptionFactory
{
private:
    ExceptionFactory() {}
    static void _throwException(ExceptionCode errorCode,
                                const string &description,
                                const string &source,
                                const char *file,
                                long line)
    {
        switch (errorCode)
        {
            case ERROR_FILE_NOT_FOUND:
            
                throw FileNotFoundException(errorCode, description, source, file, line);

                break;
            case EROOR_INVALID_PARAMETERS:
                
                throw InvalidParametersException(errorCode, description, source, file, line);
                break;
                
            default:
                
                break;
        }
    }
    
public:
    static void throwException(ExceptionCode errorCode,
                               const string &description,
                               const string &source,
                               const char *file,
                               long line)
    {
        _throwException(errorCode, description, source, file, line);
    }
};

#endif /* PORSException_hpp */
