//
//  MaxHeap.cpp
//  CPPDemo00
//
//  Created by Michael on 2022/5/1.
//  Copyright © 2022 Michael. All rights reserved.
//

#include "MaxHeap.hpp"
#include <iostream>

using namespace std;

//测试
void testMaxHeap()
{
    MaxHeap<int> h(100);//最大是100个
    cout << h.IsEmpty() << endl;
    
    h.Push(20);
    h.Push(30);
    h.Push(15);
    cout << h.Top() << endl;//最大的 根

    h.Pop();
    cout << h.Top() << endl;//最大的 根

}

//测试堆排序
void testMaxHeapSort()
{
    MaxHeap<int> h(100);//最大是100个
    
    int arr[] = {62,3,90,27,33,8,12,9,43,66};
    
    for (int i = 0; i < 10; i++) {
        h.Push(arr[i]);
    }
    
    for (int i = 0; i < 10; i++) {
        arr[i] = h.Top();
        h.Pop();
    }
    
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << endl;
    }

}
