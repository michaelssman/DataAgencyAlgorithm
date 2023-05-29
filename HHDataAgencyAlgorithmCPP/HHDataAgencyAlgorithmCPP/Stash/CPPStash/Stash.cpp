//
//  CppStash.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/16.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "Stash.hpp"
#include <cassert>

// 一些操作
// 初始化，每个数据是多大size
void Stash::initialize(int sz)
{
    size = sz;
//    等同于下面
//    this -> size = sz;
    // 也可以写成
//    this->size = sz; //this 代表当前对象
    // 开始的时候没有数据 下面的参数都是0
    quantity = 0;
    next = 0;
    storage = 0;
}

const int increment = 100;
// 扩大内存
void Stash::inflate(int increase)
{
    //加断言 必须大于0
    assert(increase > 0);
    //分配新的大一点的内存，然后把数据拷贝放到新的内存里。
    int newQuantity = quantity + increase; // 这是增大多少个
    int newBytes = newQuantity * size;//这是增大多少子节
    int oldBytes = quantity * size;//原来的大小
//    unsigned char* b = (unsigned char*)malloc(newBytes);//分配新内存 C语言的 C++使用new
    unsigned char* b = new unsigned char(newBytes);
    //把旧数据 复制新分配的内存过来
    for (int i = 0; i < oldBytes; i++) {
        b[i] = storage[i];
    }
    //释放就内存
//    free(storage);//C语言
    delete[] storage;//C++
    storage = b;
    quantity = newQuantity;
}
// 往里面放数据,做成通用的，可能是int 可能是字符串，所以是void*
int Stash::add(const void* element)
{
    // 如果有c足够的位置就添加，没有就扩大内存。
    if (next >= quantity) {
        // 扩大内存
        inflate(increment);
    }
    int startBytes = next * size;
    //element 要保存的数据，可能是各种类型，都转变为字符指针。
    unsigned char *e = (unsigned char*)element;
    for (int i = 0; i < size; i++) {
        storage[startBytes + i] = e[i];
    }
    next++;
    //返回添加的数据所在的位置
    return (next - 1);
}

//计算数据有多少个
int Stash::count()
{
    return next;
}

// 取出某个数 得到是一个指针
void* Stash::fetch(int index)
{
    //加断言
    assert(0 <= index);
    if (index >= next) {
        return 0;//取完了。没数据了。
    }
    return &(storage[index * size]);
}

//清除
void Stash::cleanup()
{
    //释放内存 内存可以被使用 防止内存泄漏
    if (storage != 0) {
        delete[] storage;
    }
}
