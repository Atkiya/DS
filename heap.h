#include<iostream>
using namespace std;
class Heap{
public:
    int *a,size;
    int n;
    Heap(int N){
       size=N;
       n=0;
       a=new int[size];
    }
    void heapifyUp(int i){
        int par=(i-1)/2;
        if(par>=0){
            if(a[i]>a[par]){
                int t=a[i];
                a[i]=a[par];
                a[par]=t;
                heapifyUp(par);
            }
        }
    }
    void insert(int key){
        n++;
        a[n-1]=key;
        heapifyUp(n-1);
    }
    void heapifyDown(int i){
        int lar=i;
        int l=2*i+1,r=2*i+2;
        if(l<n&&a[l]>a[lar])lar=l;
        if(r<n&&a[r]>a[lar])lar=r;
        if(lar!=i){
            int t=a[i];
            a[i]=a[lar];
            a[lar]=t;
            heapifyDown(lar);
        }
    }
    void heapifyDownforMin(int i){
        int lar=i;
        int l=2*i+1,r=2*i+2;
        if(l<n&&a[l]<a[lar])lar=l;
        if(r<n&&a[r]<a[lar])lar=r;
        if(lar!=i){
            int t=a[i];
            a[i]=a[lar];
            a[lar]=t;
            heapifyDownforMin(lar);
        }
    }
    void deleteRoot(){
        int last=a[n-1];
        a[0]=last;
        n--;
        heapifyDown(0);
    }
    int maxelement(){
        return a[0];
    }
    void MinHeapify(){
        for(int i=(n-2)/2;i>=0;i--)heapifyDownforMin(i);
    }
    void MaxHeapify(){
        for(int i=(n-2)/2;i>=0;i--)heapifyDown(i);
    }
    void print(){
        for(int i=0;i<n;i++)cout<<a[i]<<' ';
        cout<<'\n';
    }
};
