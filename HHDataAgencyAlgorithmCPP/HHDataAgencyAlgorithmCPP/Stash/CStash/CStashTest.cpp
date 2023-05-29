//
//  CStashTest.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/11.
//  Copyright © 2020 Michael. All rights reserved.
//

#include <stdio.h>
#include "CStash.hpp"
#include <iostream>
#include <fstream>//读文件
#include <cassert>
#include <string>

using namespace std;
void cstashtest()
{
    CStash intStash, stringStash;
    const int bufsize = 80;//最多保存80个字符(char)
    initialize(&intStash, sizeof(int));
    for (int i = 0; i < 150; i++) {
        add(&intStash, &i);
    }
    //取出来
    for (int i = 0; i < count(&intStash); i++) {
       cout << *(int*)fetch(&intStash, i) << endl;
    }
    
    //例子2 保存字符串
    initialize(&stringStash, bufsize * sizeof(char));
    ifstream in;
    in.open("wenjianming.cpp");
    assert(in);//有效的输入流
    string line;
    while (getline(in, line)) {
        //把每一行都加进去
        add(&stringStash, line.c_str());//line是C++的string字符串 需要改成c语言的指针
    }
    int k = 0;
    //把每一行都读出来
    char* cp;
    while ((cp=(char*)fetch(&stringStash, k++)) != 0) {
        cout << cp << endl;
    }
    //清理内存
    cleanup(&intStash);
    cleanup(&stringStash);
}
