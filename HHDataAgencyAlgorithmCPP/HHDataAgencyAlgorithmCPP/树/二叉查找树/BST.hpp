//
//  BST.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/12/5.
//  Copyright © 2020 Michael. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include <iostream>

//自己做的bool类型  使用枚举 FALSE是0 TRUE是1
enum Boolean {FALSE, TRUE};

//节点中的数据
template<class Type>
class Element
{
public:
    Type key;
    //使用Element可以很容易的添加更多新的数据，不止一个。
};

template<class Type> class BST;//前置声明

#pragma mark - 树的节点
template<class Type>
class BSTNode
{
    friend class BST<Type>;
//private:
public://为了测试写为public
    //节点里的数据
    Element<Type> data;
    BSTNode* LeftChild;
    BSTNode* RightChild;
    void display(int i); //显示当前节点
};

#pragma mark - 二叉查找树
template<class Type>
class BST
{
public://公有成员
    //构造函数
    BST(BSTNode<Type> *init = 0)
    {
        root = init;
    }
    //插入数据
    Boolean Insert(const Element<Type>& x);//Boolean是自己写的，不是C++的bool
    
    //查找 要找的数据x。下面两个方法是一起的。
    BSTNode<Type>* Search(const Element<Type>& x);//用递归实现
    BSTNode<Type>* Search(BSTNode<Type>*, const Element<Type>&);//查找的时候递归的方法
    
    //迭代查找 没有使用递归
    BSTNode<Type>* IterSearch(const Element<Type>&);
    
    //显示二叉查找树每一个节点
    void display()
    {
        std::cout << "\n";
        //如果有根
        if (root) {
            root->display(1);//位置是1
        } else {
            std::cout << "这是一颗空树\n";
        }
    }
private:
    BSTNode<Type> *root;//根
};

#pragma mark - 显示当前节点的数据 和所有左子树右子树里面的数据。使用递归
template<class Type>
void BSTNode<Type>::display(int i)
{
    std::cout << "Position: " << i << "， data key = " << data.key << "\n";
    //如果节点有左孩子 继续display
    if (LeftChild) {
        LeftChild->display(2*i);
    }
    //如果节点有右孩子 继续display
    if (RightChild) {
        RightChild->display(2*i+1);
    }
}

template<class Type>
Boolean BST<Type>::Insert(const Element<Type> &x)
{
    //首先拿到根
    BSTNode<Type> *p = root;//开始的时候p指向根，p是变化的，不断向左向右。
    BSTNode<Type> *q = 0; //q指向p的父节点
    //insert之前需要先查找
    while (p) {
        q = p;//每次p变为左孩子或右孩子之前先把p保存下来。
        if (x.key == p->data.key) {
            return FALSE;//发生重复，失败返回FALSE
        }
        if (x.key < p->data.key) {
            p = p->LeftChild;
        } else {
            p = p->RightChild;
        }
    }
    
    //找到的位置就是q
    p = new BSTNode<Type>;
    p->LeftChild = p->RightChild = 0;
    p->data = x;
    if (!root) {//树是空的
        root = p;
    } else if (x.key < q->data.key) {
        q->LeftChild = p;
    } else {
        q->RightChild = p;
    }
    return TRUE;
}

#pragma mark - 递归查找
template<class Type>
BSTNode<Type>* BST<Type>::Search(const Element<Type> &x)
{
    return Search(root, x);
}

template<class Type>
//b表示从b节点开始查找 x是要查找的数据。 从b节点开始找x这个数
BSTNode<Type>* BST<Type>::Search(BSTNode<Type> *b, const Element<Type> &x)
{
    if (!b) {
        return 0;
    }
    if (x.key == b->data.key) {
        return b;
    }
    if (x.key < b->data.key) {
        return Search(b->LeftChild, x);
    }
    return Search(b->RightChild, x);
}

#pragma mark - 非递归查找，迭代查找
template<class Type>
BSTNode<Type>* BST<Type>::IterSearch(const Element<Type> &x)
{
    for (BSTNode<Type>* t = root; t; ) {
        if (x.key == t->data.key) {
            return t;
        }
        if (x.key < t->data.key) {
            t = t->LeftChild;
        } else {
            t = t->RightChild;
        }
    }
    return 0;
}
#endif /* BST_hpp */
