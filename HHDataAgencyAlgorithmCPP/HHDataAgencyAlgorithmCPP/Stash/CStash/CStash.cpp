//
//  CStash.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/11.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "CStash.hpp"
#include <cstdlib>//c语言头文件，C++中加个c 后面.h不要。malloc需要
#include <cassert>
const int increase = 100;
// 初始化，每个数据是多大size
void initialize(CStash* s, int sz)
{
    s->size = sz;
    s->quantity = 0;
    s->next = 0;
    s->storage = 0;
    s->quantity = 0;
}

//往里面放数据,做成通用的，可能是int 可能是字符串，所以是void*
//返回新增加的数据所在的位置
int add(CStash* s, const void* element)
{
    //检查存储空间是否足够，不够就需要增大
    if (s->next >= s->quantity) {
        inflate(s, increase);
    }
    //把数据放进去
    //开始的位置 字节
    int startBytes = s->next * s->size;
    //element 要保存的数据，可能是各种类型，都转变为字符指针。
    unsigned char *e = (unsigned char *)element;
    //把数据以字符保存进去
    for (int i = 0; i < s->size; i++) {
        s->storage[startBytes + i] = e[i];//整书的话每个大小都是一样的。 字符串的话有长有短，短的其余空间补0空白字符
    }
    s->next++;
    //返回添加的数据所在的位置
    return (s->next - 1);
}

//内存一旦分配了就不能变大了，需要重新分配新的大一点的内存，把旧的数据复制过来
void inflate(CStash* s, int increase)
{
    //断言 增加的大小必须大于0
    assert(increase > 0);
    //新的数量
    int newQuantity = s->quantity + increase;
    //新的字节。等于数量乘以每一个的大小
    int newBytes = newQuantity * s->size;
    //原来的大小
    int oldBytes = s->quantity * s->size;
    //新的指针 分配
    unsigned char* b = (unsigned char*)malloc(newBytes);
    //旧数据一个一个复制过来
    for (int i = 0; i < oldBytes; i++) {
        b[i] = s->storage[i];
    }
    //旧分配的内存释放掉
    free(s->storage);
    //把新分配的地址 给CStash
    s->storage = b;
    s->quantity = newQuantity;
}

int count(CStash* s)
{
    return s->next;
}

//取出来某一个数据
void* fetch(CStash* s, int index)
{
    //加断言
    assert(0 <= index);
    if (index >= s->next) {//取完了。没数据了。
        return 0;
    }
    return &(s->storage[index * s->next]);//返回地址
}

void cleanup(CStash* s)
{
    //指针里面 分配的内存释放，否则这块内存不能释放，不能重新使用。内存就会越来越小，内存泄漏
    if (s->storage != 0) {
        free(s->storage);
    }
}
