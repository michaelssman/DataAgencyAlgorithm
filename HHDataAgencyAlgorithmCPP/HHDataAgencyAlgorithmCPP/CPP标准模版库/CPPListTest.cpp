//
//  CPPListTest.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/24.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "CPPListTest.hpp"
#include <iostream>
#include <list>

using namespace std;

void PrintListContents(const list<int>& listInput);

//insert
void listTest0()
{
    
    //list也是模板类
    list<int> a;//a就是双向链表
    list<int> b;
    
    //显示链表中的数据不能使用下标，因为不是数组，数组才可以用下标
    //链表只能使用迭代器
    std::list<int>::iterator iter;//迭代器类型


    b.push_back(100);
    b.push_back(200);
    b.push_back(300);
    b.push_back(400);
    b.push_back(500);
    
    PrintListContents(b);
    cout << endl;
    
    a.push_front(4);//在前面增加数据
    a.push_front(3);
    a.push_front(2);
    a.push_front(1);//每次都是从头插入，新插入的都在最前面
    a.push_back(5);//往链表后端插入
    
    iter = a.begin();//迭代器指向位置
    ++iter;//变成第二个位置
    a.insert(iter, 10);//在第二个位置插入10
    ++iter;        //改变位置
    a.insert(iter, 4, 20);//插入4个20
    //中间插入数据
    //用迭代器指定位置
    a.insert(a.begin(), 10);//在begin头插
    a.insert(a.end(), 4, 20);//在后端插入4个20

    //b里面的数据全部插入到a里面
    a.insert(a.begin(), b.begin(), b.end());//b插入到a的前面
    a.insert(a.end(), b.begin(), b.end());//b插入到a的后面：
    //插入到中间
    ++iter;
    a.insert(iter, b.begin(), b.end());
    a.insert(iter, ++b.begin(), --b.end());
    
    /*
    //显示链表中的数据，不能使用下标，只能使用迭代器。
    //显示链表中的数据不能使用下标，因为不是数组，数组才可以用下标
    //链表只能使用迭代器
    std::list<int>::iterator iter;//迭代器类型
    
    //通过a.begin()得到迭代器
    for (iter = a.begin(); iter != a.end(); ++iter) {
        cout << *iter << endl;//迭代器是指针
    }
    */
}

//delete
void listTest01()
{
    std::list<int> a;
    a.push_front(4);
    a.push_front(3);
    
    list<int>::iterator iElementValueTwo;
    
    iElementValueTwo = a.insert(a.begin(), 2);//insert返回一个迭代器 迭代器指向这个数据2
    a.push_front(1);
    a.push_front(0);

    PrintListContents(a);
    cout << endl;
    
    //把指向的2删除
    a.erase(iElementValueTwo);
    
    PrintListContents(a);
}

//显示list中的数据
void PrintListContents(const list<int>& listInput)
{
    cout << endl;
    cout << "{";
    //常迭代器
    std::list<int>::const_iterator iter;
    //通过a.begin()得到迭代器
    for (iter = listInput.begin(); iter != listInput.end(); ++iter) {
        cout << *iter << " ";//迭代器是指针
    }
    cout << "}";
}
