//
//  CStash.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/11.
//  Copyright © 2020 Michael. All rights reserved.
//

/**
 CStash
 C C语言
 Stash 存储
 利用Stash可以储存各种各样的数据，可以存整型，字符串，浮点型。
 存储的数据可多可少，指针动态分配内存。
 */
#ifndef CStash_hpp
#define CStash_hpp

#include <stdio.h>

typedef struct CStashTag
{
    int size;//每个数据的大小
    int quantity;//数组的数量 容量
    int next;//已经保存的个数
    //利用这个指针就可以动态的存储各种各样的数据（int float 字符串），可多可少。
    //整型还是字符串 都用char存储
    unsigned char* storage;//指针
}CStash;

//操作函数。函数的声明
void initialize(CStash* s, int size);
int add(CStash* s, const void* element);
//增大内存
void inflate(CStash* s, int increase);
//计算个数
int count(CStash* s);
//取出来某一个数据
void* fetch(CStash* s, int index);
void cleanup(CStash* s);
#endif /* CStash_hpp */
