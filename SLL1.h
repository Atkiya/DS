#include<iostream>
using namespace std;
class Node{
public:
    int data;
    Node* next;
    Node(int d){
        data=d;
        next=NULL;
    }
};
Node* merge(Node* f,Node* s){
    Node* h,*h1=f,*h2=s;
    if(h1->data<=h2->data){
        h=h1;
        h1=h1->next;
    }
    else{
        h=h2;
        h2=h2->next;
    }
    Node* H=h;
    while(h1!=NULL&&h2!=NULL){
        if(h1->data<=h2->data){
            H->next=h1;
            H=h1;
            h1=h1->next;
        }
        else{
            H->next=h2;
            H=h2;
            h2=h2->next;
        }
    }
    if(h1!=NULL)H->next=h1;
    if(h2!=NULL)H->next=h2;
    return h;
}
Node* merge_sort(Node* head){
    if(head==NULL||head->next==NULL)return head;
    Node* s=head,*f=head->next;
    while(f!=NULL&&f->next!=NULL){
        s=s->next;
        f=f->next->next;
    }
    Node* s2=s->next;
    s->next=NULL;
    Node* fh=merge_sort(head),*sh=merge_sort(s2);
    return merge(fh,sh);
}
Node* sortList(Node* head) {
    return merge_sort(head);
}
class SLL{
public:
    Node* head;
    SLL(){
        head=NULL;
    }
    void add(int d){
        Node* n=new Node(d);
        if(head==NULL)head=n;
        else{
            Node* t=head;
            while(t->next!=NULL){
                t=t->next;
            }
            t->next=n;
        }
    }
    void addAtBegin(int d){
        Node* n=new Node(d);
        Node* t=head;
        head=n;
        head->next=t;
    }
    void addanypos(int d,int p){
        if(p==0)addAtBegin(d);
        else{
            Node* t=head;
            int len=0;
            while(t!=NULL){
                t=t->next;
                len++;
            }
            if(p==len)add(d);
            else if(p>len)cout<<"Invalid Input\n";
            else{
                Node* n=new Node(d);
                Node* t=head,*t1=NULL;
                for(int i=1;i<p;i++){
                    t1=t;
                    t=t->next;
                }
                t1->next=n;
                n->next=t;
            }
        }
    }
    bool contains(int d){
        bool f=false;
        Node* t=head;
        while(t!=NULL){
            if(t->data==d){
                f=true;
                break;
            }
            t=t->next;
        }
        return f;
    }
    int size(){
        Node* t=head;
        int l=0;
        while(t!=NULL){
            l++;
            t=t->next;
        }
        return l;
    }
    bool isEmpty(){
        if(head==NULL)return true;
        return false;
    }
    int getdataatpos(int p){
        if(p==0||size()<p){
            return -1;
        }
        Node* t=head;
        for(int i=1;i<p;i++)t=t->next;
        return t->data;
    }
    int indexOf(int d){
        Node* t=head;
        int l=0,f=0;
        while(t!=NULL){
            l++;
            if(t->data==d){
                f=1;
                break;
            }
            t=t->next;
        }
        if(f)return l;
        return -1;
    }
    void removeFirst(){
        Node* t=head;
        head=head->next;
        delete t;
    }
    void removeLast(){
        Node* t=head,*t1=NULL;
        while(t->next!=NULL){
            t1=t;
            t=t->next;
        }
        t1->next=NULL;
        delete t;
    }
    void remove(int p){
        Node* t=head,*t1=NULL;
        for(int i=1;i<p;i++){
            t1=t;
            t=t->next;
        }
        t1->next=t->next;
        delete t;
    }
    void reverse(){
        Node* t=head,*t1=NULL,*t2=NULL;
        while(t!=NULL){
            t1=t->next;
            t->next=t2;
            t2=t;
            t=t1;
        }
        head=t2;
    }
    void sort(){
        Node* n=sortList(head);
    }
    void display(){
        Node* t=head;
        while(t!=NULL){
            cout<<t->data<<' ';
            t=t->next;
        }
        cout<<'\n';
    }
};
