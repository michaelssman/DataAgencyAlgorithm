//
//  CppStashTest.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/16.
//  Copyright © 2020 Michael. All rights reserved.
//

#include <stdio.h>
#include "Stash.hpp"
#include <iostream>
#include <fstream>//读文件
#include <cassert>
#include <string>

using namespace std;
void stashtest()
{
    Stash intStash, stringStash;
    const int bufsize = 80;//最多保存80个字符(char)
//    initialize(&intStash, sizeof(int));//C语言
    intStash.initialize(sizeof(int));
    for (int i = 0; i < 150; i++) {
        intStash.add(&i);//放的都是地址
    }
    //取出来
    for (int i = 0; i < intStash.count(); i++) {
        std::cout << *(int *)intStash.fetch(i) << std::endl;
    }
    
    //例子2 保存字符串
   stringStash.initialize(bufsize * sizeof(char));
    ifstream in;
    in.open("wenjianming.cpp");
    assert(in);//有效的输入流
    string line;
    while (getline(in, line)) {
        //把每一行都加进去
        stringStash.add(line.c_str());//line是C++的string字符串 需要改成c语言的指针
    }
    int k = 0;
    //把每一行都读出来
    char* cp;
    while ((cp=(char*)stringStash.fetch(k++)) != 0) {
        cout << cp << endl;
    }
    //清理内存
    intStash.cleanup();
    stringStash.cleanup();
}
