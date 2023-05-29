//
//  MyStackTest.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/17.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "MyStackTest.hpp"
#include <iostream>
#include "MyStack.hpp"

using namespace std;

void myStackTest()
{
    //MyStack是模版类。可以保存各种数据。不止是int string还可以是自己写的class
    MyStack<int> st(200);
    st.Push(99);
    st.Push(22);
    st.Push(18);
    st.Push(67);
    cout << st.Top() << endl;//67
    st.Pop();
    cout << st.Top() << endl;//18
}
