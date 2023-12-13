#include<iostream>
#include<vector>
#include<utility>
#include<queue>
using namespace std;
class Node{
public:
    Node* left,*right;
    int data;
    Node(int data){
        this->data=data;
        left=right=NULL;
    }
};
class BST{
public:
    int l;
    BST(){
        l=0;
    }
    Node* insert(Node* root,int d){
        if(root==NULL){
            Node* n=new Node(d);
            return n;
        }
        if(d<root->data)root->left=insert(root->left,d);
        else root->right=insert(root->right,d);
        return root;
    }
    Node* deleteNode(Node* root,int d){
        if(root==NULL)return root;
        if(d<root->data)root->left=deleteNode(root->left,d);
        else if(d>root->data)root->right=deleteNode(root->right,d);
        else{
            if(root->left==NULL){
                Node*temp=root;
                root=root->right;
                delete temp;
                return root;
            }
            else if(root->right==NULL){
                Node*temp=root;
                root=root->left;
                delete temp;
                return root;
            }
            Node*temp=findMin(root->right);
            root->data=temp->data;
            root->right=deleteNode(root->right,temp->data);
        }
        return root;
    }
    Node* search(Node * root,int d){
        if(root==NULL||root->data==d)return root;
        if(d<root->data)return search(root->left,d);
        else return search(root->right,d);
    }
    void PreOrderDFS(Node* root){
        if(root!=NULL){
            cout<<root->data<<' ';
            PreOrderDFS(root->left);
            PreOrderDFS(root->right);
        }
    }
    void InOrderDFS(Node* root){
        if(root!=NULL){
            InOrderDFS(root->left);
            cout<<root->data<<' ';
            InOrderDFS(root->right);
        }
    }
    void PostOrderDFS(Node* root){
        if(root!=NULL){
            PostOrderDFS(root->left);
            PostOrderDFS(root->right);
            cout<<root->data<<' ';
        }
    }
    Node *findMax(Node* root){
        if(root==NULL)return NULL;
        while(root->right!=NULL)root=root->right;
        return root;
    }
    Node *findMin(Node* root){
        if(root==NULL)return NULL;
        while(root->left!=NULL)root=root->left;
        return root;
    }
    int height(Node* root){
        int lh=-1,rh=-1;
        if(root!=NULL){
            lh=height(root->left)+1;
            rh=height(root->right)+1;
        }
        return max(lh,rh);
    }
    bool hasPath(Node* root,vector<int>&v,int x){
        if(root==NULL)return false;
        v.push_back(root->data);
        if(root->data==x)return true;
        if(hasPath(root->left,v,x)||hasPath(root->right,v,x))return true;
        v.pop_back();
        return false;
    }
    void printPath(Node *root,int src,int dst){
        vector<int>path1;
        vector<int>path2;
        bool l=hasPath(root,path1,src);
        bool r=hasPath(root,path2,dst);
        if(!l||!r){
            cout<<"No Path\n";
            return;
        }
        int intersection=-1;
        int i=0,j=0;
        while(i<path1.size()||j<path2.size()){
            if(i==j&&path1[i]==path2[j]){
                i++;
                j++;
            }
            else{
                intersection=j-1;
                break;
            }
        }
        for(int i=path1.size()-1;i>intersection;i--)cout<<path1[i]<<' ';
        for(int i=intersection;i<path2.size();i++)cout<<path2[i]<<' ';
    }
    int Nodes(Node* root){
        if(root==NULL)return 0;
        int c=0;
        if(root!=NULL)c++;
        c+=Nodes(root->left);
        c+=Nodes(root->right);
        return c;
    }
    ///BFS
    void levelOrder(Node * root) {
        if(!root)return;
        queue<Node*>q;
        q.push(root);
        while(!q.empty()){
            Node* n=q.front();
            q.pop();
            cout<<n->data<<' ';
            if(n->left)q.push(n->left);
            if(n->right)q.push(n->right);
        }
    }
    Node *lca(Node *root, int v1,int v2) {
        if(root==NULL)return root;
        if(v1<root->data&&v2<root->data)return lca(root->left,v1,v2);
        else if(v1>root->data&&v2>root->data)return lca(root->right,v1,v2);
        else return root;
    }
    int leaves(Node* root){
        if(root==NULL)return 0;
        int c=0;
        if(root->left==NULL&&root->right==NULL)c++;
        c+=leaves(root->left);
        c+=leaves(root->right);
        return c;
    }
    void printleaves(Node* root){
        if(root==NULL)return;
        if(root->left==NULL&&root->right==NULL)cout<<root->data<<' ';
        printleaves(root->left);
        printleaves(root->right);
    }
    int internal(Node* root){
        if(root==NULL)return 0;
        int c=0;
        if(root->left!=NULL||root->right!=NULL)c++;
        c+=internal(root->left);
        c+=internal(root->right);
        return c;
    }
    int oneChild(Node* root){
        if(root==NULL)return 0;
        int c=0;
        if((root->left==NULL&&root->right!=NULL)||(root->left!=NULL&&root->right==NULL))c++;
        c+=oneChild(root->left);
        c+=oneChild(root->right);
        return c;
    }
    void printonechild(Node* root){
        if(root==NULL)return;
        if((root->left==NULL&&root->right!=NULL)||(root->left!=NULL&&root->right==NULL))cout<<root->data<<' ';
        printonechild(root->left);
        printonechild(root->right);
    }
    int twoChild(Node* root){
        if(root==NULL)return 0;
        int c=0;
        if(root->left!=NULL&&root->right!=NULL)c++;
        c+=twoChild(root->left);
        c+=twoChild(root->right);
        return c;
    }
    void printtwochild(Node* root){
        if(root==NULL)return;
        if(root->left!=NULL&&root->right!=NULL)cout<<root->data<<' ';
        printtwochild(root->left);
        printtwochild(root->right);
    }
    Node* findParent(Node* root,Node* par,int d){
        if(root==NULL)return root;
        if(root->data==d)return par;
        else{
            if(d<root->data)return findParent(root->left,root,d);
            else return findParent(root->right,root,d);
        }
    }
    void findAnc(Node* root,int d){
        if(root==NULL||root->data==d)return;
        cout<<root->data<<' ';
        if(d<root->data)findAnc(root->left,d);
        else if(d>root->data)findAnc(root->right,d);
    }
    void findDesDfs(Node* root,int d){
        if(root!=NULL){
            findDesDfs(root->left,d);
            if(root->data!=d)cout<<root->data<<' ';
            findDesDfs(root->right,d);
        }
    }
    void findDes(Node* root,int d){
        if(root==NULL)return;
        findDesDfs(search(root,d),d);
    }
    Node* deleteLeaves(Node* root){
        if(root==NULL)return NULL;
        if(root->left==NULL&&root->right==NULL){
            delete root;
            return NULL;
        }
        root->left=deleteLeaves(root->left);
        root->right=deleteLeaves(root->right);
        return root;
    }
};
int main(){
    Node* root=NULL;
    BST b;
    root=b.insert(root,2);
    root=b.insert(root,3);
    root=b.insert(root,5);
    root=b.insert(root,7);
    root=b.insert(root,8);
    root=b.insert(root,6);
    root=b.insert(root,4);
    b.InOrderDFS(root);
    cout<<'\n';
    b.PreOrderDFS(root);
    cout<<'\n';
    b.PostOrderDFS(root);
    cout<<'\n';
    b.levelOrder(root);
    cout<<endl;
    Node* min=b.findMin(root);
    cout<<min->data<<'\n';
    Node* max=b.findMax(root);
    cout<<max->data<<'\n';
    Node* find=b.search(root,7);
    if(find!=NULL)cout<<"Found: "<<find->data<<'\n';
    else cout<<"Not Found\n";
    cout<<"Height: "<<b.height(root)<<'\n';
    cout<<"Path ";
    b.printPath(root,5,97);
    cout<<endl;
    cout<<"Total nodes: "<<b.Nodes(root)<<'\n';
    cout<<"Leaf Nodes "<<b.leaves(root)<<'\n';
    b.printleaves(root);
    cout<<endl;
    cout<<"Internal Nodes : "<<b.internal(root)<<endl;
    cout<<"Number of nodes with one child : "<<b.oneChild(root)<<'\n';
    b.printonechild(root);
    cout<<endl;
    cout<<"Nodes with two child : "<<b.twoChild(root)<<'\n';
    b.printtwochild(root);
    cout<<endl;
    cout<<"Parent of 7 : "<<b.findParent(root,NULL,7)->data<<endl;
    cout<<"Ancestors of 8 : ";
    b.findAnc(root,8);
    cout<<endl;
    cout<<"Descendents of 7 : ";
    b.findDes(root,7);
    cout<<endl;
    return 0;
}
