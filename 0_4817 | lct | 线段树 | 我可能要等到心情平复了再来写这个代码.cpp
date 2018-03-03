#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 400010
using namespace std;
int point[N],nxt[N],v[N],tr[N],delta[N],l[N],r[N],deep[N],mi[20];
int n,m,k,col[N],f[N][20],fa[N],ch[N][3],tot,sz,pos[N],cur[N];
void add(int x,int y){
    tot++;nxt[tot]=point[x];point[x]=tot;v[tot]=y;
    tot++;nxt[tot]=point[y];point[y]=tot;v[tot]=x;
}
void dfs(int rt){
    int x=rt; 
    while (true) {
        if (!deep[x]) {
            deep[x]=deep[f[x][0]]+1; 
            for (int i=1;i<=17;i++) {
                if (deep[x]-mi[i]<0) break;
                f[x][i]=f[f[x][i-1]][i-1];
            }
            l[x]=r[x]=++sz; pos[sz]=x; cur[x]=point[x];
        }
        bool pd=false;
        for (int i=cur[x];i;i=nxt[i]) {
            cur[x]=nxt[i];
            if (v[i]!=f[x][0]) {
                f[v[i]][0]=fa[v[i]]=x; x=v[i]; pd=true;
                break;
            }
        }
        if (!pd) {
            int t=f[x][0];// cout<<t<<endl;
            r[t]=max(r[t],r[x]);
            if (x==rt)  break;
            x=t;
        }
    }
}
int lca(int x,int  y){
    if (deep[x]<deep[y]) swap(x,y);
    int k=deep[x]-deep[y];
    for (int i=0;i<=17;i++)
     if ((k>>i)&1) x=f[x][i];
    if (x==y) return x;
    for (int i=17;i>=0;i--)
     if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
void update(int now){
    tr[now]=max(tr[now<<1],tr[now<<1|1]);
}
void pushdown(int now){
    if (delta[now]) {
        tr[now<<1]+=delta[now]; tr[now<<1|1]+=delta[now];
        delta[now<<1]+=delta[now]; delta[now<<1|1]+=delta[now];
        delta[now]=0;
    }
}
void change(int now,int l,int r,int ll,int rr,int val){
    if (ll<=l&&r<=rr) {
        tr[now]+=val; delta[now]+=val;
        return;
    }
    int mid=(l+r)/2; 
    pushdown(now);
    if (ll<=mid) change(now<<1,l,mid,ll,rr,val);
    if (rr>mid) change(now<<1|1,mid+1,r,ll,rr,val);
    update(now);
}
int find(int now,int l,int r,int x){
    if (l==r) return tr[now];
    int mid=(l+r)/2;
    pushdown(now);
    if (x<=mid) return find(now<<1,l,mid,x);
    else return find(now<<1|1,mid+1,r,x);
}
int query(int now,int l,int r,int ll,int rr){
    if (ll<=l&&r<=rr) return tr[now];
    int mid=(l+r)/2; int ans=0;
    pushdown(now);
    if (ll<=mid) ans=max(ans,query(now<<1,l,mid,ll,rr));
    if (rr>mid) ans=max(ans,query(now<<1|1,mid+1,r,ll,rr));
    return ans;}
bool isroot(int x){
    return ch[fa[x]][1]!=x&&ch[fa[x]][0]!=x;
}
int get(int x){
    return ch[fa[x]][1]==x;
}
void rotate(int x){
    int y=fa[x]; int z=fa[y]; int which=get(x);
    if (!isroot(y)) ch[z][ch[z][1]==y]=x;
    fa[x]=z; fa[y]=x; ch[y][which]=ch[x][which^1];
    fa[ch[x][which^1]]=y; ch[x][which^1]=y;
}
void splay(int x){
    int y;
    while (!isroot(x)){
        y=fa[x];
        if (!isroot(y)) rotate(get(y)==get(x)?y:x);
        rotate(x);
    }
}
int get_root(int x){
    while (ch[x][0]) x=ch[x][0];
    return x;
}
void access(int x){
    int t=0;
    while (x) {
        col[x]=k;
        splay(x);
        int t1=get_root(ch[x][1]);
        if (t1) change(1,1,n,l[t1],r[t1],1);
        ch[x][1]=t;
        int t2=get_root(t);
        if (t2) change(1,1,n,l[t2],r[t2],-1);
        t=x; x=fa[x];
    }
}
int main(){
    scanf("%d%d",&n,&m); k=n; mi[0]=1;
    for (int i=1;i<=18;i++) mi[i]=mi[i-1]*2;
    for (int i=1;i<n;i++) {
        int x,y; scanf("%d%d",&x,&y);
        add(x,y);
    }
    dfs(1);
    for (int i=1;i<=n;i++) change(1,1,n,l[i],r[i],1);
    for (int i=1;i<=m;i++) {
        int opt,x,y; scanf("%d%d",&opt,&x);
        if (opt==1) k++,access(x);
        if (opt==2) {
            scanf("%d",&y); int t=lca(x,y);
            printf("%d\n",find(1,1,n,l[x])+find(1,1,n,l[y])-2*find(1,1,n,l[t])+1);
        }
        if (opt==3) printf("%d\n",query(1,1,n,l[x],r[x]));
    }
}
