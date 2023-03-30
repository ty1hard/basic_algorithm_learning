#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
/*
问题描述：
初始化给定大小为n的整数数组nums，设计两种方法：
sumRange(i,j);:求闭区间元素和
update(i,val);将nums[i]的值修改为val
*/
//树状数组
//bits[i]表示【f[1],i】区间和，f[i]=i-lowbits(i)+1
//lowbits 表示i的二进制最低位的1代表的数    
//可以看到当i为如2，4，8等bits[i]指的是区间[1,i]的和
//当i取6，12,等bits[i]就是[5,6],[9,12]区间的和
//当i取3，5，7等bits[i]就是[i,i]的值

//3+lowbits(3)=4,4+lowbits(4)=8
//6+lowbits(6)=8,

//lowbits(x)，就是一个动态变化的步长，将各个数联系起来
class NumArray{
    private:
    vector<int>bits;//构造树状数组bits
    vector<int>data;
    int lowbits(int x){
        return x&(-x);//根据补码运算
    }
    int sum(int i){
        int s=0;
        while(i>0){
            int now_i=lowbits(i);
            s+=bits[now_i];
            i-=lowbits(i);
        }
        return s;
    }


    public:
        NumArray(vector<int> &nums){
           bits=vector<int>(nums.size()+1,0);//初始化bits大小；
           data=vector<int>(nums.size(),0);
           for(int i=0;i<nums.size();i++){
            update(i+1,nums[i]);
           }


            }
    void update(int i ,int val){
        int cha=val-data[i-1];
        data[i-1]=val;
        while(i<bits.size()){
            bits[i]+=cha;
            i+=lowbits(i);
        }
    }
    int sumRange(int l,int r){
        return sum(r+1)-sum(l);
    }

};

//线段树：
//度为1的结点个数是度为2结点个数+1,总结点数为奇数个
//左节点为偶数编号，右节点为奇数编号，所有叶子节点在一层，自下向上建树
class MidTree{
private:
    vector<int>st;
    int n;
    BuildTree(vector<int>&nums){

    if(n%2!=0)n+=1;
    // for(int i=1;i<=n;i++){
    //     st[n+i]=nums[i];
    // }
    // int k=2*n;
    // while(k>0){
    //     int k_=k/2;
    //     st[k_]+=st[k];
    //     k--;
    // }
    for(int i=n;i<2*n;i++)st[i]=nums[i-n];
    for(int i=n-1;i>0;i--)st[i]=st[i<<1]+st[(i<<1)|1];
}
public:
    MidTree(vector<int>&nums){
        n=nums.size();
        st=vector<int>(n*2,0);
        BuildTree(nums);
    }
    int sum_node(int i){

        i+=n;
        int di=0;
        if(i%2!=0)di=-st[i];       
        int j=n+1;
        while(j!=i){
            j>>1;
            i>>1;
        }
        return st[i]+di;

    }
    int sumRange(int l,int r){
        l+=n;
        r+=n;
        // return sum_node(r)-sum_node(l)+st[l];
    int res=0;
    //找到l和r作为叶子节点的左右两端的子树的值就可以，希望l是子树的最左节点，r是子树的最右节点
    for(;l<=r;l>>1,r>>1){
        if(l&1)res+=st[l++];//如果l是右节点（奇数），是子树之外的点，加上，并且l++使得l成为子树最左节点
        if(!(r&1))res+=st[r--];//如果r是左节点（偶数），是子树之外的点，加上，并且r--使得r成为子树的最右节点
        //最终l==r,都会进入其中一个判断加到res中
    }
    
    }
    void update(int i,int val){
        // i+=n;
        // int diff=val-st[i];
        // st[i]=val;
        // while(i>=0){
        //     st[i>>1]+=diff;
        //    i= i>>1;
        // }
        i+=n;
        st[i]=val;
        while(i>0){
            st[i>>1]=st[i]+st[i^1];//通过异或运算可以从左得到右，从右得到左数字
            i>>=1;
        }
    }

};





