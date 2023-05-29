//
//  Stack.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/16.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "Stack.hpp"
#include "require.hpp"

//初始化Link
//::名称空间 作用域
void Stack::Link::initialize(void* dat, Link* nxt)
{
    data = dat;
    next = nxt;
}

//初始化堆栈
void Stack::initialize()
{
    head = 0;
}
// 把数据放入堆栈
void Stack::push(void* dat)
{
    //数据是保存在Link里面的
    Link* newLink = new Link;
    newLink -> initialize(dat, head);
    head = newLink;
}
//查看最上面的数 head
void* Stack::peak()
{
    //加一个检查，头指针不能是0，是0的话栈就是空的。
    require(head != 0, "Stack empty");
    return head->data;
}
//从堆栈中取数据
void* Stack::pop()
{
    if (head == 0) {
        return 0;
    }
    void* result = head->data;
    //head指向下一个指针，原来的head指向的就删除了
    Link* oldHead = head;//原来的head指针
    head = head->next;//head指向下一个数据
    delete oldHead;//原来的head就不要了
    return result;
}
//清理堆栈
void Stack::cleanup()
{
    //加一个检查，如果head==0,则堆栈是空的。
    require(head == 0, "Stack empty");
    //这里并没有做真正的清理，让外部使用pop做清理，这里就只有一个是否为空的检查。
}
