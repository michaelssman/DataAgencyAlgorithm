//
//  RedBlackTree.hpp
//  CPPDemo00
//
//  Created by Michael on 2020/12/9.
//  Copyright © 2020 Michael. All rights reserved.
//

#ifndef RedBlackTree_hpp
#define RedBlackTree_hpp

#include <stdio.h>
#include "Except.hpp"

#pragma mark - 两个前置声明
template <class Comparable>
class RedBlackTree;

template <class Comparable>
class RedBlackNode;

//自定义引用类型
template <class Object>
class Cref
{
public:
    //没有参数的构造函数
    Cref() : obj(NULL) {}//指针传NULL
    //显示的构造函数
    explicit Cref(const Object & x) : obj(&x) {} //初始化
    
    //通过引用操作数据
    const Object & get() const
    {
        if (isNull()) {
            throw NullPointerException(); //抛出异常
        } else {
            //不是空的 返回数据
            return *obj;
        }
    }
    
    //成员函数
    //判断引用是不是空的 如果指针是空的 则引用是空的
    bool isNull() const
    {
        return obj == NULL;
    }
    
private:
    const Object *obj;//指针
};

#pragma mark - 红黑树的完整定义
template <class Comparable>
class RedBlackTree
{
public:
    RedBlackTree(const Comparable & negInf);//构造函数
    ~RedBlackTree();//析构函数
    
    //找指定的数
    Cref<Comparable> find(const Comparable & x) const;//找的数是x。 如果返回指针（找不到就返回空指针） 如果返回引用（找不到怎么办 C++引用必须引用对象 不能是空的，所以自己做引用类型Cref,Cref也是模版）
    Cref<Comparable> findMin() const;//找最小的数
    Cref<Comparable> findMax() const;
    
    //判断是不是空树
    bool isEmpty() const;
    //清空
    void makeEmpty() const;
    
    enum {RED,BLACK};//枚举 节点颜色，红色，黑色。
    
    void insert(const Comparable & x);//插入新的数据 会创建新的节点
    
    typedef RedBlackNode<Comparable> Node;//定义别名，原名太长了。
//private: //应该是私有的，为了测试，临时改成puglic
public:
    //两个重要的私有成员 这两个都是节点
    Node *header;//红黑树的头 -∞
    Node *nullNode;//空节点
    
    //插入过程 需要下面几个节点
    Node *current;  //指向当前节点
    Node *parent;   //指向当前节点的父节点
    Node *grand;    //指向当前节点的祖父节点
    Node *great;    //指向当前节点的曾祖父节点
    
    void reclaimMemory(Node *t) const;//清除节点 清空函数会用到
    
    //带着左孩子 向右转
    void rotateWithLeftChild(Node * & k2) const;
    //带着右孩子 向左转
    void rotateWithRightChild(Node * & k1) const;
    
    ///双旋转
    //带着左孩子向右转
    void doubleRotateWithLeftChild(Node * & k3) const;
    //带着右孩子向左转
    void doubleRotateWithRightChild(Node * & k1) const;
    
    //通用的函数 旋转 改变颜色
    void handleReorient(const Comparable & item);//重新调整
        
    /// 旋转通用函数
    /// @param item 被转节点
    /// @param parent 被转的父节点
    RedBlackNode<Comparable> * rotate(const Comparable & item, Node *parent) const;
};

//红黑节点
template <class Comparable>
class RedBlackNode
{
    //private: //为了测试，临时改成puglic
public:
    Comparable element;
    RedBlackNode *left;
    RedBlackNode *right;
    int color;
    /**
     参数 对应上面的4个成员
     1. 保存节点中的数据 模版类型
     2.
     3.
     4. 颜色 默认值是黑色
     冒号：后面的叫初始化序列，
     */
    RedBlackNode(const Comparable & theElement = Comparable(),
                 RedBlackNode *lt = NULL,
                 RedBlackNode *rt = NULL,
                 int c = RedBlackTree<Comparable>::BLACK)
    : element(theElement),left(lt),right(rt),color(c){}//构造函数 颜色默认黑色
    
    friend class RedBlackTree<Comparable>;//友元 可以访问私有成员
};

#pragma mark - 红黑树构造函数
//参数只有一个 负无穷大
template <class Comparable>
RedBlackTree<Comparable>::RedBlackTree(const Comparable & negInf)
{
    //初始化
    nullNode = new Node();//调用构造函数。参数都是默认的
    nullNode->left = nullNode->right = nullNode;//左子右子都是空的
    header = new Node(negInf);//伪头 调用构造函数 第一个参数是传过去了，其他参数是默认的。
    header->left = header->right = nullNode;
}

//析构函数
template <class Comparable>
RedBlackTree<Comparable>::~RedBlackTree()
{
    //构造函数用的new 析构要delete
    makeEmpty();
    delete nullNode;
    delete header;
}

#pragma mark - 插入 数据x
template <class Comparable>
void RedBlackTree<Comparable>::insert(const Comparable &x)
{
    //开始的时候 current等于header
    current = parent = grand = header;
    //把要插入的数据先放到空指针里
    nullNode->element = x;
    
    //找合适的位置  开始的时候current等于header 从根开始不断的向左向右找位置
    //使用循环查找新的节点插入的位置。
    while (current->element != x) {//树里不允许有重复的数据
        great = grand;
        grand = parent;
        parent = current;
        
        //做平衡的时候要用到上面的几个节点
        
        //新插入的数据比当前节点数据小就找左子 大就找右子
        current = x < current->element ? current->left : current->right;
        
        
        //在循环中可能遇到一个节点的两个孩子都是红色的，需要做处理
        //进行检查 如果当前节点和左孩子颜色是红色的并且右孩子的颜色也是红色的 这时候就需要做处理调整。
        //变成左儿子是红色的 右儿子是黑色的
        if (current->left->color == RED && current->right->color == RED) {
            handleReorient(x);
        }
    }
    
    //找到了相等了 找到了重复的抛出异常
    if (current != nullNode) {
        throw DuplicateItemException();
    }
    current = new Node(x,nullNode,nullNode);
    //新节点插入
    if (x < parent->element) {
        parent->left = current;
    } else {
        parent->right = current;
    }
    //上面的代码 实现二叉树
    //自动平衡 --》 红黑树
    //自动平衡是重点 需要用到旋转
    
    //新插入的节点是红色的 父节点也是红色的 需要再做一个处理 旋转
    handleReorient(x);//这个函数是通用的函数，改变颜色，旋转

}

#pragma mark - 两个旋转函数
//旋转 向右转
template <class Comparable>
void RedBlackTree<Comparable>::rotateWithLeftChild(Node * & k2) const
{
    Node *k1 = k2->left;//k1是k2的左子
    k2->left = k1->right;//横向移动
    k1->right = k2;//旋转之后k1的右边就是k2
    k2 = k1;//k1上升，变成了根
}

//向左转
template <class Comparable>
void RedBlackTree<Comparable>::rotateWithRightChild(Node * & k1) const
{
    Node *k2 = k1->right;
    k1->right = k2->left;//横向移动
    k2->left = k1;//旋转之后的k2的left是k1
    k1 = k2;//
}

///带着左孩子向右转
template <class Comparable>
void RedBlackTree<Comparable>::doubleRotateWithLeftChild(Node * & k3) const
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <class Comparable>
void RedBlackTree<Comparable>::doubleRotateWithRightChild(Node *&k1) const
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}


///这个函数在insert函数调了两次
template <class Comparable>
void RedBlackTree<Comparable>::handleReorient(const Comparable &item)
{
    //变色
    current->color = RED;//变红色 遇到节点有两个红色的孩子 则节点要变色
    //左右两个孩子变黑色
    current->left->color = BLACK;
    current->right->color = BLACK;

    //如果父节点是红色的 需要旋转
    if (parent->color == RED) {
        //先把爷爷节点变成黑色
        grand->color = RED;
        
        //然后判断内部孙子 外部孙子
        //内部孙子：小于爷爷 大于爸爸 或大于爷爷 小于爸爸。
        //内部孙子不会同时比爷爷和爸爸小 不会比爷爷和爸爸同时大
        if (item < grand->element != item < parent->element) {//不会同时大 同时小
            //内部孙子
            //加多一次旋转 双旋转
            parent = rotate(item, grand);
        }
        
        //如果一个节点比爷爷小 比爸爸小 则是左外部孙子
        //如果一个节点比爷爷大 比爸爸大 则是右外部孙子
        //外部孙子 只做一次旋转
        current = rotate(item, great);
        
        //当前节点变黑的 因为父节点是红的
        current->color = BLACK;
    }
    //最后把根节点变黑的。根节点必须是黑的
    header->right->color = BLACK;
}

//旋转通用函数
template <class Comparable>
/// 通用函数 根据大小 自动旋转
/// @param item 被旋转节点
/// @param theParent 父节点
RedBlackNode<Comparable> * RedBlackTree<Comparable>::rotate(const Comparable &item, Node *theParent) const
{
    //分四种情况
    //根据大小判断，红黑树是二叉树
    //左子向左转 向右转
    //左子树
    if (item < theParent->element) {
        //向左转向右转 根据大小判断
        //比左边的小 向右转。
        item < theParent->left->element ? rotateWithLeftChild(theParent->left) :
        rotateWithRightChild(theParent->left);
        return theParent->left;
    }
    //右子树
    else {
        item < theParent->right->element ?
        rotateWithLeftChild(theParent->right) :
        rotateWithRightChild(theParent->right);
        return theParent->right;
    }
}

#pragma mark - 判断二叉树是不是空树
template <class Comparable>
bool RedBlackTree<Comparable>::isEmpty() const
{
    //是否是空的红黑树 判断伪根header右子节点（根）是不是空节点
    //创建的时候就是nullNode 如果等于nullNode就是空的
    return header->right == nullNode;
}

#pragma mark - 清空
template <class Comparable>
void RedBlackTree<Comparable>::makeEmpty() const
{
    //红黑树里所有的节点删除 节点是insert函数里new创建出来的 按照C++要求就需要delete删除
    //delete删除所有的节点 节点数可能多可能少
    //使用reclaimMemory函数从根节点开始清除
    reclaimMemory(header->right);
    header->right = nullNode;
}

template <class Comparable>
void RedBlackTree<Comparable>::reclaimMemory(Node *t) const
{
    //使用递归设计 所有的子子孙孙清除
    if (t != t->left) {//到叶子节点t == t->left或者t == t->right 停止递归。因为叶子结点的子结点是空的，子结点和子结点也是空的，所以如果都是空的则停止递归。
        reclaimMemory(t->left);//左子节点清除
        reclaimMemory(t->right);//右子节点清除
        delete t;//清除
    }
}

//查找最小的
template <class Comparable>
Cref<Comparable> RedBlackTree<Comparable>::findMin() const
{
    //红黑树是不是空的。是空的就返回空引用
    if (isEmpty()) {
        return Cref<Comparable>();
    }
    //不是空的就从根节点一直向左最找最小的，找到最后的时候 左右子都是nullNode
    Node *itr = header->right;
    while (itr->left != nullNode) {
        itr = itr->left;
    }
    return Cref<Comparable>(itr->element);
}
//查找最大的 向右
template <class Comparable>
Cref<Comparable> RedBlackTree<Comparable>::findMax() const
{
    //红黑树是不是空的。是空的就返回空引用
    if (isEmpty()) {
        return Cref<Comparable>();
    }
    //不是空的就从根节点开始一直向右找右子节点最大的，找到最后的时候 左右子都是nullNode
    Node *itr = header->right;
    while (itr->right != nullNode) {
        itr = itr->right;
    }
    return Cref<Comparable>(itr->element);
}
//查找指定的数
template <class Comparable>
Cref<Comparable> RedBlackTree<Comparable>::find(const Comparable &x) const
{
    //要找的数是x
    nullNode->element = x;
    Node *curr = header->right;//节点指针 从根节点开始
    for (; ;) {
        if (x < curr->element) {
            curr = curr->left;
        } else if (x > curr->element) {
            curr = curr->right;
        } else if (curr != nullNode) {
            //找到了
            return Cref<Comparable>(curr->element);
        } else {
            //没找到 返回空引用
            return Cref<Comparable>();
        }
    }
}

#endif /* RedBlackTree_hpp */
