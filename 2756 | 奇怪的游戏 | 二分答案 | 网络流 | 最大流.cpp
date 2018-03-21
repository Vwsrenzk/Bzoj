#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 2010
#define INF 1LL<<60
using namespace std;
int val[51][51],id[51][51],col[51][51],head[maxn],cur[maxn];
int n,m,dis[maxn],S,T,num,cnt;
struct node{int to,pre;long long v;}e[maxn*maxn];
long long n1,n2,s1,s2;
void Insert(int from,int to,long long v){
    e[++num].to=to;e[num].v=v;e[num].pre=head[from];head[from]=num;
    e[++num].to=from;e[num].v=0;e[num].pre=head[to];head[to]=num;
}
bool jg(int x,int y){
    return (x<=n)&&(x>=1)&&(y<=m)&&(y>=1);
}
bool bfs(){
    queue<int>q;
    memset(dis,-1,sizeof(dis));
    for(int i=S;i<=T;i++)cur[i]=head[i];
    dis[S]=0;q.push(S);
    while(!q.empty()){
        int now=q.front();q.pop();
        for(int i=head[now];i;i=e[i].pre){
            int to=e[i].to;
            if(dis[to]==-1&&e[i].v>0){
                dis[to]=dis[now]+1;
                if(to==T)return 1;
                q.push(to);
            }
        }
    }
    return dis[T]!=-1;
}
long long dinic(int x,long long flow){
    if(x==T||flow==0)return flow;
    long long rest=flow;
    for(int &i=cur[x];i;i=e[i].pre){
        int to=e[i].to;
        if(dis[to]==dis[x]+1&&e[i].v>0){
            long long delta=dinic(to,min(e[i].v,rest));
            e[i].v-=delta;
            e[i^1].v+=delta;
            rest-=delta;
            if(rest==0)return flow;
        }
    }
    return flow-rest;
}
long long Flow(){
    long long res=0;
    while(bfs()){
        res+=dinic(S,INF);
    }
    return res;
}
bool check(long long x){
    long long tot=0;
    num=1;memset(head,0,sizeof(head));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(col[i][j]){
                Insert(S,id[i][j],x-val[i][j]);
                tot+=x-val[i][j];
                if(jg(i-1,j))Insert(id[i][j],id[i-1][j],INF);
                if(jg(i,j-1))Insert(id[i][j],id[i][j-1],INF);
                if(jg(i+1,j))Insert(id[i][j],id[i+1][j],INF);
                if(jg(i,j+1))Insert(id[i][j],id[i][j+1],INF);
            }
            else
                Insert(id[i][j],T,x-val[i][j]);
        }
    long long mxf=Flow();
    return tot==mxf;
}
int main(){
    int Case;scanf("%d",&Case);
    while(Case--){
        scanf("%d%d",&n,&m);
        n1=0;n2=0;s1=0;s2=0;
        S=0;T=n*m+1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&val[i][j]);
        int mx=0;cnt=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                col[i][j]=(i+j)&1,id[i][j]=++cnt,mx=max(mx,val[i][j]);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                if(col[i][j]){n1++;s1+=val[i][j];}
                else {n2++;s2+=val[i][j];}
            }
        if(n1==n2){
            if(s1!=s2){puts("-1");continue;}
            else{
                long long l=mx,r=(1LL<<50),ans;
                while(l<=r){
                    long long mid=(l+r)>>1;
                    if(check(mid))r=mid-1,ans=mid;
                    else l=mid+1;
                }
                printf("%lld\n",ans*n1-s1);
            }
        }
        else{
            long long x=(s2-s1)/(n2-n1);
            if(x<mx){puts("-1");continue;}
            if(check(x))printf("%lld\n",x*n1-s1);
            else puts("-1");
        }
    }
    return 0;
}
