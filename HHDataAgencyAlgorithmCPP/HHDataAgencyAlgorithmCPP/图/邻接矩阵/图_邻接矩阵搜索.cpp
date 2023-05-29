//
//  图_邻接矩阵搜索.cpp
//  HHDataAgencyAlgorithmCPP
//
//  Created by Michael on 2022/6/25.
//  图_邻接矩阵搜索

#include "图_邻接矩阵搜索.hpp"
#include <iostream>
#include <vector>//动态数组
#include <list>//C++ STL中的链表
#include <queue>//C++ STL中的队列

#include <set>
#include <map>//二叉树映射，不是哈希映射。
#include <stack>//堆栈
using namespace std;
#define SWAP(x,y,t) ((t) = (x),(x) = (y),(y) = (t))

#pragma mark - 顶点 类 这个例子里面顶点只保存一个字符类型 只是简单学习。 以后可以做复杂的数据。
class Vertex
{
public:
    Vertex(char lab)
    {
        Label = lab;
        wasVisited = false;
    }
public:
    bool wasVisited;//bool变量，记录顶点有没有访问过
    char Label;
};

#define MAX_VERTS 20 //顶点最多的个数
#pragma mark - 图 类
class Graph
{
public:
    Graph();//构造函数
    ~Graph();//析构函数
    //成员函数
    void addVertex(char lab);//增加一个顶点
    void addEdge(int start, int end);//增加一条边 从一个顶点到另一个顶点的边
    void printMatrix();//打印矩阵
    void showVertex(int v);//显示某一个顶点 这个demo是显示字符char。辅助函数 DFS要用。
    void DFS();//深度优先搜索
    void BFS();//广度优先搜索
private:
    Vertex* vertexList[MAX_VERTS];//指针数组。存所有顶点。定义一个数组，做邻接矩阵。
    int nVerts;//顶点个数
    int adjMat[MAX_VERTS][MAX_VERTS];//定义一个矩阵 MAX_VERTS行MAX_VERTS列。
    //获取下标v的顶点邻接的下一个要访问的顶点  辅助函数 DFS要用。返回值是下一个邻接顶点的下标，没找到就返回-1.
    int getAdjUnvisitedVertex(int v);
};

//构造函数
Graph::Graph()
{
    nVerts = 0;//开始的时候顶点数为0
    for (int i = 0; i < MAX_VERTS; i++) {
        for (int j = 0; j < MAX_VERTS; j++) {
            adjMat[i][j] = 0;//二维数组都初始为0
        }
    }
}

//析构函数
Graph::~Graph()
{
    for (int i = 0; i < nVerts; i++) {
        delete vertexList[i];//因为每增加一个顶点都用了new创建了对象，所以需要delete。
    }
}

/// 深度优先搜索 使用C++做好的堆栈stack
void Graph::DFS()
{
    //定义一个堆栈 堆栈里面保存的是顶点的下标
    stack<int> gStack;
    //从第一个顶点开始 把第一个顶点设为true 显示第一个顶点
    vertexList[0]->wasVisited = true;
    showVertex(0);
    gStack.push(0);//把访问过的顶点压入堆栈，因为访问完了要返回 从堆栈里找到每一个顶点
    int v;
    while (gStack.size() > 0) {//当堆栈是空的时候，搜索就结束了
        v = getAdjUnvisitedVertex(gStack.top());//找相邻的没有访问过的下一个。一直找。找到的是下标。
        //没找到 最后一个顶点没有下一个 有可能没有下一个
        if (v == -1) {
            gStack.pop();//向回返回
        }
        //找到了
        else {
            vertexList[v]->wasVisited = true;
            showVertex(v);//把下一个显示出来
            gStack.push(v);//把下一个放入堆栈
        }
    }
    cout << endl;
    //最后把所有的顶点处理一下，因为深度优先搜索的时候把顶点都变成了true，访问完了要把顶点都变成false，这样以后可以再进行重复搜索。
    for (int j = 0; j < nVerts; j++) {
        vertexList[j]->wasVisited = false;
    }
}

//广度优先
void Graph::BFS()
{
    queue<int> qQueue;//队列里面保存的顶点的下标
    vertexList[0] -> wasVisited = true;
    showVertex(0);//把顶点显示出来
    qQueue.push(0);//访问过的每一个顶点都要放入队列
    int vert1, vert2;//定义两个变量
    //如果队列里面有顶点 不是空的 就一直循环
    while (qQueue.size() > 0) {
        vert1 = qQueue.front();
        qQueue.pop();
        vert2 = getAdjUnvisitedVertex(vert1);//和vert1相邻接的未访问过的顶点。可能有多个。所以需要下面循环 找到所有相邻接的顶点。
        while (vert2 != -1) {
            vertexList[vert2] -> wasVisited = true;
            showVertex(vert2);//把顶点显示出来
            qQueue.push(vert2);//访问过的每一个顶点都要放入队列，访问下一层的时候要用
            vert2 = getAdjUnvisitedVertex(vert1);//和vert1相邻接的未访问过的顶点。可能有多个。所以需要循环 找到所有相邻接的顶点。
        }
    }
    cout << endl;//加一个换行
    //最后把所有的顶点处理一下，访问完了要把顶点都变成false，这样以后可以再进行重复搜索。
    for (int j = 0; j < nVerts; j++) {
        vertexList[j]->wasVisited = false;
    }
}

#pragma mark - 获得邻接的下一个访问的顶点
//1. 是否是邻接的。
//2. 是否被访问过。
int Graph::getAdjUnvisitedVertex(int v)
{
    //循环 找是1并且没有访问过 已经访问过就不能重复搜索
    for (int j = 0; j < nVerts; j++) {
        if ((adjMat[v][j] == 1) && (vertexList[j]->wasVisited == false)) {
            return j;
        }
    }
    return -1;
}

//显示某一个顶点 下标是v
void Graph::showVertex(int v)
{
    cout << vertexList[v]->Label << " ";
}

#pragma mark - 成员函数
//增加一个顶点 把顶点放到数组里
void Graph::addVertex(char lab)
{
    //顶点的数量++，创建一个顶点放到数组里。
    vertexList[nVerts++] = new Vertex(lab);
}
//增加一条边
void Graph::addEdge(int start, int end)
{
    //邻接矩阵是对称的 所以要两个1
    adjMat[start][end] = 1;
    adjMat[end][start] = 1;
}
//把邻接矩阵打印出来
void Graph::printMatrix()
{
    //二维数组打印 打印用到的 nVerts个
    for (int i = 0; i < nVerts; i++) {
        for (int j = 0; j < nVerts; j++) {
            cout << adjMat[i][j] << " ";
        }
        cout << endl;
    }
}

//测试
void testGraphSource()
{
    //创建顶点
    Graph g;
    //把顶点加进去
    g.addVertex('A');//0
    g.addVertex('B');//1
    g.addVertex('C');//2
    g.addVertex('D');//3
    g.addVertex('E');//4
    //添加边 addEdge用的是下标
    g.addEdge(0, 1);//A-B
    g.addEdge(0, 3);//A-D
    g.addEdge(1, 0);//B-A
    g.addEdge(1, 4);//B-E
    g.addEdge(2, 4);//C-E
    g.addEdge(3, 0);//D-A
    g.addEdge(3, 4);//D-E
    g.addEdge(4, 1);//
    g.addEdge(4, 2);//
    g.addEdge(4, 3);//

    g.printMatrix();
    
    //深度优先
    g.DFS();
    //广度优先搜索的结果
    g.BFS();
}


