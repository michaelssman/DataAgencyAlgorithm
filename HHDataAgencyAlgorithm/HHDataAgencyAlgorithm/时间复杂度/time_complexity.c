//
//  main.c
//  HHDataAgencyAlgorithm
//
//  Created by Michael on 2022/4/21.
//

#include <stdio.h>
/*大O表示法
 1. 用常数1取代运行时间中所有常数 3->1 O(1)
 2. 在修改运行次数函数中,只保留最高阶项 n^3+2n^2+5 -> O(n^3)
 3. 如果在最高阶存在且不等于1,则去除这个项目相乘的常数 2n^3 -> n^3
 */

/*
 时间复杂度术语:
 1. 常数阶
 2. 线性阶
 3. 平方阶
 4. 对数阶（logn）
 5. 立方阶
 6. nlog阶
 7. 指数阶(不考虑) O(2^n)或者O(n!) 除非是非常小的n,否则会造成噩梦般的时间消耗. 这是一种不切实际的算法时间复杂度. 一般不考虑!
 O(1) < O(log n) < O(n) < O(nlog n) < O(n^2) < O(n^3) < O(2^n) < O(n!) < O(n^n)//后面三个都是指数阶
 */

#pragma mark - /* 1. 常数阶时间复杂度计算 O(1) */
//1+1+1 = 3 O(1)
void testSum1(int n){
    int sum = 0;                //执行1次
    sum = (1+n)*n/2;            //执行1次
    printf("testSum1:%d\n",sum);//执行1次
}

//1+1+1+1+1+1+1 = 7 O(1)
void testSum2(int n){
    int sum = 0;                //执行1次
    sum = (1+n)*n/2;            //执行1次
    sum = (1+n)*n/2;            //执行1次
    sum = (1+n)*n/2;            //执行1次
    sum = (1+n)*n/2;            //执行1次
    sum = (1+n)*n/2;            //执行1次
    printf("testSum2:%d\n",sum);//执行1次
    
}
//x=x+1; 执行1次
void add(int x){
    x = x+1;
}


#pragma mark - /*2.线性阶时间复杂度*/
//x=x+1; 执行n次 O(n)
void add2(int x,int n){
    for (int i = 0; i < n; i++) {
        x = x+1;
    }
}

//1+(n+1)+n+1 = 3+2n -> O(n)
void testSum3(int n){
    int i,sum = 0;               //执行1次
    for (i = 1; i <= n; i++) {   //执行n+1次
        sum += i;                //执行n次
    }
    printf("testSum3:%d\n",sum);  //执行1次
}

#pragma mark - /*3.对数阶*/
/*2的x次方等于n x = log2n  ->O(logn)*/
//log2n log4n log4n都是用logn表示，省略了底数
void testA(int n){
    int count = 1;         //执行1次
    //n = 10
    while (count < n) {
        count = count * 2;//2的x次方等于n就会结束
    }
    
}


#pragma mark - /*4.平方阶*/
//x=x+1; 执行n*n次 ->O(n^2)
void add3(int x,int n){
    for (int i = 0; i< n; i++) {//i执行1次 j执行n次。所以共执行nXn次
        for (int j = 0; j < n ; j++) {
            x=x+1;
        }
    }
}

//n+(n-1)+(n-2)+...+1 = n(n-1)/2 = n^2/2 + n/2 = O(n^2)
//sn = n(a1+an)/2
void testSum4(int n){
    int sum = 0;                        //执行1次
    for(int i = 0; i < n;i++)           //执行n次
        for (int j = i; j < n; j++) {   //i=1 j执行n次，i=1 j执行n-1次，i=2 j执行n-2次
            sum += j;
        }
    printf("textSum4:%d",sum);
    
}

//1+(n+1)+n(n+1)+n^2+n^2 = 2+3n^2+2n -> O(n^2)
void testSum5(int n){
    int i,j,x=0,sum = 0;           //执行1次
    for (i = 1; i <= n; i++) {     //执行n+1次
        for (j = 1; j <= n; j++) { //执行n(n+1)
            x++;                   //执行n*n次
            sum = sum + x;         //执行n*n次
        }
    }
    printf("testSum5:%d\n",sum);
}


#pragma mark - /*5.立方阶*/
void testB(int n){
    int sum = 1;                         //执行1次
    for (int i = 0; i < n; i++) {        //执行n次
        for (int j = 0 ; j < n; j++) {   //执行n*n次
            for (int k = 0; k < n; k++) {//执行n*n*n次
                sum = sum * 2;          //执行n*n*n次
            }
        }
    }
}

int shijianfuzadu(int argc, const char * argv[]) {
    
    testSum1(100);
    testSum2(100);
    testSum3(100);
    
    return 0;
}
