//
//  QueueLiTest.cpp
//  CPPDemo00
//
//  Created by Michael on 2020/11/23.
//  Copyright © 2020 Michael. All rights reserved.
//

#include "QueueLiTest.hpp"
#include "QueueLi.hpp"
#include <iostream>

using namespace std;

void QueueLiTest()
{
    Queue<int> myQ;
    myQ.enqueue(10);
    myQ.enqueue(20);
    myQ.enqueue(30);

    cout << myQ.getFront() << endl;
    myQ.dequeue();
    cout << myQ.getFront() << endl;

    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            myQ.enqueue(i);
        }
        while (!myQ.isEmpty()) {
            cout << myQ.dequeue() << endl;
        }
    }
}
