//
//  LinkedStack.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/23.
//  Copyright © 2020 Michael. All rights reserved.
//  链式栈

#ifndef LinkedStack_hpp
#define LinkedStack_hpp

#include <stdio.h>

template<class T> class LinkedStack;//前置声明

//链的节点
template<class T>
class ChainNode
{
    friend class LinkedStack<T>;
private:
    //构造函数
    ChainNode(const T&theData, ChainNode *n = 0)
    : data(theData),link(n){}
    //私有数据成员
    T data;             //节点数据
    ChainNode<T> *link; //指针指向下一个节点
};

//链式栈
template<class T>
class LinkedStack
{
public:
    LinkedStack():top(0){}//构造函数 top等于0
    ~LinkedStack(){MakeEmpty();}//析构函数 把堆栈里的所有节点都删除掉
    bool IsEmpty() const;//堆栈是不是空的
    T& Top() const;//返回栈顶数据
    void Push(const T& e);//把新的数据压入堆栈
    void Pop();//从栈顶删除数据
    void MakeEmpty();//把所有数据析构
private:
    //数据成员
    ChainNode<T> *top;
};

template<class T>
bool LinkedStack<T>::IsEmpty() const
{
    return top == 0;
}

//top指针永远指向新放入的数据。
//新的节点的指向下一个节点的指针 指向的是以前的top。
template<class T>
void LinkedStack<T>::Push(const T &e)
{
    //创建新节点，新节点的数据是e，指针是top原来的栈顶。
    top = new ChainNode<T>(e,top);
}

//返回栈顶的数据
template<class T>
T& LinkedStack<T>::Top() const
{
    //如果堆栈是空的
    if (this->IsEmpty()) {
        //抛出异常
        throw "Stack is empty";
    } else {
        return top->data;
    }
}

//删除栈顶元素
template<class T>
void LinkedStack<T>::Pop()
{
    //如果堆栈是空的
    if (this->IsEmpty()) {
        throw "Stack is empty Cannot delete";
    } else {
        //1. 用一个指针指向栈顶的数据
        ChainNode<T> *delNode = top;
        //2. 栈顶向下移动（栈顶指向栈顶的下一个），栈顶的下一个变成栈顶。
        top = top->link;
        //3. 防止内存泄漏 和new对应 push的时候new了新节点，pop的时候要delete掉。
        delete delNode;
    }
}

//堆栈节点清空
template<class T>
void LinkedStack<T>::MakeEmpty()
{
    //如果堆栈不是空的。循环删除，直到为空。
    while (!IsEmpty()) {
        Pop();
    }
}

#endif /* LinkedStack_hpp */
