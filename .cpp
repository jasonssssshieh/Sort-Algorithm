//
//  main.cpp
//  HeapSort
//
//  Created by Zijian Xie on 2016/10/8.
//  Copyright © 2016年 Zijian Xie. All rights reserved.
// Heap Sort
/* http://wuchong.me/blog/2014/02/09/algorithm-sort-summary/
 七、堆排序 HeapSort
 介绍：
 
 堆排序在 top K 问题中使用比较频繁。堆排序是采用二叉堆的数据结构来实现的，虽然实质上还是一维数组。二叉堆是一个近似完全二叉树 。
 
 二叉堆具有以下性质：
 
 父节点的键值总是大于或等于（小于或等于）任何一个子节点的键值。
 每个节点的左右子树都是一个二叉堆（都是最大堆或最小堆）。
 步骤：
 
 构造最大堆（Build_Max_Heap）：若数组下标范围为0~n，考虑到单独一个元素是大根堆，则从下标n/2开始的元素均为大根堆。于是只要从n/2-1开始，向前依次构造大根堆，这样就能保证，构造到某个节点时，它的左右子树都已经是大根堆。
 
 堆排序（HeapSort）：由于堆是用数组模拟的。得到一个大根堆后，数组内部并不是有序的。因此需要将堆化数组有序化。思想是移除根节点，并做最大堆调整的递归运算。第一次将heap[0]与heap[n-1]交换，再对heap[0...n-2]做最大堆调整。第二次将heap[0]与heap[n-2]交换，再对heap[0...n-3]做最大堆调整。重复该操作直至heap[0]和heap[1]交换。由于每次都是将最大的数并入到后面的有序区间，故操作完后整个数组就是有序的了。
 
 最大堆调整（Max_Heapify）：该方法是提供给上述两个过程调用的。目的是将堆的末端子节点作调整，使得子节点永远小于父节点 。
 
 
 */
#include <iostream>
#include <vector>
using namespace std;

//inline int parent(int i){return (i-1)/2;}
//inline int leftchild(int i){return (i*2) + 1;}
//inline int rightchild(int i){return (i*2) + 2;}

void max_heapify(vector<int>& nums, int start, int end, int n){
    // end 不能忘记，因为这个就是用来控制调整范围的，每次相当于把最大的元素放在最后，然后去调整前面的。
    //用以维护heap的性质
    //check以i为父节点的这棵子树是否满足堆序性
    int root = start;
    int left = root * 2 + 1;
    //int right = left + 1;
    
    while(left <= end){
        if(left < end && left + 1 < end && nums[left + 1] > nums[left]){
            //这里不能用left < n !!! debug了好久！
            left++;
        }
        if(left < end && nums[root] > nums[left]){
            return;
        }
        else{
            swap(nums[root],nums[left]);
            root = left;
            left = root * 2 + 1;
            //做了swap，那么其他的根节点也需要做相应的调整，自上而下调整，floyd建堆法
            //不要从下往上->这样是考虑其深度了，应该用高度更合适！因为堆顶的元素更少！
        }
    }
}

void heap_sort(vector<int>& nums){
    int n = (int)nums.size();
    //construct_max_heap
    //先保证最底层的，也就是所有叶节点所在的那heap都已经有序
    for(int k = (int)(n/2) - 1; k >= 0; k--){
        max_heapify(nums, k, n - 1, n);
    }
    for(int i = n - 1; i > 0; i--){
        //每次取出最大元，取出堆顶的元素
        //并调整复原
        swap(nums[0], nums[i]);
        max_heapify(nums, 0, i-1, n);//自上而下调整！
    }
}
