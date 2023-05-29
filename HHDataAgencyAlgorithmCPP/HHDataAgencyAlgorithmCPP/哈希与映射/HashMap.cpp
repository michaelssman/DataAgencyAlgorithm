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

template<class Key, class Value>
class HashMap //哈希映射 用的多 因为快
{
public:
    //构造函数 里面设置一个初始的大小
    HashMap(int size = 101) : arr(size)
    {
        currentSize = 0;
    }
    
    //放数据
    void Put(const Key & k, const Value & v)
    {
        int pos = myhash(k);//得到下标
        arr[pos] = DataEntry(k,v);//放到数组里
        ++currentSize;
    }
    
    //找数据  根据key找value
    Value Get(const Key & k)
    {
        int pos = myhash(k);//先计算哈希 得到下标
        if (arr[pos].key == k) {//根据下标位置找数据
            return arr[pos].value;
        } else {
            return Value();//没找到 返回一个Value空值
        }
    }
    //哈希函数
    unsigned hash(const Key & k) const
    {
        unsigned int hashVal = 0;//开始的时候哈希值设为0
        const char *keyp = reinterpret_cast<const char *>(&k);//把关键字转型 Bill Mary等转型为字符
        //对里面的每一个字符 例Bill它的四个字符，每个字符做循环里面的算法 每一个字符都做运算 最后得出来一个数。有很多中方法计算哈希值 这只是一种常见的
        for (size_t i = 0; i < sizeof(Key); i++) {
            hashVal = 37 * hashVal + keyp[i];
        }
        return hashVal;
    }
    //上面计算的哈希值特别大。如果要使用上面的哈希值做下标 那么数组就要特别大，但是数组又没用那么大，还要对上面的哈希值变成很小的 和数组容量相一致的值。
    //需要再使用下面的计算
    int myhash(const Key & k) const
    {
        //首先利用上面的函数计算出来的非常大的哈希
        unsigned hashVal = hash(k);
        //然后把它变小 取余
        hashVal %= arr.size();
        //得到比较小的哈希
        return hashVal;
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
void testHashMap()
{

    //二叉树（红黑树）映射
    //保存每个学生的成绩
    map<string, int> m;//m是二叉树映射
    m["Bill"] = 98;
    m["Tom"] = 67;
    m["Mary"] = 100;
    
    //...继续保存，保存了很多，100万个

    cout << m["Tom"] << endl;
    
    //我的哈希映射
    HashMap<string, int> myHMap;
    //查看哈希值
    cout << myHMap.hash("Bill") << endl;
    cout << myHMap.myhash("Bill") << endl;

    myHMap.Put("Bill", 999);
    myHMap.Put("Tom", 888);
    myHMap.Put("Mary", 777);
    cout << myHMap.Get("Tom") << endl;
    
}


