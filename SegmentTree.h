ll a[MAX],tree[4*MAX+1]={0};
void init(ll *a,ll s,ll e,ll *tree,ll n){
    if(s==e){
        tree[n]=a[s];
        return;
    }
    ll l=n*2,r=n*2+1,mid=(s+e)/2;
    init(a,s,mid,tree,l);
    init(a,mid+1,e,tree,r);
    tree[n]+=tree[l]+tree[r];
    return;
}
ll query(ll *tree,ll s,ll e,ll i,ll j,ll n){
    if(j<s||i>e)return 0;
    if(s>=i&&e<=j)return tree[n];
    ll l=n*2,r=n*2+1,mid=(s+e)/2;
    ll left=query(tree,s,mid,i,j,l);
    ll rigth=query(tree,mid+1,e,i,j,r);
    return left+rigth;
}
void update(ll *tree,ll s,ll e,ll i,ll val,ll n){
    if(i>e||i<s)return;
    if(s==e){
        tree[n]=val;
        return;
    }
    ll l=n*2,r=n*2+1,mid=(s+e)/2;
    update(tree,s,mid,i,val,l);
    update(tree,mid+1,e,i,val,r);
    tree[n]=tree[l]+tree[r];
    return;
}
