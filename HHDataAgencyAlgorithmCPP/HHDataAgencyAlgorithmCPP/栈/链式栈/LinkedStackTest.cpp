//
//  LinkedStackTest.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/23.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "LinkedStackTest.hpp"
#include "LinkedStack.hpp"
#include <iostream>

using namespace std;

void LinkedStackTest()
{
    LinkedStack<int> s;
    s.Push(10);
    cout << s.Top() << endl;
    s.Push(20);
    cout << s.Top() << endl;
    s.Push(30);
    cout << s.Top() << endl;

    s.Pop();
    cout << s.Top() << endl;

}
