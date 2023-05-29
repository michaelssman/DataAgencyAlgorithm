//
//  Except.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/12/9.
//  Copyright © 2020 Michael. All rights reserved.
//  异常类

#ifndef Except_hpp
#define Except_hpp

#include <stdio.h>
#include <string>
using namespace std;

#pragma mark - 异常类
class DSException
{
public:
    //构造函数
    DSException(const string & msg = "") : message(msg){}
    //析构函数
    virtual ~DSException(){}
    virtual string toString() const
    {
        return "Exception " + string(": ") + what();
    }
    virtual string what() const
    {
        return message;
    }
private:
    string message;
};

class DuplicateItemException : public DSException
{
public:
    //构造函数
    DuplicateItemException(const string & msg = "") : DSException(msg){}
};

class NullPointerException : public DSException
{
public:
    //构造函数 参数是字符串
    NullPointerException(const string & msg = "") : DSException(msg)
    {}
};

#endif /* Except_hpp */
