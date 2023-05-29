//
//  main.c
//  HHDataAgencyAlgorithm
//
//  Created by Michael on 2022/4/21.
//  线性表顺序存储（逻辑相邻，物理存储地址相邻）

#include <stdio.h>
#include "stdlib.h"
#include "math.h"
#include "time.h"


#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

/* ElemType类型根据实际情况而定，这里假设为int */
typedef int ElemType;
/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int Status;

/*线性结构使用顺序表的方式存储*/

//顺序表结构设计
typedef struct {
    ElemType *data; //数据
    int length;     //数组长度
}Sqlist;

//1.1 顺序表初始化
Status InitList(Sqlist *L){//传指针，因为要修改链表本身，所以要把地址传进来。
    //为顺序表分配一个大小为MAXSIZE 的数组空间
    L->data =  malloc(sizeof(ElemType) * MAXSIZE);
    //存储分配失败退出
    if(!L->data) exit(ERROR);
    //空表长度为0
    L->length = 0;
    return OK;
}

//1.2 顺序表的插入
/*
 1. 初始条件：顺序线性表L已存在，位置合法：1≤i≤ListLength(L);
 2. 找到位置，位移
 3. 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1
 */
Status ListInsert(Sqlist *L,int i,ElemType e){//因为要修改 所以传L的指针
    
    //i值不合法判断
    if((i<1) || (i>L->length+1)) return ERROR;
    //存储空间已满
    if(L->length == MAXSIZE) return ERROR;
 
    //插入数据不在表尾,则先移动出空余位置
    if(i <= L->length){
        for(int j = L->length-1; j>=i-1;j--){
            //插入位置以及之后的位置后移动1位
            L->data[j+1] = L->data[j];
        }
    }
    
    //将新元素e 放入第i个位置上
    L->data[i-1] = e;
    //长度+1;
    ++L->length;
    
    return OK;
}

//1.3 顺序表的取值
Status GetElem(Sqlist L,int i, ElemType *e){
    //判断i值是否合理, 若不合理,返回ERROR
    if(i<1 || i > L.length) return  ERROR;
    //data[i-1]单元存储第i个数据元素.
    *e = L.data[i-1];
    
    return OK;
}

//1.4 顺序表删除
/*
 1. 初始条件：顺序线性表L已存在，位置合法1≤i≤ListLength(L)
 2. 元素移动，后面的元素都要向前移
 操作结果: 删除L的第i个数据元素,L的长度减1
 */
Status ListDelete(Sqlist *L,int i){
    //线性表为空
    if(L->length == 0) return ERROR;
    
    //i值不合法判断
    if((i<1) || (i>L->length)) return ERROR;
    
    for(int j = i; j < L->length;j++){
        //被删除元素之后的元素向前移动
        L->data[j-1] = L->data[j];
    }
    //表长度-1;
    L->length --;
    
    return OK;
}

//1.5 清空顺序表
/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(Sqlist *L)
{
    L->length=0;
    return OK;
}

//1.6 判断顺序表清空
/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(Sqlist L)
{
    if(L.length==0)
        return TRUE;
    else
        return FALSE;
}

//1.7 获取顺序表长度ListEmpty元素个数 */
int ListLength(Sqlist L)
{
    return L.length;
}

//1.8 顺序输出List
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status TraverseList(Sqlist L)
{
    int i;
    for(i=0;i<L.length;i++)
        printf("%d\n",L.data[i]);
    printf("\n");
    return OK;
}

//1.9 顺序表查找元素并返回位置
/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(Sqlist L,ElemType e)
{
    int i;
    if (L.length==0) return 0;
    
    for(i=0;i<L.length;i++)
    {
        if (L.data[i]==e)
            break;
    }
  
    if(i>=L.length) return 0;
    return i+1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, Data Structure!\n");
    
    Sqlist L;
    Sqlist Lb;
    ElemType e;
    Status iStatus;
    
    //1.1 顺序表初始化
    iStatus = InitList(&L);
    printf("初始化L后: L.Length = %d\n", L.length);
    
    //1.2 顺序表数据插入
    for(int j=1; j <= 5;j++){
        iStatus = ListInsert(&L, 1, j);
    }
    printf("插入数据L长度: %d\n",L.length);
    
    //1.3 顺序表取值
    GetElem(L, 5, &e);
    printf("顺序表L第5个元素的值为:%d\n",e);
    
    //1.4 顺序表删除第2个元素
    ListDelete(&L, 2);
    printf("顺序表删除第%d元素,长度为%d\n",2,L.length);
    
    //1.5 清空顺序表
    iStatus = ClearList(&L);
    printf("清空后,L.length = %d\n",L.length);
    
    //1.6 判断List是否为空
    iStatus=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",iStatus);
    
    //1.8 TraverseList
    for(int j=1; j <= 5;j++){
        iStatus = ListInsert(&L, 1, j);
    }
    TraverseList(L);
    
    
    return 0;
}
