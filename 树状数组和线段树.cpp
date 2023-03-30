#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
/*
����������
��ʼ��������СΪn����������nums��������ַ�����
sumRange(i,j);:�������Ԫ�غ�
update(i,val);��nums[i]��ֵ�޸�Ϊval
*/
//��״����
//bits[i]��ʾ��f[1],i������ͣ�f[i]=i-lowbits(i)+1
//lowbits ��ʾi�Ķ��������λ��1�������    
//���Կ�����iΪ��2��4��8��bits[i]ָ��������[1,i]�ĺ�
//��iȡ6��12,��bits[i]����[5,6],[9,12]����ĺ�
//��iȡ3��5��7��bits[i]����[i,i]��ֵ

//3+lowbits(3)=4,4+lowbits(4)=8
//6+lowbits(6)=8,

//lowbits(x)������һ����̬�仯�Ĳ���������������ϵ����
class NumArray{
    private:
    vector<int>bits;//������״����bits
    vector<int>data;
    int lowbits(int x){
        return x&(-x);//���ݲ�������
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
           bits=vector<int>(nums.size()+1,0);//��ʼ��bits��С��
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

//�߶�����
//��Ϊ1�Ľ������Ƕ�Ϊ2������+1,�ܽ����Ϊ������
//��ڵ�Ϊż����ţ��ҽڵ�Ϊ������ţ�����Ҷ�ӽڵ���һ�㣬�������Ͻ���
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
    //�ҵ�l��r��ΪҶ�ӽڵ���������˵�������ֵ�Ϳ��ԣ�ϣ��l������������ڵ㣬r�����������ҽڵ�
    for(;l<=r;l>>1,r>>1){
        if(l&1)res+=st[l++];//���l���ҽڵ㣨��������������֮��ĵ㣬���ϣ�����l++ʹ��l��Ϊ��������ڵ�
        if(!(r&1))res+=st[r--];//���r����ڵ㣨ż������������֮��ĵ㣬���ϣ�����r--ʹ��r��Ϊ���������ҽڵ�
        //����l==r,�����������һ���жϼӵ�res��
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
            st[i>>1]=st[i]+st[i^1];//ͨ�����������Դ���õ��ң����ҵõ�������
            i>>=1;
        }
    }

};





