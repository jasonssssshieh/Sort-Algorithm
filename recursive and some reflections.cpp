//
//  main.cpp
//  Heap Sort _ Review and Thoughts
//
//  Created by Zijian Xie on 2016/11/18.
//  Copyright © 2016年 Jason Xie. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/*
 父节点的键值总是大于或等于（小于或等于）任何一个子节点的键值。
 每个节点的左右子树都是一个二叉堆（都是最大堆或最小堆）。
 
 对于一个heap而言，无非就是用vector去保持一个完全二叉树的结构，这里一定钥匙完全二叉树，也就是高度差>=0.
 对于每一个parent node，其value一定是大于它的两个子节点。
 i的两个子节点：left: 2i + 1, right: 2i+2;
 内部节点（即不包含最后最底层的叶节点）：0-> floor(i/2)-1;
 其实就类似于heap这个class继承了vector + binarytree这两个类
 insert操作：在vector最末尾插入这个元素，也就是在tree的后面加入，然后上虑交换违反了堆序性的地方，时间复杂度O(logn)
 getMax操作：也就是返回root节点，即index = 0 of vector 时间复杂度O(1)
 deleteMax操作：那么此时我们弹出root元素，这个空缺的位置由末尾的元素来顶替，这样减少了vector里面的时间开销，然后不断下虑，交换违反了堆序性的地方。时间复杂度O(logn)
 construct a heap / heaptification: 构建堆，最直观的方法就是每一次我都把节点插入到vector最末尾，采用insert操作，然后不断上滤，那么这个地方的操作复杂度是O(nlogn)，那还不如我们直接sort全排来得舒服。所以这样的暴力方法肯定不行。原因呢？是因为这种直观的方法是属于自上而下的上滤操作，我们从第一个节点开始一直上滤到最后一个节点，这里的复杂度的来源是每个节点的深度，而越到后面，节点深度越深，同时，节点数目也增加，所以复杂度就会非常高。自上而下，从左往右。
 
因此，我们在这里采用floyd建堆法：也就是自下而上的下滤方法。自下而上，从右往左。 我们用节点的高度来作为指标，这样高度越高的节点也就越少，高度越低的节点越多，相对而言就降低了复杂度。对于最后一层的叶节点，因为没有子节点，我们就默认为已经是满足了heap的要求，我们这里只需要考虑内部节点，也就是从floor(i/2)-1 往前来判断，即delete max & merge的操作，对于 某个i节点，我们去判现在已经有了两个heap的顶节点，判断这三个是否满足堆序性，不满足，那就交换，这样i节点可能被交换至左右的一个子树，那么对于这棵子树，我们再进行下滤，直至满足堆序性。然后往前i-1，判断这个节点，再进行merge，这样复杂度的来源就是每个节点的高度，整体复杂度就降低为O(n)
 
 heap_sort就是先构造一个heap，然后每次取出最顶端的元素和末端的元素交换，然后in-place exchange，然后再用floyd建堆，即更新。直至全部结束。
 
 */

class Heap{
private:
    vector<int> nums;
    vector<int> _nums;
    int n;
public:
    Heap(vector<int>& nums){
        this->nums = nums;
        this->_nums = nums;
        this->n = (int)nums.size();
    }
    void recover(){
        nums = _nums;
        n = (int)nums.size();
    }
    
    int leftchild(int i){
        return i*2 + 1;
    }
    int rightchild(int i){
        return i*2 + 2;
    }
    
    void down(int i, int start, int end){//下滤操作
        if(i > (end - start)/2 - 1) return;
        int L = i*2 + 1;
        int R = i*2 + 2;
        if(R < end && nums[R] > nums[L]){
            if(nums[R] > nums[i]){
                swap(nums[R], nums[i]);
                down(R, start, end);
            }
        }else if(nums[L] > nums[i]){
            swap(nums[L], nums[i]);
            down(L, start, end);
        }
        return;
    }
    
    void construct_heap(int start, int end){
        for(int i = (end - start)/2 - 1; i >= start; --i){
            down(i, start, end);
        }
    }
    void heap_sort(){
        construct_heap(0, n);
        for(int i = n - 1; i >= 0; --i){
            swap(nums[0],nums[i]);
            construct_heap(0, i);
        }
    }
    int getMax(){
        construct_heap(0, n);
        cout<<"getMax: "<<nums[0]<<endl;
        return nums[0];
    }
    void delMax(){
        construct_heap(0, n);
        swap(nums[0], nums[n-1]);
        nums.pop_back();
        n--;
        down(0, 0, n);
        cout<<"delMax completed."<<endl;
    }
    void print(){
        for(int i = 0; i < n; ++i){
            cout<<nums[i]<<" ";
        }
        cout<<endl;
    }
};

int main(int argc, const char * argv[]) {
    vector<int> nums = {9,2,4,5,2,3,5,6,-1,2,33,9,0,4,2,2,-5,4,1,3,23,4,57,8,94,10};
    Heap* test = new Heap(nums);
    //这里稍微注意一下， 最开始自己写的结果，因为没有在getMax里面调用construct——heap，在调用完sort之后，导致getMax其实是最小的那个数，因为你sort是把最大的数放在了最后面，construct_heap是把最大的数放在index = 0，这里需要注意一下区别。
    test->getMax();
    test->print();
    
    test->delMax();
    
    test->heap_sort();
    test->print();
    
    test->recover();
    test->heap_sort();
    
    test->print();
    return 0;
}
/*
getMax: 94
94 57 10 6 33 9 5 5 4 23 4 9 4 4 2 2 -5 -1 1 3 2 2 2 8 3 0 
delMax completed.
-5 -1 0 1 2 2 2 2 2 3 3 4 4 4 4 5 5 6 8 9 9 10 23 33 57 
-5 -1 0 1 2 2 2 2 2 3 3 4 4 4 4 5 5 6 8 9 9 10 23 33 57 94 
Program ended with exit code: 0
*/
