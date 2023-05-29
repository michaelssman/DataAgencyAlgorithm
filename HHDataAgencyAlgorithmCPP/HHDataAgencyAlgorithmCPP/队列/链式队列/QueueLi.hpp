//
//  QueueLi.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/23.
//  Copyright © 2020 Michael. All rights reserved.
//

#ifndef QueueLi_hpp
#define QueueLi_hpp

#include <stdio.h>

//链式队列
template<class Object>
class Queue
{
public:
    Queue();//构造函数
    ~Queue();//析构函数
    //成员函数
    bool isEmpty() const;//队列是否是空的
    const Object & getFront() const;//返回队首的数据，并没有删除
    void enqueue(const Object & x);//入队 把一个数据放入队列里 新放入的数据在后面 出来的数据从前面出来
    Object dequeue();//出队 把队首的数据删除
    void makeEmpty();//整个队列清除
private:
    //私有数据成员
    //嵌套的结构 节点，使用嵌套的。不需要使用友元类了。
    struct ListNode
    {
        Object element;//数据域
        ListNode *next;//指针域 指针指向下一个
        ListNode(const Object & theElement, ListNode *n = 0)//构造函数
        : element(theElement),next(n){};//初始化列表
    };
    //两个指针 私有
    ListNode *front;
    ListNode *back;
};

//构造函数
template<class Object>
Queue<Object>::Queue()
{
    //两个指针都等于0
    front = back = 0;
}

//析构函数
template<class Object>
Queue<Object>::~Queue()
{
    //把整个队列数据都清空
    makeEmpty();
}

template<class Object>
void Queue<Object>::makeEmpty()
{
    while (!isEmpty()) {//如果队列不为空 则一直调用删除函数。
        dequeue();
    }
}

//队列是否是空的
template<class Object>
bool Queue<Object>::isEmpty() const
{
    return front == 0;
}

//读取队首的数据
template<class Object>
const Object & Queue<Object>::getFront() const
{
    if (isEmpty()) {
        throw "Queue is empty";
    } else{
        return front->element;
    }
}

#pragma mark - 入队列
/**
 如果之前是空的：

 新插入一个节点，队首和队尾都是这一个节点。

 如果不是空的：

 新加的节点在最后，队尾的后面。

 队尾就是新加入的节点。
 */
template<class Object>
void Queue<Object>::enqueue(const Object &x)
{
    //如果队列是空的，则只有一个节点
    if (isEmpty()) {
        back = front = new ListNode(x);
    } else {
        back = back->next = new ListNode(x);//back向后指一个 front不变 新加的数据都在后面back
    }
}

#pragma mark - 把队首的数据从队列删除
/**

 删除节点 把节点里面的数据给返回。

 删除就是第一个front的指针指向它的下一个。
 */
template<class Object>
Object Queue<Object>::dequeue()
{
    Object frontItem = getFront();//要删除的节点 队首
    //删除节点
    ListNode *old = front;
    front = front->next;//front指向下一个
    delete old;//对应new
    return frontItem;//返回节点数据
}



#endif /* QueueLi_hpp */
