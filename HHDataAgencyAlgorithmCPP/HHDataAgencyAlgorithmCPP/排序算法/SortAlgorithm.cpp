//
//  SortAlgorithm.cpp
//  HHDataAgencyAlgorithmCPP
//
//  Created by Michael on 2022/10/16.
//

#include "SortAlgorithm.hpp"

using namespace std;

template<class T>
void printList(T *a, int n) {
    for (int i = 0; i < 11; ++i) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

void BubbleSort(int list[], int n)
{
    /**
     需要两个循环
     最后剩一个数据的时候，就不需要再循环了。
     例：10个数 需要循环9遍，i < 9  从0到8
     */
    for (int i = 0; i < n - 1; i++) {
        // 里面的扫描 会越来越短，所以会越来越快
        // 10个数 第一遍 扫9次 j从0到8
        for (int j = 0; j < n - i - 1; j++) {
            if (list[j] > list[j + 1]) {
                std::swap(list[j], list[j + 1]);
            }
        }
        
//        //打印每次循环结果
//        for (int k = 0; k < n; k++) {
//            std::cout << list[k] << " ";
//        }
//        std::cout << std::endl;

    }
}

/// 冒泡法优化，如果已经排好序了，减少排序次数
void BubbleSortBetter(int list[], int n)
{
    /**
     需要两个循环
     最后剩一个数据的时候，就不需要再循环了。
     例：10个数 需要循环9遍，i < 9  从0到8
     */
    bool sortted = false;
    for (int i = 0; (i < n - 1) && (sortted == false); i++) {
        sortted = true;//默认已经排序完毕
        // 里面的扫描 会越来越短，所以会越来越快
        // 10个数 第一遍 扫9次 j从0到8
        for (int j = 0; j < n - i - 1; j++) {
            if (list[j] > list[j + 1]) {
                std::swap(list[j], list[j + 1]);
                sortted = false;//只要发生交换则排序未完成，还需要再排序
            }
        }
        
//        //打印每次循环结果
//        for (int k = 0; k < n; k++) {
//            std::cout << list[k] << " ";
//        }
//        std::cout << std::endl;

    }
}

void testBubbleSort()
{
    int a[] = {2,4,6,8,0,1,3,5,7,9};
    BubbleSortBetter(a, 10);
    for (int k = 0; k < 10; k++) {
        std::cout << a[k] << " ";
    }
    std::cout << std::endl;
}


#pragma mark - 插入排序
template<class T>
void InsertionSort(T *a, int n)//a可以是int，可以是float，可以是double 0(n*n)
{
    int in, out;
    //开始时out=0这个人已经出去了
    for (out = 1; out < n; ++out) {
        T temp = a[out];
        in = out;
        while (in > 0 && a[in - 1] >= temp) {
            a[in] = a[in - 1];
            --in;
            //打印每次循环结果
            for (int k = 0; k < n; k++) {
                std::cout << a[k] << " ";
            }
            std::cout << std::endl;
        }
        a[in] = temp;
        
        //打印每次循环结果
        for (int k = 0; k < n; k++) {
            std::cout << a[k] << " ";
        }
        std::cout << std::endl;
    }
}

void testInsertionSort()
{
    double x[] = {2.2, 4.5, 6.6, 8, 0, 1, 3, 5, 7, 9};
    InsertionSort(x, 10);
//    for (int i = 0; i < 10; i++) {
//        std::cout << x[i] << std::endl;
//    }
}

#pragma mark - 归并排序
template<class T>
/// 两个有序数组合并
/// @param initList 原数组
/// @param mergedList 结果数组
/// @param l 第一部分开始下标
/// @param m 第二部分开始下标
/// @param n 总下标
void Merge(T *initList, T *mergedList, const int l, const int m, const int n)
{
    int i1, i2, iResult;
    for (i1 = l, i2 = m + 1, iResult = l; i1 <= m && i2 <= n; iResult++) {
        if (initList[i1] <= initList[i2])
        {
            mergedList[iResult] = initList[i1];
            i1++;
        }
        else
        {
            mergedList[iResult] = initList[i2];
            i2++;
        }
    }
    //把剩下的一次拷进去
    std::copy(initList + i1, initList + m + l, mergedList + iResult);
    std::copy(initList + i2, initList + n + l, mergedList + iResult);
}

template<class T>

/// <#Description#>
/// @param initList <#initList description#>
/// @param resultList <#resultList description#>
/// @param n 总个数
/// @param s <#s description#>
void MergePass(T *initList, T *resultList, const int n, const int s)
{
    int i;
    for (i = 1; i <= n-2*s+1; i += 2 * s) {
        Merge(initList, resultList, i, i+s-1, i+2*s-1);
    }
    if ((i+s-1) < n) {
        Merge(initList, resultList, i, i+s-1, n);
    } else {
        //剩下的直接复制下来
        std::copy(initList+i, initList+n+1, resultList+i);
    }
}

template<class T>
void MergeSort(T *a, const int n)
{
    T *tempList = new int[n+1];//tempList[0]不用
    for (int l = 1; l < n; l*=2) {
        MergePass(a, tempList, n, l);
        l *= 2;
        MergePass(tempList, a, n, l);
    }
    delete [] tempList;
}

void testMergeSort()
{
    //a[0]不用
//    int a[] = {0, 23, 47, 81, 95, 7, 14, 39, 55, 62, 74};
//    int b[11] = {0};
//    Merge(a, b, 1, 4, 10);
    
//    int m[] = {0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
//    int n[11] = {0};
//    MergePass(m, n, 10, 1);
//    for (int i = 0; i < 11; i++) {
//        std::cout << n[i] << " ";
//    }
//    std::cout << std::endl;
//
//    MergePass(n, m, 10, 2);
//    for (int i = 1; i < 11; i++) {
//        std::cout << m[i] << " ";
//    }
//    std::cout << std::endl;
//
//    MergePass(m, n, 10, 4);
//    for (int i = 1; i < 11; i++) {
//        std::cout << n[i] << " ";
//    }
//    std::cout << std::endl;
//
//    MergePass(n, m, 10, 8);
//    for (int i = 0; i < 11; i++) {
//        std::cout << m[i] << " ";
//    }
//    std::cout << std::endl;

    //上面都是中间结果的测试
    //下面开始测试MergeSort

    int x[] = {0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
    MergeSort(x, 10); //最终
    for (int i = 0; i < 11; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;
}

#pragma mark - 快速排序
template<class T>
void QuickSort(T *a, const int left, const int right)
{
    if (left < right) {
        //选枢轴 进行划分
        int i = left;
        int j = right + 1;//为什么要加1
        int pivot = a[left];
        
        //划分算法
        do {
            do i++; while(a[i] < pivot);
            do j--; while(a[j] > pivot);//多加一个数，这个条件 简单一些
            if (i < j) {
                swap(a[i], a[j]);
            }
        } while (i < j);
        swap(a[left], a[j]);
        
        for (int k = 0; k < 7; k++) {
            std::cout << a[k] << ", ";
        }
        std::cout << std::endl;
        std::cout << left << ", " << right << std::endl;
        
        //递归
        QuickSort(a, left, j - 1);
        QuickSort(a, j + 1, right);
    }
}

void testQuickSort()
{
    int a[] = {421,240,135,532,305,430,124};
    QuickSort(a, 0, 6);
//    for (int k = 0; k < 7; k++) {
//        std::cout << a[k] << "";
//        std::cout << std::endl;
//    }
}
