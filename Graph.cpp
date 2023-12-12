#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class SLLNode{
public:
    int data;
    SLLNode *next;

    SLLNode(int val){
        data=val;
        next=NULL;
    }
};

class DLLNode{
public:
    int data;
    DLLNode *next;
    SLLNode *sllpart;

    DLLNode(int val){
        data=val;
        next=NULL;
        sllpart=NULL;
    }
};

class Graph{
public:
    int vertices;
    DLLNode* head,*tail;
    Graph(int v){
        vertices=v;
        head=tail=NULL;
        for(int i=0;i<vertices;i++){
            DLLNode* n=new DLLNode(i);
            if(head==NULL){
                head=tail=n;
            }
            else{
                tail->next=n;
                tail=n;
            }
        }
    }
    void addVertex(){
        DLLNode* n=new DLLNode(vertices);
        tail->next=n;
        tail=n;
        vertices++;
    }
    void addEdge(int a,int b){
        DLLNode* t=head;
        SLLNode* n=new SLLNode(b);
        while(t!=NULL){
            if(t->data==a){
                SLLNode* tt=t->sllpart;
                if(tt==NULL)t->sllpart=n;
                else{
                    while(tt->next!=NULL)tt=tt->next;
                    tt->next=n;
                }
                break;
            }
            t=t->next;
        }
    }
    void deleteVertex(int v){
        DLLNode* t=head,*prev;
        while(t!=NULL){
            if(t->data==v){
                prev->next=t->next;
                delete t;
                break;
            }
            prev=t;
            t=t->next;
        }
        DLLNode* tt=head;
        while(tt!=NULL){
            SLLNode* s=tt->sllpart,*prevs=NULL;
            while(s!=NULL){
                if(s->data==v){
                    if(prevs==NULL){
                        if(s->next==NULL)tt->sllpart=NULL;
                        else{
                            tt->sllpart=s->next;
                            delete s;
                        }
                    }
                    else{
                        prevs->next=s->next;
                        delete s;
                    }
                    break;
                }
                prevs=s;
                s=s->next;
            }
            tt=tt->next;
        }
    }
    void deleteEdge(int a,int b){
        DLLNode* t=head;
        while(t!=NULL){
            if(t->data==a){
                SLLNode* s=t->sllpart,*prev=NULL;
                while(s!=NULL){
                    if(s->data==b){
                        if(prev==NULL){
                            if(s->next==NULL)t->sllpart=NULL;
                            else{
                                t->sllpart=s->next;
                                delete s;
                            }
                        }
                        else{
                            prev->next=s->next;
                            delete s;
                        }
                        break;
                    }
                    prev=s;
                    s=s->next;
                }
            }
            t=t->next;
        }
    }
    int FindDegree(int v){
        int d=0;
        DLLNode* t=head;
        while(t!=NULL){
            if(t->data==v){
                SLLNode* s=t->sllpart;
                while(s!=NULL){
                    s=s->next;
                    d++;
                }
                break;
            }
            t=t->next;
        }
        return d;
    }
    int degreeOfGraph(){
        int mx=0;
        DLLNode* t=head;
        while(t!=NULL){
            int d=0;
            SLLNode* s=t->sllpart;
            while(s!=NULL){
                s=s->next;
                d++;
            }
            if(d>mx)mx=d;
            t=t->next;
        }
        return mx;
    }
    bool FindPath(int s,int e,int vis[],vector<int>&path){
        vis[s]=1;
        path.push_back(s);
        if(s==e)return true;
        DLLNode* t=head;
        while(t!=NULL){
            if(t->data==s){
                SLLNode* tt=t->sllpart;
                while(tt!=NULL){
                    if(vis[tt->data]==0){
                        if(FindPath(tt->data,e,vis,path))return true;
                    }
                    tt=tt->next;
                }
            }
            else t=t->next;
        }
        path.pop_back();
        return false;
    }
    void printPath(int s,int e){
        int vis[vertices]={0};
        vector<int>path;
        if(FindPath(s,e,vis,path)){
            cout<<"Path from "<<s<<" to "<<e<<" : ";
            for(auto x:path)cout<<x<<' ';
            cout<<'\n';
        }
        else cout<<"Path doesn't exist\n";
    }
    void printAllPaths(int s,int e){
        int vis[vertices]={0};
        vector<int>path;
        getAllPaths(s,e,vis,path);
    }
    void getAllPaths(int s,int e,int vis[],vector<int>&path){
        vis[s]=1;
        path.push_back(s);
        if(s==e){
            for(auto x:path)cout<<x<<' ';
            cout<<'\n';
        }
        else{
            DLLNode* t=head;
            while(t!=NULL){
                if(t->data==s){
                    SLLNode* tt=t->sllpart;
                    while(tt!=NULL){
                        if(vis[tt->data]==0){
                            getAllPaths(tt->data,e,vis,path);
                        }
                        tt=tt->next;
                    }
                }
                t=t->next;
            }
        }
        path.pop_back();
        vis[s]=0;
    }
    void dfs(int s){
        int vis[vertices]={0};
        stack<int>st;
        cout<<"DFS from "<<s<<" : ";
        st.push(s);
        while(!st.empty()){
            int t=st.top();
            st.pop();
            if(vis[t]==0){
                cout<<t<<' ';
                vis[t]=1;
            }
            DLLNode* t1=head;
            while(t1!=NULL){
                if(t1->data==t){
                    SLLNode* tt=t1->sllpart;
                    while(tt!=NULL){
                        if(vis[tt->data]==0){
                            st.push(tt->data);
                        }
                        tt=tt->next;
                    }
                }
                t1=t1->next;
            }
        }
        cout<<'\n';
    }
    void bfs(int n){
        queue<int>q;
        int vis[vertices]={0};
        cout<<"BFS from "<<n<<" : ";
        q.push(n);
        while(!q.empty()){
            int f=q.front();
            q.pop();
            if(vis[f]==0){
                cout<<f<<' ';
                vis[f]=1;
            }
            DLLNode* t1=head;
            while(t1!=NULL){
                if(t1->data==f){
                    SLLNode* tt=t1->sllpart;
                    while(tt!=NULL){
                        if(vis[tt->data]==0){
                            q.push(tt->data);
                        }
                        tt=tt->next;
                    }
                }
                t1=t1->next;
            }
        }
        cout<<'\n';
    }
    void findParent(int n){
        cout<<"Parents of "<<n<<" : ";
        DLLNode* t=head;
        while(t!=NULL){
            SLLNode* s=t->sllpart;
            while(s!=NULL){
                if(s->data==n){
                    cout<<t->data<<' ';
                    break;
                }
                s=s->next;
            }
            t=t->next;
        }
        cout<<'\n';
    }
    void findChildren(int n){
        cout<<"Children of "<<n<<" : ";
        DLLNode* t=head;
        while(t!=NULL){
            if(t->data==n){
                SLLNode* s=t->sllpart;
                while(s!=NULL){
                    cout<<s->data<<' ';
                    s=s->next;
                }
                break;
            }
            t=t->next;
        }
        cout<<'\n';
    }
    void print(){
        DLLNode* t=head;
        while(t!=NULL){
            cout<<t->data<<':';
            SLLNode* tt=t->sllpart;
            while(tt!=NULL){
                cout<<' '<<tt->data;
                tt=tt->next;
            }
            cout<<'\n';
            t=t->next;
        }
    }
};

int main(){
    Graph g(5);
    g.addEdge(0,1);
    g.addEdge(1,0);
    g.addEdge(0,2);
    g.addEdge(2,0);
    g.addEdge(1,2);
    g.addEdge(2,1);
    g.addEdge(1,3);
    g.addEdge(3,1);
    g.addEdge(1,4);
    g.addEdge(4,1);
    g.addEdge(2,3);
    g.addEdge(3,2);
    g.addEdge(3,4);
    g.addEdge(4,3);
    g.print();
    cout<<"After deleting vertex 1 :\n";
    g.deleteVertex(1);
    g.print();
    cout<<"After removing edge from 4 to 3\n";
    g.deleteEdge(4,3);
    g.print();
    cout<<"Degree of vertex 2 : "<<g.FindDegree(2)<<'\n';
    cout<<"Degree of Graph : "<<g.degreeOfGraph()<<'\n';
    g.printPath(0,4);
    cout<<"All Paths from 0 to 4 : \n";
    g.printAllPaths(0,4);
    g.dfs(0);
    g.bfs(0);
    g.findParent(2);
    g.findChildren(3);
    return 0;
}
