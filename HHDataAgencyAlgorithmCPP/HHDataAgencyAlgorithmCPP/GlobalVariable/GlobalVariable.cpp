//
//  GlobalVariable.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/16.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "GlobalVariable.hpp"

//全局变量

/**
 在函数外面
 C语言里 全局变量
 C++ 全局作用域 默认的名称空间
 */
int a;//全局变量

void f() {}//全局的函数

struct S
{
    int a;
    void f();//S作用域中的函数
};

void S::f()
{
    ::f();//调全局的f。 不需要写std:: 直接写:: 就是默认的 全局作用域
    a--;//a就是S结构内部的a 因为f函数 和a都在S中，所以这个就是S中的a。
    ::a++;//这个a就是全局的a。
}

int GlobalVariableTest()
{
    S s;
    s.f();
    f();
    return 0;
}
