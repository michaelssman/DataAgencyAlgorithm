//
//  Stack.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/16.
//  Copyright © 2020 Michael. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>
//定义堆栈
struct Stack
{
    //结构中嵌套结构
    //节点
    struct Link //堆栈中的每一个数据都是Link。
    {
        void* data;//Link中的数据，保存数据
        Link* next;//指针 指向下一个数据
        void initialize(void* dat, Link* nxt);//Link节点初始化
    }* head;//头 head也是一个Link
    
    void initialize();//堆栈初始化
    void push(void* dat);//把数据压入堆栈
    void* pop();//从堆栈中拿数据，只能从一头拿 不能从中间拿。把head指向的数据拿出来，head指向下一个。
    void* peak();//只看一下数据，不拿出来。
    void cleanup();
};
#endif /* Stack_hpp */
