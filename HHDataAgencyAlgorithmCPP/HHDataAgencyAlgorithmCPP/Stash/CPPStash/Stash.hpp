//
//  CppStash.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/16.
//  Copyright © 2020 Michael. All rights reserved.
//

#ifndef CppStash_hpp
#define CppStash_hpp

#include <stdio.h>

// C++的Stash
struct Stash
{
    int size;// 每一个是多大。存字符串的话就是最多的存多少字符。
    int quantity;// 数量。一共可以保存多少个。
    int next;// 已经保存了多少个。
    unsigned char* storage;// 指针
    
    
    // 一些操作  C++可以放到里面
    // 函数是在结构里面的，所以函数定义的时候要写 结构名加::
    // 这些函数也叫 这个结构的成员
    void initialize(int size);
    void cleanup();
    void* fetch(int index);
    int add(const void* element);
    int count();
    // 扩大内存
    void inflate(int increase);
};

#endif /* CppStash_hpp */
