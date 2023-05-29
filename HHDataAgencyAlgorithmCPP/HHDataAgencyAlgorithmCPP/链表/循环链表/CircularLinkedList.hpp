//
//  CircularLinkedList.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/19.
//  Copyright © 2020 Michael. All rights reserved.
//  循环链表

#ifndef CircularLinkedList_hpp
#define CircularLinkedList_hpp

#include <stdio.h>
#include <iostream>

template <class Type> class List;//前置声明 声名友元类的时候要用到
template <class Type> class ListIterator;//前置声明

#pragma mark - 链表节点
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
    ListNode(){}//默认的构造函数
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
//    //没有表头的链表
//    List() {first = 0;};//构造函数 first指向0 没有指向节点 一个节点都没有
    
    //有表头的链表 循环链表有表头 指向自己
    List() {first = new ListNode<Type>; first->link = first;};//first指向表头,first的下一个指向first。
    
    void Insert(Type);//在链表里插入节点
    void Delete(Type);//删除
private:
    ListNode<Type> *first;//私有成员 是一个指针
};

#pragma mark - 链表迭代器
template<class Type>
class ListIterator
{
public:
    ListIterator(const List<Type>& l) : list(l),current(l.first->link){}//构造函数 参数就是链表//构造函数 要使用first的下一个，因为first是空的。
    bool NotNull();//链表迭代器当前指向的节点是不是空的
    bool NextNotNull();//当前节点的下一个节点是不是空的
    Type* First();//返回第一个节点的指针
    Type* Next();//返回当前节点的下一个
private://私有数据成员
    const List<Type> &list; //链表的迭代器
    ListNode<Type>* current;//指向链表里的一个节点
};

//返回链表第一个节点里的数据的指针
template<class Type>
Type* ListIterator<Type>::First()
{
    if (current != list.first) {//first是空的
//        return &list.first->data;
        return &current->data;
    } else {
        return 0;
    }
}

//返回当前节点的下一个节点里的数据域的指针
//如果是最后一个节点的下一个，就再往后移动一次。因为最后一个节点的下一个是表头first first是空的。
template<class Type>
Type* ListIterator<Type>::Next()
{
    current = current->link;
    //指向了表头，表头是空的，就再向下移动一次。从最后一个到第一个。
    //最后一个的下一个是表头first。first是空的。所以还需要再向下一个。
    if (current == list.first) {
        current = current->link;
    }
    return &current->data;
}

template<class Type>
bool ListIterator<Type>::NotNull()
{
    if (current != list.first) {//first是空 其它不为空
        return true;
    } else {
        return false;
    }
}

template<class Type>
bool ListIterator<Type>::NextNotNull()
{
    //当前节点的下一个不等于first
    if (current->link != list.first) {
        return true;
    } else {
        return false;
    }
}

#pragma mark - Insert
//新插入的节点放在表头first的后面
/**
 每次都是从头插：
 1. 用k去生成一个节点
 2. 新节点的下一个节点是头节点的下一个节点
 3. 头节点的下一个节点是新节点
 link就是指下一个节点。
 */
template<class Type>
void List<Type>::Insert(Type k)
{
    //插入节点
    //首先创建一个新的节点
    //k是存放新节点里面的数据，使用k创建一个新的节点
    ListNode<Type> *newnode = new ListNode<Type>(k);
    newnode->link = first->link;//新的节点的下一个是表头的下一个
    first->link = newnode;//新的节点就变成了第一个
}

#pragma mark - Delete
template<class Type>
void List<Type>::Delete(Type k)
{
    //要删除一个节点，首先把这个节点找到。
    //被删除节点的前一个节点  这个节点的link指针要指向被删除节点的下一个节点
    ListNode<Type> *previous = first;//fitst是表头 表头是空的
    ListNode<Type> *current;//这个指针用来做循环
    for (current = first->link;
         (current!=first) && current->data != k; //current==first因为是循环的 这是找了一圈又回来了
         previous = current,current = current->link) {
        //什么都不做，空循环，找到要被删除的节点
    }
    if (current != first) {//找到了
        previous->link = current->link;
        delete current;
    }
}

#endif /* CircularLinkedList_hpp */
