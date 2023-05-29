//
//  BiT.hpp
//  HHDataAgencyAlgorithmCPP
//
//  Created by Michael on 2022/10/11.
//

#ifndef BiT_hpp
#define BiT_hpp

#include <stdio.h>

/**
//二叉树的二叉链表存储表示
typedef  struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;//左右孩子指针
}BiTNode, *BiTree;
 */

//等于下面
struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;//左右孩子指针
};
typedef struct BiTNode BiTNode;
typedef struct BiTNode* BiTree;

int sum;
void countLeaf(BiTNode *T)
{
    if (T != NULL) {
        if (T->lchild == NULL && T->rchild == NULL) {
            sum ++;
        }
        if (T->lchild) {
            countLeaf(T->lchild);
        }
        if (T->rchild) {
            countLeaf(T->rchild);
        }
    }
}
//上面方法在多线程中 会对sum资源争夺。
void countLeaf3(BiTNode *T, int *sum)
{
    if (T != NULL) {
        if (T->lchild == NULL && T->rchild == NULL) {
            (*sum) ++;
        }
        if (T->lchild) {
            countLeaf3(T->lchild, sum);
        }
        if (T->rchild) {
            countLeaf3(T->rchild, sum);
        }
    }
}

int Depth(BiTNode *T)
{
    int deptleft = 0;
    int deptright = 0;
    int deptval = 0;
    if (T == NULL) {
        deptval = 0;
        return deptval;
    }
    //左子树高度
    deptleft = Depth(T->lchild);
    //右子树高度
    deptright = Depth(T->rchild);
    
    //+1
    deptval = 1 + (deptleft > deptright ? deptleft : deptright);
    return deptval;
}
#endif /* BiT_hpp */
