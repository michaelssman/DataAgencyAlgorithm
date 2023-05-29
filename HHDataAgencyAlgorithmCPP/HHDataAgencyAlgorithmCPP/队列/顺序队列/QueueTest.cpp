//
//  QueueTest.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/17.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "QueueTest.hpp"
#include <iostream>
#include "Queue.hpp"

using namespace std;
void queueTest()
{
    Queue<char> q(5);
    q.Push('A');
    q.Push('B');
    q.Push('C');
    cout << q.Front() << ", " << q.Rear() << endl;
    q.Push('D');
    q.Push('E');
    q.Push('F');
    cout << q.Front() << ", " << q.Rear() << endl;
    q.Push('G');
    cout << q.Front() << ", " << q.Rear() << endl;
}

