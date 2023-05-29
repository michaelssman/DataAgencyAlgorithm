//
//  MyUtil.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/17.
//  Copyright © 2020 Michael. All rights reserved.
//  通用的公用函数

#ifndef MyUtil_hpp
#define MyUtil_hpp

#include <stdio.h>
#include <iostream>

//把数组放大一倍。不断的push 满了就把原来的数据放大一倍
template<class T>
void ChangeSize1D(T* &a, const int oldSize, const int newSize);

template<class T>
void ChangeSize1D(T* &a, const int oldSize, const int newSize)
{
    if (newSize < 0) {
        throw "New length must be >= 0";
    }
    //new一个新的数组，把旧数组中的数据一个一个的拷贝到新数组里
    T* temp = new T(newSize);//利用新的大小创建新数组
    int number = std::min(oldSize, newSize);
    std::copy(a, a+number, temp);
    delete [] a;//把原来的数组删除
    a = temp;
}
#endif /* MyUtil_hpp */
