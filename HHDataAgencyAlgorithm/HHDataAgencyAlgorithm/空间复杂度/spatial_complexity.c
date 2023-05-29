//
//  main.c
//  HHDataAgencyAlgorithm
//
//  Created by Michael on 2022/4/21.
//

/*
 算法的空间复杂度通过计算算法所需的存储空间实现,算法空间复杂度的计算公式
 记做: S(n) = n(f(n)),其中,n为问题的规模,f(n)为语句关于n所占存储空间的函数
 程序空间计算因素:
 1. 寄存本身的指令
 2. 常数
 3. 变量
 4. 输入
 5. 对数据进行操作的辅助空间
 
 在考量算法的空间复杂度,主要考虑算法执行时所需要的辅助空间.
 空间复杂度计算:

 问题: 数组逆序,将一维数组a中的n个数逆序存放在原数组中.
 */

#include <stdio.h>

int kongjianfuzafu(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
   
    int n = 5;
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    
    //算法实现(1)
    int temp;//只用了一个临时变量，因为是常树，所以是O(1)
    for(int i = 0; i < n/2 ; i++){
        temp = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }

    for(int i = 0;i < 10;i++)
    {
        printf("%d\n",a[i]);
    }
    
    //算法实现(2)。O(n)
    int b[10] = {0};
    for(int i = 0; i < n;i++){
        b[i] = a[n-i-1];
    }
    for(int i = 0; i < n; i++){
        a[i] = b[i];
    }
    for(int i = 0;i < 10;i++)
    {
        printf("%d\n",a[i]);
        
    }
    
    return 0;
}
