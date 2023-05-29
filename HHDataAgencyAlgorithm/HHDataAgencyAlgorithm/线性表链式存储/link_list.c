//
//  main.c
//  HHDataAgencyAlgorithm
//
//  Created by Michael on 2022/4/21.
//  线性表链式存储

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

#pragma mark - //定义结点
typedef struct Node{
    ElemType data;      //数据域
    struct Node *next;  //指针域
}Node;

typedef struct Node * LinkList;//重定义


#pragma mark - //2.1 初始化单链表线性表
Status InitList(LinkList *L){
    
    //产生头结点,并使用L指向此头结点
    *L = (LinkList)malloc(sizeof(Node));
    //存储空间分配失败
    if(*L == NULL) return ERROR;
    //将头结点的指针域置空
    (*L)->next = NULL;
    
    return OK;
}


#pragma mark - //2.2 单链表插入
/*
 初始条件:顺序线性表L已存在,1≤i≤ListLength(L);
 操作结果：在L中第i个位置之后插入新的数据元素e，L的长度加1;
 */
Status ListInsert(LinkList *L,int i,ElemType e){
 
    int j;
    LinkList p,s;
    p = *L;
    j = 1;
    
    //寻找第i-1个结点
    while (p && j<i) {
        p = p->next;
        ++j;
    }
    
    //第i个元素不存在
    if(!p || j>i) return ERROR;
    
    //生成新结点s
    s = (LinkList)malloc(sizeof(Node));
    //将e赋值给s的数值域
    s->data = e;
    //将p的后继结点赋值给s的后继
    s->next = p->next;
    //将s赋值给p的后继
    p->next = s;
    
    return OK;
}


#pragma mark - //2.3 单链表取值
/*
 初始条件: 顺序线性表L已存在,1≤i≤ListLength(L);
 操作结果：用e返回L中第i个数据元素的值
 */
Status GetElem(LinkList L,int i,ElemType *e){
    
    //j: 计数.
    int j;
    //声明结点p;
    LinkList p;
    
    //将结点p 指向链表L的第一个结点;
    p = L->next;
    //j计算=1;
    j = 1;
    
    
    //p不为空,且计算j不等于i,则循环继续
    while (p && j<i) {
        
        //p指向下一个结点
        p = p->next;
        ++j;
    }
    
    //如果p为空或者j>i,则返回error
    if(!p || j > i) return ERROR;
    
    //e = p所指的结点的data
    *e = p->data;
    return OK;
    
    
}

#pragma mark - //2.4 单链表删除元素
/*
 初始条件：顺序线性表L已存在，1≤i≤ListLength(L)
 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1
 */

Status ListDelete(LinkList *L,int i,ElemType *e){
    
    int j;
    LinkList p,q;
    p = (*L)->next;
    j = 1;
    
    //查找第i-1个结点,p指向该结点
    while (p->next && j<(i-1)) {
        p = p->next;
        ++j;
    }
    
    //当i>n 或者 i<1 时,删除位置不合理
    if (!(p->next) || (j>i-1)) return  ERROR;
    
    //q指向要删除的结点
    q = p->next;
    //将q的后继赋值给p的后继
    p->next = q->next;
    //将q结点中的数据给e
    *e = q->data;
    //让系统回收此结点,释放内存;
    free(q);
    
    return OK;
}

#pragma mark - 单链表的遍历
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L)
{
    LinkList p=L->next;//因为有头节点，所以头节点的下一个才是首元节点
    while(p)
    {
        printf("%d\n",p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{
    LinkList p,q;
    p=(*L)->next;           /*  p指向第一个结点 */
    while(p)                /*  没到表尾 */
    {
        q=p->next;
        free(p);
        p=q;
    }
    (*L)->next=NULL;        /* 头结点指针域为空 */
    return OK;
}

#pragma mark - //3.1 单链表前插入法，创建单链表
/* 随机产生n个元素值,建立带表头结点的单链线性表L(前插法)*/
void CreateListHead(LinkList *L, int n){
    
    LinkList p;
    
    //建立1个带头结点的单链表
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    
    //循环前插入随机数据
    for(int i = 0; i < n;i++)
    {
        //生成新结点
        p = (LinkList)malloc(sizeof(Node));
       
        //i赋值给新结点的data
        p->data = i;
        //p->next = 头结点的L->next
        p->next = (*L)->next;
        
        //将结点P插入到头结点之后;
        (*L)->next = p;
        
    }
}

#pragma mark - //3.2 单链表后插入法，创建单链表
/* 随机产生n个元素值,建立带表头结点的单链线性表L(后插法)*/
void CreateListTail(LinkList *L, int n){
    
    LinkList p,r;
 
    //建立1个带头结点的单链表
    *L = (LinkList)malloc(sizeof(Node));
    //r指向尾部的结点
    r = *L;
    
    for (int i=0; i<n; i++) {
        
        //生成新结点
        p = (Node *)malloc(sizeof(Node));
        p->data = i;
        
        //将表尾终端结点的指针指向新结点
        r->next = p;
        //将当前的新结点定义为表尾终端结点
        r = p;
    }
    
    //将尾指针的next = null
    r->next = NULL;
    
}

void link_list_test(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    Status iStatus;
    LinkList L;
    struct Node *L2;
    ElemType e;
    
//    L1 =(LinkList) malloc(sizeof(Node));
//    L2 =(LinkList) malloc(sizeof(Node));
//
//    L1->data = 1;
//    L2->data = 2;
//    printf("L1.data=%d,L2.data=%d\n",L1->data,L2->data);
    
    //2.1 单链表初始化
    iStatus = InitList(&L);
    printf("L 是否初始化成功?(0:失败,1:成功) %d\n",iStatus);
    
    //2.2 单链表插入数据
    for(int j = 1;j<=10;j++)
    {
        iStatus = ListInsert(&L, 1, j);
    }
    printf("L 插入后\n");
    ListTraverse(L);
    
    //2.3 单链表获取元素
    GetElem(L,5,&e);
    printf("第5个元素的值为：%d\n",e);
    
    //2.4 删除第5个元素
    iStatus = ListDelete(&L, 5, &e);
    printf("删除第5个元素值为:%d\n",e);
    ListTraverse(L);
    
    //3.1 前插法整理创建链表L
    iStatus = ClearList(&L);
    CreateListHead(&L, 20);
    printf("整理创建L的元素(前插法):\n");
    ListTraverse(L);
    
    //3.2 后插法整理创建链表L
    iStatus = ClearList(&L);
    CreateListTail(&L, 20);
    printf("整理创建L的元素(后插法):\n");
    ListTraverse(L);
    
}
