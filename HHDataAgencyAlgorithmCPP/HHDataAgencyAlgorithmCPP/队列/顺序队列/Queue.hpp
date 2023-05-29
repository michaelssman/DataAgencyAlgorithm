//
//  Queue.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/17.
//  Copyright © 2020 Michael. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

#pragma mark - 使用模版类创建队列
template<class T>
class Queue
{
public://共有成员 可对外使用
    Queue(int queueCapacity = 10);//构造函数  数组默认大小是10
    bool IsEmpty() const;//判断队列是否为空
    //查看数据只能查看两端的。不能查看中间的。
    T& Front() const;//读取队首数据
    T& Rear() const;//查看队尾数据
    void Push(const T& item);//队尾插入数据
    void Pop();//队首删除数据
private://私有成员 内部用
    T *queue;//指针 创建一个数组
    int front;//队首下标 位置
    int rear;//队尾下标
    int capacity;//容量 数组有多大
};

//构造函数
template<class T>
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)//初始化列表
{
    if (capacity < 1) {
        throw "Queue capacity must be > 0";
    }
    queue = new T[capacity];
    front = rear = 0; //开始时 队首和队尾都是指向下标0.
}

//IsEmpty  做成内联函数inline。内联函数快
template<class T>
inline bool Queue<T>::IsEmpty() const
{
    return front == rear; //如果队首等于队尾，则是空的
}

//push
/**
 开始的时候队首和队尾都指向0。都是空的。

 队首的位置空的，留一个空的位置，插入在队尾插入。

 一直插入到最后一个，回转，利用队首前面的空白位置。

 插入的时候，队尾已经到最后了，队尾要回到前面，要检查rear是否等于容量-1。即是否是到了最后一个位置。

 如果到了最后一个，那么它的下一个就回到了最前面的0位置。
 
 如果没有到最后一个，则就直接rear++。队尾位置加1即可。

 删除的时候，从队首删除。
 */
template<class T>
void Queue<T>::Push(const T& item)
{
    /**
     判断是否到了数组的最后一个，如果到了变成数组中的第一个，节约内存。
     */
//    检查队尾是否是最后一个，不是的话就rear++，是最后一个的话就变成第一个
//    if (rear == capacity - 1) {
//    队尾到了最后，就需要回到第一个。
//        rear = 0;
//    } else {
//    队尾没有到最后
//        rear++;//队尾++
//    }
    
    //上面可以写成下面一行
//    rear = (rear + 1) % capacity;//高水平
    
    
    /**
     判断数组是否已经满了，满了就放大一倍
     如果数组是回转过来的，队尾转了一圈的情况。也放大一倍。
     */
    if ((rear + 1) % capacity == front) {//队列满了
        //加倍
        //创建一个新的数组
        T* newQueue = new T[2 * capacity];//新数组容量是原来的2倍
        //两种情况，没有发生回绕 队首在前面，队尾在后面。发生了回调，队首在后面，队尾在前面，队首和队尾挨在一起。
        int start = (front + 1) % capacity;
        if (start < 2) {
            //没有回转
            copy(queue + start, queue + start + capacity - 1, newQueue);//把所有的拷贝到新的数组里
        } else {
            //发生了回转
            copy(queue + start, queue + capacity, newQueue);//先拷贝后面的
            copy(queue, queue + rear + 1, newQueue + capacity - start);//再拷贝前面回绕的
        }
        //重新设置队首和队尾下标位置
        front = 2 * capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        //旧数组删除
        delete [] queue;
        queue = newQueue;
    }
    
    rear = (rear + 1) % capacity;//高水平
    queue[rear] = item;
}

//读队首数据  做成内联的。内联函数快
template<class T>
inline T& Queue<T>::Front() const
{
    if (IsEmpty()) {
        throw "Queue is empty";
    }
    return queue[(front + 1) % capacity];//front是空的 是下一个数据。
    /**
     设计的时候，队首的位置设置成空的，第一个数据是front的下一个。
     如果front是最后一个，则下一个是下标位置为0的数据，回绕的情况。
     */
}

//读队尾数据  做成内联的。内联函数快
template<class T>
inline T& Queue<T>::Rear() const
{
    if (IsEmpty()) {
        throw "Queue is empty";
    }
    return queue[rear];//队尾不用加1，rear就是指向的队尾的数据
}

//pop 从队首删除数据
template<class T>
void Queue<T>::Pop()
{
    //如果堆栈是空的 抛异常
    if (IsEmpty()) {
        throw "Queue is empty Cannot delete";
    }
    //删除 队首始终指向第一个数据的前一个的空位。
    //在加1的时候要处理回绕。
    front = (front + 1) % capacity;
    queue[front].~T();//数据有可能是对象类型，调用析构函数，要释放内存。
}

#endif /* Queue_hpp */
