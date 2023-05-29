//
//  List.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/18.
//  Copyright © 2020 Michael. All rights reserved.
//  模版类实现链表，并且有迭代器功能

/**
 迭代器也是一个类
 一共有三个类：
 1. 节点
 2. 链表
 3. 迭代器
 */

#ifndef List_hpp
#define List_hpp

#include <stdio.h>
#include <iostream>

#pragma mark - 前置声明
template <class Type> class List;//前置声明 声名友元类的时候要用到
template <class Type> class ListIterator;//前置声明

#pragma mark - 节点
template<class Type>
class ListNode
{
    friend class List<Type>;//友元类
    friend class ListIterator<Type>;
    //私有成员
private:
    Type data;//数据
    ListNode *link;//指针 指向链表下一个节点
    ListNode(Type);//私有的构造函数 只能友元类调用。
};

//节点的构造函数定义
template<class Type>
ListNode<Type>::ListNode(Type element)
{
    data = element;//节点里面的数据
    link = 0;//节点的下一个节点
}

#pragma mark - 链表
template<class Type>
class List
{
    friend class ListIterator<Type>;
public:
    List() {first = 0;};//构造函数 first指向0 没有指向节点 一个节点都没有
    void Insert(Type);//在链表里插入节点
    void Delete(Type);//删除
    void Invert();//反转
    void Concatenate(List<Type>);//两个链表链接起来，传进去的是另外一个链表
    void Show();//测试用的。 把链表里面的数据显示出来
private:
    ListNode<Type> *first;//私有成员 是一个指针 指向第一个
};

#pragma mark - 链表迭代器
template<class Type>
class ListIterator
{
public:
    ListIterator(const List<Type>& l) : list(l),current(l.first){}//构造函数 参数就是链表
    bool NotNull();//链表迭代器指向链表当前的节点是不是空的
    bool NextNotNull();//当前节点的下一个节点是不是空的
    Type* First();//返回第一个节点的指针
    Type* Next();//返回当前节点的下一个节点的指针
private://私有数据成员
    const List<Type> &list; //链表list的迭代器
    ListNode<Type>* current;//指向链表里的一个节点
};

#pragma mark - 链表迭代器成员函数的实现
//迭代器当前的节点是否是NULL
//如果有current 则是true 否则就是false
template<class Type>
bool ListIterator<Type>::NotNull()
{
    if (current) {
        return true;
    } else {
        return false;
    }
}
//当前的节点的下一个节点是否NULL
//如果有current当前节点 和当前节点的下一个节点 则是true 否则就是false
template<class Type>
bool ListIterator<Type>::NextNotNull()
{
    if (current && current->link) {
        return true;
    } else {
        return false;
    }
}

template<class Type>
Type* ListIterator<Type>::First()
{
    if (list.first) {
        return &list.first->data;//返回节点里的数据的指针
    } else {
        return 0;
    }
}

//返回当前节点的下一个节点里的数据域的指针
template<class Type>
Type* ListIterator<Type>::Next()
{
    if (current) {
        current = current->link;
        return &current->data;
    } else {
        return 0;
    }
}

#pragma mark - 链表操作
//新的节点永远都插在第一个
template<class Type>
void List<Type>::Insert(Type k)
{
    //插入节点
    //首先创建一个新的节点
    //k是存放新节点里面的数据
    ListNode<Type> *newnode = new ListNode<Type>(k);//调用链表节点的构造函数
    newnode->link = first;//新的节点的下一个是原来的第一个
    first = newnode;//新的节点就变成了第一个
}

template<class Type>
void List<Type>::Delete(Type k)
{
    //要删除一个节点，首先把这个节点找到。
    //被删除节点的前一个节点  这个节点的link指针要指向被删除节点的下一个节点
    ListNode<Type> *previous = 0;//保存要删除节点的前一个节点
    ListNode<Type> *current;//这个指针用来做循环
    
    //previous = current,current = current->link 前一个节点保存下来，当前节点向下移动
    for (current = first;
         current && current->data != k;
         previous = current,current = current->link) {
        //什么都不做，空循环，找到要被删除的节点
    }
    
    //找到了
    if (current) {
        //有前一个节点
        if (previous) {
            previous->link = current->link;
        }
        //要删除的就是第一个，就把第一个指向第一个的下一个。
        else {
            first = first->link;
        }
        delete current;//delete对应insert中节点的new
    }
}

//反转
/**
 1. p：刚开始指向第一个节点，循环一直沿着链表指向下一个节点，直到最后一个节点。
 2. q：保存新链表的最后一个指针
 3. r：r保存q，然后p的下一个节点指向r
 */
template<class Type>
void List<Type>::Invert()
{
    //两个指针 一个指针指向链表的开头 一个指针指向链表的结尾
    ListNode<Type> *p = first, *q = 0;
    while (p) {
        ListNode<Type> *r = q; q = p;
        p = p->link; //p变成p的下一个，向下移动，第一个交换完了 交换第二个
        q->link = r;//r就是q，q（q=p）的下一个指向的是q
    }
    first = q;
}

//链接 把一个链表和另外一个链表进行连接成一个链表
template<class Type>
void List<Type>::Concatenate(List<Type> b)
{
    //如果第一个链表是空的 第一个链表就等于第二个链表的第一个。
    if (!first) {
        first = b.first;
        return;
    }
    
    //如果第二个链表不是空的，找到第一个链表的最后一个。把第二个链表的头接到第一个链表的尾。
    if (b.first) {
        ListNode<Type> *p;//找到第一个链表的最后一个
        for (p = first; p->link; p=p->link) {
            //空循环 找链表的最后一个。空循环里面是什么都不做，循环是为了查找位置节点。
        }
        p->link = b.first;//第一个链表的最后一个的下一个 指向第二个链表的第一个
    }
}

#pragma mark - 把链表里每一个数据显示出来
template<class Type>
void List<Type>::Show()
{
    //开始等于第一个，然后不断的变成下一个。
    for (ListNode<Type> *current = first; current; current = current->link) {
       std::cout << current->data;
        if (current->link) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

#endif /* List_hpp */
