//
//  main.cpp
//  Sort Algorithm
//
//  Created by Zijian Xie on 2016/11/22.
//  Copyright © 2016年 Jason Xie. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

template <typename T>
class Sort {
    vector<T> nums;
    vector<T> _nums;
    int n;
    
public:
    Sort(vector<T> nums){
        this->nums = nums;
        this->_nums = nums;
        n = (int) nums.size();
    }
    vector<T> getNums(){return nums;}
    vector<T> get_Nums(){return _nums;}
    int getN(){return n;}
    void clear(){
        nums = _nums;
    }
    void SWAP(T& a, T& b){
        T tmp = a;
        a = b;
        b = tmp;
        return;
    }
    
    void print(){
        for(int i = 0; i < n; ++i){
            cout<<nums[i]<<" ";
        }
        cout<<endl;
        return;
    }
    //起泡排序
    void bubble_sort(){
        int tmp = 0;
        while(true){
            for(int i = 1; i < n; ++i){
                if(nums[i] < nums[i-1]){
                    swap(nums[i],nums[i-1]);
                    tmp = 1;
                }
            }
            if(!tmp){break;}
            else{tmp = 0;}
        }
        print();
        return;
    }
    //插入排序
    //比如6，3，5，6，7，9，3，2，3，1
    /*基本思想就是对于每一个平凡的情况：单个的数已经是排序好了的，然后从length = 2开始，目前来了一个数：3，在前面已经排序好的序列中给3找一个最合适的位置，也就是6前面，因此交换。现在有序序列为3，6. 下一个数是5，5最合适的位置是3后面，因此把5插入其中。以此类推.
     在算法中因为每次插入的空间开销太大，所以我们采取逐项比较swap的方式，如果发现逆序了，就交换，如果没有，那么就直接break；进入下一次循环
     */
    void insert_sort(){
        for(int i = 0; i < n; ++i){
            for(int j = i; j > 0; --j){
                if(nums[j-1] > nums[j]){
                    SWAP(nums[j-1], nums[j]);
                }else{break;}
            }
        }
        print();
    }
    
    //选择排序 Selection Sort: 每次都从乱序数组中找到最大（最小）值，放到当前乱序数组头部，最终使数组有序。
    void selection_sort(){
        for(int i = 0; i < n; ++i){
            int k = i;
            for(int j = i+1; j < n; ++j){
                if(nums[k] > nums[j]){k = j;}
            }
            SWAP(nums[k], nums[i]);
        }
        print();
    }
    
    
    //归并排序
    void merge(vector<T>& res, int start, int m, int end){
        int s1 = start, s2 = m+1, k = start;
        while(s1 <= m && s2 <= end){
            if(nums[s1] < nums[s2]){
                res[k++] = nums[s1++];
            }else{
                res[k++] = nums[s2++];
            }
        }
        
        while(s1 <= m){
            res[k++] = nums[s1++];
        }
        while(s2 <= end){
            res[k++] = nums[s2++];
        }
        
        for(int i = start; i <= end; ++i){
            nums[i] = res[i];
        }
    }
    void merge_sort(int start, int end){
        if(start >= end) return;
        vector<T> res(n);
        int m = (end+start)/2;
        merge_sort(start, m);
        merge_sort(m+1, end);
        merge(res, start, m, end);
    }
    
    //快速排序
    /*
     就是每次寻找一个pivot，然后对于pivot前面的数，最大的也不超过pivot所代表的数，对于pivot后面的数，最小的也不小于pivot所代表的数，对于平凡的情况，递归基就是单独的元素情况，已经有序。
     这个与merge sort的不同在于，merge的分段复杂度为O(1)，也就是每次只需要分开就行了，每次都能分成尽可能相等的两部分，所以是一个稳定的算法，复杂度为O(nlogn)，同时，分段后的两端是无序，并且两边的最大最小值和分开的中点没有必然的大小关系，这点是与quick sort不同的地方，也因此，merge sort的在merge的时候复杂度就会来到O(n)，但此时对于quick sort而言，他在merge的时候，只需要左边merge，右边merge，然后加上中间的pivot即可，因此，他的这个地方的复杂度为O(1)，但quick sort由于在分段的时候必须保证左右两边的大小关系，因此分段的结果不确定，所以不稳定，在最坏情况下会达到O(n^2)总体复杂度，平均而言是O(nlogn)
     */
    void quick_sort(int start, int end){//end will be included
        if(n < 2 || start >= end) return;
        int pivot = start;
        int left = start + 1;
        int right = end;
        while(left < right){
            while(right > left && nums[right] > nums[pivot]){right--;}
            while(left < right && nums[left] <= nums[pivot]){left++;}
            swap(nums[left], nums[right]);
        }
        SWAP(nums[pivot],nums[left]);
        quick_sort(start, left-1);
        quick_sort(left+1, end);
    }
    
    //Radix排序：桶排序的升级版本，因为桶排序中我们利用了hash table来进行排序，但是如果当数字的范围特别大的时候，就非常耗时间，这里用Radix排序，是根据最大的数的位数来k来进行比较，时间复杂度为O(nk), 空间复杂度O(nk)、我们用10位数字，所以0 - 9 共10个桶，然后开始第一位比较（最低位），依次进入对应的桶，按照最低位的数值以此入桶，然后按照0-9号桶，以此从最底端的数次开始出桶，然后形成一组新的序列，然后扫描第二位。。。一直到最后一位，即可。
    
    T getKthDigit(T num, int k){
        return (int)(num/(pow(10.0, k-1.0))) % 10;
    }
    void radix_sort(){
        T Max = nums[0];
        for(auto num : nums){
            Max = max(Max, num);
        }
        int k = 0;
        while(Max>>k){k++;}
        
        vector<queue<int>> bucket(10);
        for(int digit = 0; digit <= k; ++digit){
            for(int i = 0; i < n; ++i){
                bucket[getKthDigit(nums[i], digit)].push(nums[i]);
            }
            int k = 0;
            for(int i = 1; i < 10; ++i){
                while(!bucket[i].empty()){
                    nums[k++] = bucket[i].front();
                    bucket[i].pop();
                }
            }
        }
        print();
    }
};

int main(int argc, const char * argv[]) {
    vector<int> nums = {6,3,5,6,7,9,3,2,3,1};
    Sort<int> test(nums);
    test.quick_sort(0, (int)nums.size()-1);
    cout<<"Quick Sort: ";
    test.print();
    test.clear();
    
    cout<<"Bubble Sort: ";
    test.bubble_sort();
    test.clear();
    
    cout<<"Insert Sort: ";
    test.insert_sort();
    test.clear();
    
    cout<<"Selection Sort: ";
    test.selection_sort();
    test.clear();
    
    cout<<"Merge Sort: ";
    test.merge_sort(0,(int)nums.size()-1);
    test.print();
    test.clear();
    
    cout<<"Radix Sort: ";
    test.radix_sort();
    test.clear();
    
    return 0;
}
/*
Quick Sort: 1 2 3 3 3 5 6 6 7 9 
Bubble Sort: 1 2 3 3 3 5 6 6 7 9 
Insert Sort: 1 2 3 3 3 5 6 6 7 9 
Selection Sort: 1 2 3 3 3 5 6 6 7 9 
Merge Sort: 1 2 3 3 3 5 6 6 7 9 
Radix Sort: 1 2 3 3 3 5 6 6 7 9 
Program ended with exit code: 0
*/
