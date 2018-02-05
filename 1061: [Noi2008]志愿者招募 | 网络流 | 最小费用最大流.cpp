/*
    题目大意：
        项目需要N 天才能完成，其中第i 天至少需要Ai 个人。 布布通过了解得知，一共有M 类志愿者可以招募。其中第i 类可以从第Si 天工作到第Ti 天，招募费用是每人Ci 元。新官上任三把火，为了出色地完成自己的工作，布布希望用尽量少的费用招募足够的志愿者 
    题解：
        http://blog.csdn.net/lych_cys/article/details/50703729 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 1e9
#define maxn 10010
using namespace std;
int n,m,head[maxn],num=1,a[maxn],S,T,ans,dis[maxn];
bool mark[maxn],vis[maxn];
struct node{int to,pre,c,cc;}e[maxn*10];
void Insert(int from,int to,int c,int cc){
    e[++num].to=to;
    e[num].c=c;
    e[num].cc=cc;
    e[num].pre=head[from];
    head[from]=num;
}
bool spfa(){
    queue<int>q;
    q.push(T);
    for(int i=S;i<=T;i++)vis[i]=0,dis[i]=INF;
    vis[T]=1;dis[T]=0;
    while(!q.empty()){
        int now=q.front();q.pop();vis[now]=0;
        for(int i=head[now];i;i=e[i].pre){
            int to=e[i].to;
            if(dis[to]>dis[now]-e[i].cc&&e[i^1].c){
                dis[to]=dis[now]-e[i].cc;  
                if(!vis[to])vis[to]=1,q.push(to);
            }
        }
    }
    return dis[S]!=INF;
}
int dfs(int now,int flow){
    mark[now]=1;
    if(now==T)return flow;
    int delta,used=0;
    for(int i=head[now];i;i=e[i].pre){
        int to=e[i].to;
        if(e[i].c&&!mark[to]&&dis[to]==dis[now]-e[i].cc){
            delta=dfs(to,min(flow-used,e[i].c));
            ans+=delta*e[i].cc;
            used+=delta;
            e[i].c-=delta;e[i^1].c+=delta;
            if(used==flow)return used;
        }
    }
    return used;
}
void solve(){
    int tmp=0;
    while(spfa()){
        mark[T]=1;
        while(mark[T]){
            memset(mark,0,sizeof(mark));
            tmp+=dfs(S,INF);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    S=0,T=1005;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        int cha=a[i]-a[i-1];
        if(cha>0)Insert(S,i,cha,0),Insert(i,S,0,0);
        else Insert(i,T,-cha,0),Insert(T,i,0,0);
        Insert(i+1,i,INF,0),Insert(i,i+1,0,0);
    }
    Insert(n+1,T,a[n],0);Insert(T,n+1,0,0);
    int l,r,C;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&l,&r,&C);
        Insert(l,r+1,INF,C);Insert(r+1,l,0,-C);
    }
    solve();
    printf("%d",ans);
    return 0;
}
