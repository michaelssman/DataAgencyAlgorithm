//
//  DblList.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/20.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "DblList.hpp"
#include <iostream>

using namespace std;

#pragma mark - 前置声明
class DblList;//前置声明

#pragma mark - 双向链表节点
class DblListNode
{
    friend class DblList;//友元类
public:
    int data;//保存int整型数据
    DblListNode *llink,*rlink;//两个指针
};

#pragma mark - 链表
class DblList
{
public:
    //构造函数 构造函数first的左节点和右节点都指自己。刚开始是空的。
    DblList()
    {
        //创建表头结构
        first = new DblListNode();
        first->llink = first->rlink = first;//左节点右节点都指向自己
    };
    //插入新节点，一个节点插入到一个节点的右边，两个参数
    void Insert(DblListNode*,DblListNode*);
    //删除一个节点（指针指向的节点）
    void Delete(DblListNode*);
//private:
public:
    DblListNode *first;//指向表头结构
};

#pragma mark - 链表操作
/// 插入新节点
/// @param p 新插入的节点
/// @param x p插入到x节点的右边
void DblList::Insert(DblListNode *p, DblListNode *x)
{
    //有四个指针指向需要调整
    p->llink = x;
    p->rlink = x->rlink;
    x->rlink->llink = p;
    x->rlink = p;
}

void DblList::Delete(DblListNode *x)
{
    if (x == first) {
        //表头节点不允许删除
        std::cerr << "Deletion of head node not permitted" << std::endl;
    } else {
        x->llink->rlink = x->rlink;
        x->rlink->llink = x->llink;
        delete x;//创建的节点 删除和new相对应。没有new就不用delete。如果x是指针 使用new创建 则可以`delete x`; 否则是在外面delete。
    }
}

//测试
void dblListTest()
{
    DblList intList;
    DblListNode *node1,*node2,*node3,*node4,*node5;
    node1 = new DblListNode();
    node2 = new DblListNode();
    node3 = new DblListNode();
    node4 = new DblListNode();
    node5 = new DblListNode();
    node1->data = 10;
    node2->data = 20;
    node3->data = 30;
    node4->data = 40;
    node5->data = 50;
    
    intList.Insert(node1, intList.first);
    intList.Insert(node2, intList.first);
    intList.Insert(node3, intList.first);
    intList.Insert(node4, intList.first);
    intList.Insert(node5, intList.first);
    
    intList.Delete(node3);
    
    cout << intList.first->rlink->data << endl;
    cout << intList.first->rlink->rlink->data << endl;
    cout << intList.first->rlink->rlink->rlink->data << endl;
    cout << intList.first->rlink->rlink->rlink->rlink->data << endl;
    cout << intList.first->rlink->rlink->rlink->rlink->llink->data << endl;
    cout << intList.first->rlink->rlink->rlink->rlink->llink->llink->data << endl;
}
