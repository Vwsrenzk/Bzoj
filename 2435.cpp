#include<iostream>
#include<cstdio>
#include<cstdlib>
#define maxn 1000010
using namespace std;
int n,sz[maxn],head[maxn],num;
long long ans=0;
struct node{int to,pre,v;}e[maxn*2];
void Insert(int from,int to,int v){
    e[++num].to=to;
    e[num].v=v;
    e[num].pre=head[from];
    head[from]=num;
}
void dfs(int x,int father){
    sz[x]=1;
    for(int i=head[x];i;i=e[i].pre){
        int to=e[i].to;
        if(to==father)continue;
        dfs(to,x);
        sz[x]+=sz[to];
        ans+=(long long)e[i].v*abs(sz[to]-(n-sz[to]));
    }
}
int main(){
    scanf("%d",&n);
    int x,y,z;
    for(int i=1;i<n;i++){
        scanf("%d%d%d",&x,&y,&z);
        Insert(x,y,z);Insert(y,x,z);
    }
    dfs(1,0);
    cout<<ans;
    return 0;
}
