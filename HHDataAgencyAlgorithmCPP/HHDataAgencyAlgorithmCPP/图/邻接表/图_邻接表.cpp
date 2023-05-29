//
//  main.cpp
//  CPPDemo00
//
//  Created by Michael on 2019/10/31.
//  Copyright © 2019 Michael. All rights reserved.
//

#include <iostream>
#include <vector>//动态数组
#include <list>//C++ STL中的链表
#include <queue>

#include <set>
#include <map>//二叉树映射，不是哈希映射。
using namespace std;
#define SWAP(x,y,t) ((t) = (x),(x) = (y),(y) = (t))

//设计顶点类 保存各种数据
class Vertex
{
public:
    char Label;
    Vertex(char lab) {Label = lab; }
};

#pragma mark - 对输出运算符做重载 这样才可以输出顶点 cout<<v
ostream& operator<<(ostream& out, const Vertex& v)
{
    cout << v.Label;
    return out;
}

//图 类
template<class T>
class Graph
{
public:
    Graph(const int vertices) : n(vertices) //构造函数 参数传有多少个顶点 保存到变量n里
    {
        VertexList = new T*[n];//数组 用来保存n个顶点
        HeadNodes = new list<int>[n];//数组 里面有n个链表
        nVerts = 0;//开始的时候一个顶点都没有。个数是0。
    }
    ~Graph()//析构函数
    {
        //new数组对应的delete
        delete [] VertexList;
        delete [] HeadNodes;
    }
    //成员函数
    void addVertex(T* v);//给图增加一个顶点 类型是模版范型T
    void addEdge(int start, int end);//增加一条边 从一个顶点到另一个顶点的边 start和end用的是顶点的序号
    //两个调试函数
    void printVertice();//打印所有的顶点
    void printAdjList();//打印链接表
private:
    //两个数组
    T** VertexList;
    list<int>* HeadNodes;//链表
    int n;//顶点总数 最多有多少个顶点
    int nVerts;//当前顶点个数
};

#pragma mark - 成员函数
//增加一个顶点
template<class T>
void Graph<T>::addVertex(T* v)
{
    //顶点的数量++ 把顶点放到数组VertexList里
    VertexList[nVerts++] = v;
}
//增加一条边
template<class T>
void Graph<T>::addEdge(int start, int end)
{
    //把end的顶点加到数组下标start的链表里
    HeadNodes[start].push_back(end);
}

//打印所有顶点
template<class T>
void Graph<T>::printVertice()
{
    //循环顶点数组
    for (int i = 0; i < nVerts; i++) {
        cout << *VertexList[i] << " ";
    }
    cout << endl;
}

//打印邻接表
template<class T>
void Graph<T>::printAdjList()
{
    //循环数据
    for (int i = 0; i < nVerts; i++) {
        cout << i << "->";
        //循环链表 使用标准模版库的迭代器
        for (list<int>::iterator iter = HeadNodes[i].begin(); iter != HeadNodes[i].end(); ++iter) {
            cout << *iter << "->";
        }
        cout << "end" << endl;
    }
    //先输出i然后输出迭代器里的*iter。
}

//测试
void testP()
{
    //创建图
//    Graph<char> g(5);//有5个顶点 顶点类型是char 也可以是自定义的类型 因为是模版 所以可以是任何类型
    //把顶点加进去
//    char a = 'A';
//    char b = 'B';
//    char c = 'C';
//    char d = 'D';
//    char e = 'E';
    Graph<Vertex> g(5);
    Vertex a('A');
    Vertex b('B');
    Vertex c('C');
    Vertex d('D');
    Vertex e('E');
    
    g.addVertex(&a);//传地址&a
    g.addVertex(&b);//1
    g.addVertex(&c);//2
    g.addVertex(&d);//3
    g.addVertex(&e);//4
    
    g.printVertice();
    
    //添加边 addEdge用的是序号下标
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

    g.printAdjList();
}


