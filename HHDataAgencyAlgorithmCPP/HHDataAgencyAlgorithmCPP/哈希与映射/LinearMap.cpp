//
//  main.cpp
//  CPPDemo00
//
//  Created by Michael on 2019/10/31.
//  Copyright © 2019 Michael. All rights reserved.
//  线性映射（只是为了学习使用）

#include <iostream>
#include <vector>//动态数组
#include <list>//C++ STL中的链表
#include <queue>

#include <set>
#include <map>//二叉树映射，不是哈希映射。
using namespace std;
#define SWAP(x,y,t) ((t) = (x),(x) = (y),(y) = (t))

template<class Key, class Value>
class LinearMap //线性映射 没用的东西
{
public:
    //构造函数 里面设置一个初始的大小
    LinearMap(int size = 101) : arr(size)
    {
        currentSize = 0;
    }
    
    //放数据
    void Put(const Key & k, const Value & v)
    {
        arr[currentSize] = DataEntry(k,v);//数据都放在数组里 数组里数据是DataEntry 一对一对的
        ++currentSize;
    }
    
    //找数据  根据key找value
    Value Get(const Key & k)
    {
        //普通的线性查找 从数组里找出来
        for (size_t i = 0; i < currentSize; ++i) {
            if (arr[i].key == k) {
                return arr[i].value;
            }
        }
        return Value();//没找到 返回一个Value空值
    }
private:
    struct DataEntry {//struct也可以使用class
        Key key;
        Value value;
        //构造函数
        DataEntry(const Key & k = Key(), const Value & v = Value()) : key(k),value(v){}
    };
    std::vector<DataEntry> arr;//#include <vector>//动态数组 数组里保存的是一对一对的数据DataEntry
    int currentSize;//数组当前的大小
};

//测试
void testLinerMap()
{

    //二叉树（红黑树）映射
    //保存每个学生的成绩
    map<string, int> m;//m是二叉树映射
    m["Bill"] = 98;
    m["Tom"] = 67;
    m["Mary"] = 100;
    
    //...继续保存，保存了很多，100万个

    cout << m["Tom"] << endl;
    
    
    //一个没用的 仅学习的线性映射
    LinearMap<string, int> lm;
    lm.Put("Bill", 99);
    lm.Put("Tom", 88);
    lm.Put("Mary", 77);
    //继续put很多数据 100万个 线性查找 就需要查找50万次
    cout << "LinearMap:" << lm.Get("Tom") << endl;

}


