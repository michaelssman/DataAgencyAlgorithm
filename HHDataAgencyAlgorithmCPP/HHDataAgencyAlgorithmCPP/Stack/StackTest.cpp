//
//  StackTest.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/16.
//  Copyright © 2020 Michael. All rights reserved.
//

#include <stdio.h>
#include "Stack.hpp"
#include <iostream>
#include <fstream>//读文件
#include <cassert>
#include <string>

using namespace std;

void stackTest()
{
    ifstream in("Test.cpp");//输入文件流
    
    Stack textlines;
    textlines.initialize();//初始化
    
//    textlines.push(new string("one"));
//    textlines.push(new string("two"));
//    textlines.push(new string("three"));
//
//    cout << *(string *)textlines.peak() << endl;

    string line;
    //读到的每一个行都放到堆栈里
    while (getline(in, line)) {
        textlines.push(new string(line));
    }
    
    string *s;
    //输出每一行，结果是倒序的
    while ((s = (string *)textlines.pop()) != 0) {
        cout << *s << endl;
        delete s;
    }
    
    textlines.cleanup();
    
}
