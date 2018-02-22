#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 150010
#define mod 9875321
using namespace std;
int n,cnt,c[maxn][2],sz[maxn],h[maxn],p[maxn],v[maxn],rt,fa[maxn];
char op[10],d[10],ch[maxn];
void update(int x){
    sz[x]=sz[c[x][0]]+sz[c[x][1]]+1;
    h[x]=(h[c[x][0]]+1LL*v[x]*p[sz[c[x][0]]]%mod+1LL*h[c[x][1]]*p[sz[c[x][0]]+1]%mod)%mod;
}
void build(int l,int r,int f){
    if(l>r)return;
    int mid=l+r>>1;
    fa[mid]=f;c[f][mid>=f]=mid;v[mid]=ch[mid]-'a'+1;
    if(l==r){sz[mid]=1;h[mid]=v[mid];return;}
    build(l,mid-1,mid);build(mid+1,r,mid);
    update(mid);
}
int find(int x,int k){
    if(sz[c[x][0]]+1==k)return x;
    if(sz[c[x][0]]>=k)return find(c[x][0],k);
    else return find(c[x][1],k-sz[c[x][0]]-1);
}
void rotate(int x,int &k){
    int y=fa[x],z=fa[fa[x]],l,r;
    if(c[y][0]==x)l=0;else l=1;r=l^1;
    fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
    c[y][l]=c[x][r],c[x][r]=y;
    if(y==k){k=x;}
    else c[z][c[z][1]==y]=x;
    update(y);update(x);
}
void splay(int x,int &k){
    while(x!=k){
        int y=fa[x],z=fa[fa[x]];
        if(y!=k){
            if((c[y][0]==x)^(c[z][0]==y))rotate(x,k);
            else rotate(y,k);
        }
        rotate(x,k);
    }
}
int query(int k,int len){
    int x=find(rt,k),y=find(rt,k+len+1);
    splay(x,rt);splay(y,c[x][1]);
    int z=c[y][0];
    return h[z];
}
int solve(int x,int y){
    int l=1,r=min(cnt-x,cnt-y)-1,ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(query(x,mid)==query(y,mid))ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}
void insert(int k,int w){
    int x=find(rt,k),y=find(rt,k+1);
    splay(x,rt);splay(y,c[x][1]);
    int z=++cnt;v[z]=w;fa[z]=y;c[y][0]=z;
    update(z);update(y);update(x);
}
int qread()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main(){
    scanf("%s",ch+2);
    n=strlen(ch+2);cnt=n+2;
    p[0]=1;
    for(int i=1;i<=150004;i++)p[i]=p[i-1]*27%mod;
    build(1,n+2,0);rt=(n+3)>>1;
    int T;T=qread();
    int x,y;
    while(T--){
        scanf("%s",op);
        if(op[0]=='Q'){
            x=qread();y=qread();
            printf("%d\n",solve(x,y));
        }
        else if(op[0]=='R'){
            x=qread();scanf("%s",d);
            x=find(rt,x+1);splay(x,rt);
            v[rt]=d[0]-'a'+1;update(rt);
        }
        else{
            x=qread();scanf("%s",d);
            insert(x+1,d[0]-'a'+1);
        }
    }
}
