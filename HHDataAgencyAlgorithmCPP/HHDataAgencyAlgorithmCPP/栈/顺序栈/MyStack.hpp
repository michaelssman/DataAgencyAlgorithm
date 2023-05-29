//
//  MyStack.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/17.
//  Copyright © 2020 Michael. All rights reserved.
//  顺序栈

#ifndef MyStack_hpp
#define MyStack_hpp

#include <stdio.h>
#include "MyUtil.hpp"

//使用模版类创建
template<class T>
class MyStack
{
public://共有成员 可对外使用
    MyStack(int stackCapacity = 10);//构造函数  默认大小是10
    ~MyStack();//析构
    bool IsEmpty() const;//判断堆栈是否为空 常函数
    T& Top() const;
    void Push(const T& item);//入栈
    void Pop();//栈顶数据删除
private://私有成员 内部用
    T *stack;//指针 用这个指针动态创建一个数组
    int top;//记录栈顶的位置
    int capacity;//容量 数组有多大 大小可以动态的改变
};


//构造函数
template<class T>
MyStack<T>::MyStack(int stackCapacity):capacity(stackCapacity)//初始化列表
{
    if (capacity < 1) {
        throw "stack capacity must be > 0";
    }
    stack = new T[capacity];//动态创建数组
    top = -1;
    //空堆栈
}

//析构函数
template<class T>
MyStack<T>::~MyStack()
{
    //构造函数中动态创建的数组 析构函数中删除
    delete [] stack;
}

//IsEmpty  做成内联的。内联函数快
template<class T>
inline bool MyStack<T>::IsEmpty() const
{
    return top == -1; //如果top为-1则是空的
}
 
//top  做成内联的。内联函数快
template<class T>
inline T& MyStack<T>::Top() const
{
    if (IsEmpty()) {
        throw "Stack is empty";
    }
    return stack[top];
}

//pop 把栈顶数据删除
template<class T>
void MyStack<T>::Pop()
{
    //如果堆栈是空的 抛异常
    if (IsEmpty()) {
        throw "Stack is empty Cannot delete";
    }
    //重要
    stack[top--].~T();//Top--，并且还得把数据析构，因为栈里可能保存的数据是类，需要调用T的析构函数
}

//push
//添加到数组中 先判断是否满了  数组满了 要扩大容量 旧数据拷贝到新到里面
template<class T>
void MyStack<T>::Push(const T& item)
{
    //数组满了 就放大
    if (top == capacity - 1) {
        ChangeSize1D(stack, capacity, 2*capacity);
        capacity *= 2;
    }
    //数据放到数组
    stack[++top] = item;
}



#endif /* MyStack_hpp */
