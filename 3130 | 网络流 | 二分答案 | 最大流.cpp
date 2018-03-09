/*注意第43行*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 110
#define INF 1000000000
#define eps 0.00001
using namespace std;
int head[maxn],num=1;
struct node{int to,pre;double v;}e[maxn*maxn*2],e1[maxn*maxn*2];
int n,m,S,T,dis[maxn];
double p;
void Insert(int from,int to,double v){
    e[++num].to=to;e[num].v=v;e[num].pre=head[from];head[from]=num;
    e[++num].to=from;e[num].v=0;e[num].pre=head[to];head[to]=num;
}
double abs(double x){return x>0?x:-x;}
bool bfs(){
    queue<int>q;
    memset(dis,-1,sizeof(dis));
    dis[S]=0;q.push(S);
    while(!q.empty()){
        int now=q.front();q.pop();
        for(int i=head[now];i;i=e[i].pre){
            int to=e[i].to;
            if(e[i].v>0&&dis[to]==-1){
                dis[to]=dis[now]+1;
                if(to==T)return 1;
                q.push(to);
            }
        }
    }
    return dis[T]!=-1;
}
double dinic(int x,double flow){
    if(x==T||flow<eps)return flow;
    double rest=flow;
    for(int i=head[x];i;i=e[i].pre){
        int to=e[i].to;
        if((dis[to]==dis[x]+1)&&(e[i].v>0)){
            double delta=dinic(to,min(rest,e[i].v));
            if(!delta)dis[to]=-1;
            e[i].v-=delta;
            e[i^1].v+=delta;
            rest-=delta;
        }
    }
    return flow-rest;
}
double solve(double mid){
    for(int i=1;i<=num;i++){e[i]=e1[i];e[i].v=min(e[i].v,mid);}
    double res=0;
    while(bfs()){
        res+=dinic(S,INF);
    }
    return res;
}
int main(){
    scanf("%d%d%lf",&n,&m,&p);
    S=1,T=n;
    int x,y,z;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        Insert(x,y,z);
    }
    for(int i=1;i<=num;i++)e1[i]=e[i];
    double ans=solve(50001);
    double l=0,r=50000,res=50001;
    while(r-l>=eps){
        double mid=(l+r)*0.5;
        double nowans=solve(mid);
        if(abs(ans-nowans)<eps)r=mid,res=mid;
        else l=mid;
    }
    printf("%.0lf\n%.5lf",ans,res*p);
}
