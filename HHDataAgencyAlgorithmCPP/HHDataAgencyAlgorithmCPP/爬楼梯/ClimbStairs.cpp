//
//  ClimbStairs.cpp
//  HHDataAgencyAlgorithmCPP
//
//  Created by Michael on 2022/6/23.
//

#include "ClimbStairs.hpp"
#include <iostream>

using namespace std;

/**
 1.常见的一个简单写的爬楼梯问题为：一人要爬n个台阶，一步能爬1个台阶或者2个台阶，问：爬完n个台阶一共有多少种爬法？

 解析：这个人开始爬台阶时只可能有两种爬法：

 1）：爬1个台阶，剩下的n-1个有f(n-1)种爬法；

 2）：爬2个台阶，剩下的n-2个有f(n-2)中爬法；

 除了这两种爬法，没有其他的了，所以很明显f(n) = f(n-1) + f(n-2) 。很明显这是一个递归类问题。

 需要注意的是f(2) = f(1) + f(0), 很显然f(1)=1,f(2)=2，所以f(0) = 1，所以函数如下：
 */


int getMethodCount(int allsteps) {
    if (allsteps == 0){
        return 1;
    } else if (allsteps == 1){
        return 1;//爬一阶楼梯 1种方法
    } else if (allsteps == 2){
        return 2;//爬两阶楼梯 2种方法
    } else {
        //爬一阶楼梯 爬两阶楼梯
        return getMethodCount(allsteps - 1) + getMethodCount(allsteps - 2);
    }
}

void testClimbStairs() {
    cout << getMethodCount(0) << endl;
    cout << getMethodCount(1) << endl;
    cout << getMethodCount(2) << endl;
    cout << getMethodCount(10) << endl;
}
