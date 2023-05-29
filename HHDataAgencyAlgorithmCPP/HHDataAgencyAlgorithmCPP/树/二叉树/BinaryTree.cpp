//
//  BinaryTree.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/12/3.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "BinaryTree.hpp"

using namespace std;

void BinaryTreeTest()
{
    BinaryTree<char> tree;
    TreeNode<char> 加,减,乘,除,a,b,c,d,e;
    加.data = '+';
    减.data = '-';
    乘.data = '*';
    除.data = '/';
    a.data = 'A';
    b.data = 'B';
    c.data = 'C';
    d.data = 'D';
    e.data = 'E';
    
    //组装树
    tree.root = &加;
    加.leftChild = &减;
    加.rightChild = &e;
    减.leftChild = &乘;
    减.rightChild = &d;
    乘.leftChild = &除;
    乘.rightChild = &c;
    除.leftChild = &a;
    除.rightChild = &b;
    
    //中序遍历
    tree.InOrder();
    //前序遍历
    tree.PreOrder();
}
