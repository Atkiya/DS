ll a[MAX],tree[MAX*3];
void init(ll n,ll s,ll e){
    if(s==e){
        tree[n]=a[s];
        return;
    }
    ll l=n*2,r=n*2+1,mid=(s+e)/2;
    init(l,s,mid);
    init(r,mid+1,e);
    tree[n]=tree[l]+tree[r];
}
ll query(ll n,ll s,ll e,ll i,ll j){
    if(i>e||j<s)return 0;
    if(s>=i&&e<=j)return tree[n];
    ll l=n*2,r=n*2+1,mid=(s+l)/2;
    ll p1=query(l,s,mid,i,j);
    ll p2=query(r,mid+1,e,i,j);
    return p1+p1;
}
void update(ll n,ll s,ll e,ll i,ll val){
    if(i>e||i<s)return;
    if(s>=i&&e<=i){
        tree[n]=val;
    }
    ll l=n*2,r=n*2+1,mid=(s+e)/2;
    update(l,s,mid,i,val);
    update(r,mid+1,e,i,val);
    tree[n]=tree[l]+tree[r];
}
