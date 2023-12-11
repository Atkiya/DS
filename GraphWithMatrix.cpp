#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
class Graph{
public:
    int vertices;
    int adjMatrix[100][100];
    Graph(int v){
        vertices=v;
        for(int i=0;i<vertices;i++)
            for(int j=0;j<vertices;j++)
                adjMatrix[i][j]=0;
    }
    void addVertex(){
        if(vertices<1000)vertices++;
    }
    void addEdge(int a,int b){
        if(a<vertices&&b<vertices)adjMatrix[a][b]=1;
    }
    void deleteEdge(int a,int b){
        if(a<vertices&&b<vertices)adjMatrix[a][b]=0;
    }
    void deleteVertex(int v){
        if(v<0||v>=vertices)return;
        for(int i=v;i<vertices-1;i++)
            for(int j=0;j<vertices;j++)
                adjMatrix[i][j]=adjMatrix[i+1][j];

        for(int i=0;i<vertices;i++)
            for(int j=v;j<vertices-1;j++)
                adjMatrix[i][j]=adjMatrix[i][j+1];

        vertices--;
    }
    int FindDegree(int v){
        int d=0;
        for(int i=0;i<vertices;i++){
            if(adjMatrix[v][i]==1)d++;
        }
        return d;
    }
    int degreeOfGraph(){
        int mx=0;
        for(int i=0;i<vertices;i++){
            int d=0;
            for(int j=0;j<vertices;j++){
                if(adjMatrix[i][j]==1)d++;
            }
            if(d>mx)mx=d;
        }
        return mx;
    }
    bool findpath(int s,int e,int vis[],vector<int>&path){
        vis[s]=1;
        path.push_back(s);
        if(s==e)return true;
        for(int i=0;i<vertices;i++){
            if(adjMatrix[s][i]==1&&vis[i]==0){
                if(findpath(i,e,vis,path))return true;
            }
        }
        path.pop_back();
        return false;
    }
    void printPath(int s,int e){
        int vis[vertices]={0};
        vector<int>path;
        if(findpath(s,e,vis,path)){
            cout<<"Path from "<<s<<" to "<<e<<" : ";
            for(int x:path)cout<<x<<' ';
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
            for(int i=0;i<vertices;i++){
                if(adjMatrix[s][i]==1&&vis[i]==0){
                    getAllPaths(i,e,vis,path);
                }
            }
        }
        path.pop_back();
        vis[s]=0;
    }
    void dfsReccursive(int n,int vis[]){
        if(n>=vertices)return;
        cout<<n<<' ';
        vis[n]=1;
        for(int i=0;i<vertices;i++){
            if(adjMatrix[n][i]==1&&vis[i]==0){
                dfsReccursive(i,vis);
            }
        }
    }
    void dfsIterative(int n){
        int vis[vertices]={0};
        stack<int>s;
        cout<<"DFS from "<<n<<" : ";
        s.push(n);
        while(!s.empty()){
            int t=s.top();
            s.pop();
            if(vis[t]==0){
                cout<<t<<' ';
                vis[t]=1;
            }
            for(int i=0;i<vertices;i++){
                if(adjMatrix[t][i]==1&&vis[i]==0){
                    s.push(i);
                }
            }
        }
    }
    void bfs(int s){
        int vis[vertices]={0};
        queue<int>q;
        cout<<"BFS from "<<s<<" : ";
        q.push(s);
        while(!q.empty()){
            int f=q.front();
            cout<<f<<' ';
            q.pop();
            for(int i=0;i<vertices;i++){
                if(adjMatrix[f][i]==1&&vis[i]==0){
                    q.push(i);
                    vis[i]=1;
                }
            }
        }
        cout<<'\n';
    }
    void findparent(int n){
        cout<<"Parents of "<<n<<" : ";
        for(int i=0;i<vertices;i++){
            if(adjMatrix[i][n]==1)cout<<i<<' ';
        }
    }
    void findchildren(int n){
        cout<<"Children of "<<n<<" : ";
        for(int i=0;i<vertices;i++){
            if(adjMatrix[n][i]==1)cout<<i<<' ';
        }
    }
    void print(){
        cout<<"Adjacency Matrix: \n";
        for(int i=0;i<vertices;i++){
            for(int j=0;j<vertices;j++){
                cout<<adjMatrix[i][j]<<' ';
            }
            cout<<'\n';
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
    cout<<"Degree of vertex 0 : "<<g.FindDegree(0)<<'\n';
    cout<<'\n';
    cout<<"Degree of Graph : "<<g.degreeOfGraph()<<'\n';
    g.printPath(0,4);
    cout<<'\n';
    cout<<"All possible paths from 0 to 4:\n";
    g.printAllPaths(0,4);
    cout<<'\n';
    int vis[g.vertices]={0};
    g.dfsReccursive(0,vis);
    cout<<'\n';
    g.dfsIterative(0);
    cout<<'\n';
    g.bfs(0);
    cout<<'\n';
    g.findparent(4);
    cout<<'\n';
    g.findchildren(0);
    cout<<'\n';
    return 0;
}
