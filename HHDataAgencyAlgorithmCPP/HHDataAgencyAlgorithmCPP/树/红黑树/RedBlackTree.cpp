//
//  RedBlackTree.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/12/9.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "RedBlackTree.hpp"
#include <iostream>

using namespace std;

void RedBlackTreeTest()
{
    const int NEG_INF = -99999; //刚创建一个红黑树，红黑树一个节点都没有，根节点也没有。往红黑树中插入insert的时候，第一次才有根。
    RedBlackTree<int> t(NEG_INF);//很大的负数，一个节点都没有 是空的。一个特殊的节点。伪根。
//    t.insert(50);
//    t.insert(40);
//    t.insert(30); //如果这里不是红黑树 就退化成链表的。
//    //动态调整 红黑树根动态变化 保证根的左子树右子树深度基本一致 红色节点数一致
//    //如果是普通的二叉查找树 根是50 不变
//    //红黑树会自动调整平衡

    
    /*
    t.insert(30);
    t.insert(15);
    t.insert(70);
    t.insert(20);

    //根节点
    cout << t.header->right->element << endl;
    cout << t.header->right->left->element << endl;
    cout << t.header->right->right->element << endl;
    cout << t.header->right->left->right->element << endl;


    //向右转
    t.rotateWithLeftChild(t.header->right);
    cout << t.header->right->element << endl;
    cout << t.header->right->right->left->element << endl;

    //向左转
    t.rotateWithRightChild(t.header->right);
    //先向右转后又向左转 就还原了 和转之前一样
    cout << t.header->right->element << endl;
    cout << t.header->right->left->element << endl;
    cout << t.header->right->right->element << endl;
    cout << t.header->right->left->right->element << endl;
     */

    
    //双旋转
    t.insert(12);
    t.insert(16);
    t.insert(8);
    t.insert(10);
    t.insert(4);
    t.insert(14);
    t.insert(2);
    t.insert(6);
    t.insert(5);
    //旋转前的根
    cout << t.header->right->element << endl;

    t.doubleRotateWithLeftChild(t.header->right->left);//8 向右转
    
}

//测试
void test()
{
    const int NEG_INF = -99999;
    RedBlackTree<int> t(NEG_INF);//很大的负数，一个节点都没有 是空的。一个特殊的节点。伪根。
    t.insert(50);
    t.insert(40);
    t.insert(30); //如果这里不是红黑树 就退化成链表的。
    //动态调整 红黑树根动态变化 保证根的左子树右子树深度基本一致 红色节点数一致
    //如果是普通的二叉查找树 根是50 不变
    //红黑树会自动调整平衡

    //根
    cout << t.header->right->element << endl;
    
    //是不是空的
    if (!t.isEmpty()) {
        cout << "红黑树不是空的" << endl;
    }
    
    //清空
    t.makeEmpty();
    if (t.isEmpty()) {
        cout << "红黑树是空的" << endl;
    }
    
    //查找
    Cref<int> r = t.find(66);
    if (r.isNull()) {
        cout << "没找到";
    } else {
        cout << "找到：" << r.get() << endl;
    }
    
    t.insert(200);
    t.insert(100);
    t.insert(90);
    t.insert(50);
    t.insert(80);
    t.insert(70);
    t.insert(60);

    if (t.findMin().get() == 50) {
        cout << "找到了最小的数" << endl;
    }
    cout << "最大的：" << t.findMax().get() << endl;

//    cout << t.header->right->element << endl;
//    cout << t.header->right->right->left->element << endl;
//
//    //向左转
//    t.rotateWithRightChild(t.header->right);
}
