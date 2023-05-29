//
//  BinaryTree.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/12/3.
//  Copyright © 2020 Michael. All rights reserved.
//  C++模版类设计二叉树

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <stdio.h>
#include <iostream>
#include <queue>//C++标准模版库
using namespace std;

#pragma mark - 先做树的前置声明。因为二叉树还有一个类 树的节点。
template<class T> class BinaryTree;//树类的声明

#pragma mark - 节点
template<class T>
class TreeNode
{
public:
    //构造函数
    TreeNode()
    {
        leftChild = NULL;
        rightChild = NULL;
    }
    T data;//数据
    TreeNode<T> *leftChild;//左孩子
    TreeNode<T> *rightChild;//右孩子
};

#pragma mark - 树的定义和操作
template<class T>
class BinaryTree
{
public:
    //二叉树可以进行的操作
    void InOrder();//中序遍历
    void InOrder(TreeNode<T>* currentNode);
    void PreOrder();//前序
    void PreOrder(TreeNode<T>* currentNode);
    void PostOrder();//后序
    void PostOrder(TreeNode<T>* currentNode);
    void LevelOrder();//层序遍历，需要使用队列。
    void Visit(TreeNode<T>* currentNode);//访问当前节点
public:
    TreeNode<T> *root;//拿到根节点 相当于得到整个树
};

#pragma mark - 访问节点
template<class T>
void BinaryTree<T>::Visit(TreeNode<T> *currentNode)
{
    //可以对节点的数据进行处理 想怎么做都可以
    std::cout << currentNode->data;
}

#pragma mark - 中序遍历
template<class T>
void BinaryTree<T>::InOrder()
{
    InOrder(root);
}

template<class T>
void BinaryTree<T>::InOrder(TreeNode<T> *currentNode)
{
    //节点不为空
    if (currentNode) {
        //左子树当前节点右子树
        //可以使用递归
        InOrder(currentNode->leftChild);//对左子节点继续进行中序遍历
        //显示当前节点
        Visit(currentNode);
        InOrder(currentNode->rightChild);//对右子节点继续进行中序遍历
    }
}

#pragma mark - 前序遍历
template<class T>
void BinaryTree<T>::PreOrder()
{
    PreOrder(root);
}

template<class T>
void BinaryTree<T>::PreOrder(TreeNode<T> *currentNode)
{
    //节点不为空
    if (currentNode) {
        //显示当前节点
        Visit(currentNode);
        PreOrder(currentNode->leftChild);//对左子节点进行中序遍历
        PreOrder(currentNode->rightChild);//对右子节点进行中序遍历
    }
}

#pragma mark - 后序遍历
template<class T>
void BinaryTree<T>::PostOrder()
{
    PostOrder(root);
}

template<class T>
void BinaryTree<T>::PostOrder(TreeNode<T> *currentNode)
{
    //节点不为空
    if (currentNode) {
        PostOrder(currentNode->leftChild);//对左子节点进行中序遍历
        PostOrder(currentNode->rightChild);//对右子节点进行中序遍历
        Visit(currentNode);
    }
}

#pragma mark - 层序遍历
template<class T>
void BinaryTree<T>::LevelOrder()
{
    //先声明一个队列 队列里面是节点指针
    std::queue<TreeNode<T>*> q;
    TreeNode<T>* currentNode = root;//从根开始
    while (currentNode) {
        Visit(currentNode);
        //有左子 就放到队列里
        if (currentNode->leftChild) {
            q.push(currentNode->leftChild);
        }
        if (currentNode->rightChild) {
            q.push(currentNode->rightChild);
        }
        //如果队列是空的 就结束
        if (q.empty()) {
            return;
        }
        currentNode = q.front();//从队头取下一个要显示的节点
        q.pop();//然后从队列里删除
    }
}

#endif /* BinaryTree_hpp */
