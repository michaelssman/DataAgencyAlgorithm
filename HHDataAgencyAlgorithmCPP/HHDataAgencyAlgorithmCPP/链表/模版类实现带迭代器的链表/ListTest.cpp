//
//  ListTest.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/18.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "ListTest.hpp"
#include <list>//C++ STL种的链表
#include "List.hpp"//自己做的链表
#include <iostream>

using namespace std;
//标准C++ STL中的链表和迭代器
void cppListTest()
{
    //标准C++ STL中的链表和迭代器
    //可以往链表的前面增加数据，也可以往链表的后面增加数据
    list<int> listIntegers;
    listIntegers.push_front(5);//在链表前面插入数据
    listIntegers.push_front(15);
    listIntegers.push_front(25);
    listIntegers.push_front(35);
    
    //想要看链表中的数据 使用迭代器
    list<int>::iterator i = listIntegers.begin();//迭代器 返回第一个数据
    //迭代器是一个指针
    cout << *i << "->";
    while (i!=listIntegers.end()) {
        cout << *i << "->";
        ++i;//下一个元素
    }
    cout << endl;
}

//自己写的链表 和 迭代器
void listTest()
{
    List<int> intList;
    intList.Insert(5);
    intList.Insert(15);
    intList.Insert(25);
    intList.Insert(35);
    
    //迭代器
    ListIterator<int> li(intList);
    if (li.NotNull()) {//先检查链表是不是空的
        cout << *li.First();
        while (li.NextNotNull()) {
            cout << "->" << *li.Next();
        }
        cout << endl;
    }
    
    
    intList.Show();
    intList.Invert();
    intList.Show();
    
    intList.Delete(15);
    intList.Show();
    
    List<char> charList;
    charList.Insert('a');
    charList.Insert('b');
    charList.Insert('c');
    charList.Insert('d');
    charList.Invert();
    charList.Show();
    
    List<char> char2List;
    char2List.Insert('e');
    char2List.Insert('f');
    char2List.Invert();
    char2List.Show();
    
    charList.Concatenate(char2List);
    charList.Show();
}
