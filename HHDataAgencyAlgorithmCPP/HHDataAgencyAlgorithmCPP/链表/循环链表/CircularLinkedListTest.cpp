//
//  CircularLinkedListTest.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/20.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "CircularLinkedListTest.hpp"
#include <iostream>
#include "CircularLinkedList.hpp"

using namespace std;

void CircularLinkedListTest()
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
    
    //证明是循环链表
    //测试一下循环
    ListIterator<int> iter(intList);
    cout << *iter.First() << endl;
    cout << *iter.Next() << endl;
    cout << *iter.Next() << endl;
    cout << *iter.Next() << endl;
    cout << *iter.Next() << endl;
    cout << *iter.Next() << endl;
    cout << *iter.Next() << endl;
}
