#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define cy cout<<"YES\n"
#define cn cout<<"NO\n"
#define all(v) v.begin(),v.end()
#define vl vector<ll>
#define vi vector<int,int>
#define vp vector<pair<ll,ll>>
#define pb push_back
#define pf push_front
#define mp make_pair
#define ff first
#define ss second
#define MAX 200005
const ll MOD=1000000007;
/*ll prime[10000000]={0};
void seive(){
    for(ll i=2;i<10000000;i++){
        for(ll j=i*i;j<30;j+=i){
            prime[j-1]=1;
        }
    }
}*/
/*int result[1000] = {0};
int fact(int n) {
   if (n >= 0) {
      result[0] = 1;
      for (int i = 1; i <= n; ++i) {
         result[i] = i * result[i - 1];
      }
      return result[n];
   }
}*/
struct suff{
    int ind;
    int pos[2];
};
int cmp(struct suff a,struct suff b){
    return (a.pos[0]==b.pos[0])?(a.pos[1]<b.pos[1]?1:0):(a.pos[0]<b.pos[0]?1:0);
}
int *suffarr(char *t,int n){
    struct suff sf[n];
    for(int i=0;i<n;i++){
        sf[i].ind=i;
        sf[i].pos[0]=t[i]-'a';
        if((i+1)<n)sf[i].pos[1]=t[i+1]-'a';
        else sf[i].pos[1]=-1;
    }
    sort(sf,sf+n,cmp);
    int in[n];
    for(int j=4;j<2*n;j*=2){
        int pos=0;
        int pr=sf[0].pos[0];
        sf[0].pos[0]=pos;
        in[sf[0].ind]=0;
        for(int i=1;i<n;i++){
            if(sf[i].pos[0]==pr&&sf[i].pos[1]==sf[i-1].pos[1]){
                pr=sf[i].pos[0];
                sf[i].pos[0]=pos;
            }
            else{
                pr=sf[i].pos[0];
                sf[i].pos[0]=++pos;
            }
            in[sf[i].ind]=i;
        }
        for(int i=0;i<n;i++){
            int next_ind=sf[i].ind+j/2;
            if(next_ind<n)sf[i].pos[1]=sf[in[next_ind]].pos[0];
            else sf[i].pos[1]=-1;
        }
        sort(sf,sf+n,cmp);
    }
    int *sa=new int[n];
    for(int i=0;i<n;i++)sa[i]=sf[i].ind;
    return sa;
}
void p(int a[],int n){
    for(int i=0;i<n;i++)cout<<a[i]<<' ';
}
/*
void find(char *p,char *t,int *sa,int n,int m){
    int lo=0,hi=n-1;
    while(lo<=hi){
        int mid=(lo+hi)/2;
        int res=strncmp(p,t+sa[mid],m);
        if(!res){
            cout<<"Yes"<<endl;
            return;
        }
        if(res<0)hi=mid-1;
        else lo=mid+1;
    }
    cout<<"No"<<endl;
    return;
}*/
int main(){
    string s;
    cin>>s;
    int n=s.length();
    char a[n];
    for(int i=0;i<n;i++)a[i]=s[i];
    int *sa=suffarr(a,n);
    cout<<n<<' ';
    p(sa,n);
	return 0;
}
