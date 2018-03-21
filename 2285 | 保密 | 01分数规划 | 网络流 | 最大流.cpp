#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define eps 1e-3
#define INF 1000000000
#define maxn 710
using namespace std;
int n,m,n1,m1,s,t;
double maxflow,dis[maxn];
struct node{int x,y;double a,b;}E[100010];
int dcmp(double x){
	if(x<=eps&&x>=-eps)return 0;
	return (x>0)?1:-1;
}
namespace plan{
	int head[maxn],num;
	struct node{int to,pre;double v;}e[100010];
	double dis[maxn];bool vis[maxn];
	queue<int>q;
	void Insert(int from,int to){
		e[++num].to=to;
		e[num].pre=head[from];
		head[from]=num;
	}
	void spfa(int x){
		memset(dis,127,sizeof(dis));dis[n]=0;
		memset(vis,0,sizeof(vis));vis[n]=1;
		q.push(n);
		while(!q.empty()){
			int now=q.front();q.pop();vis[now]=0;
			for(int i=head[now];i;i=e[i].pre){
				int to=e[i].to;
				if(dcmp(dis[to]-dis[now]-e[i].v)>0){
					dis[to]=dis[now]+e[i].v;
					if(to==x&&dcmp(dis[to])<=0)return;
					if(!vis[to])vis[to]=1,q.push(to);
				}
			}
		}
	}
	bool check(int id,double mid){
		for(int i=1;i<=m;i++)e[i].v=E[i].a-E[i].b*mid;
		spfa(id);
		return dcmp(dis[id])<=0;
	}
	double find(int id){
		double l=0,r=10,mid,ans=INF;
		while(r-l>eps){
			mid=(l+r)*0.5;
			if(check(id,mid))ans=r=mid;
			else l=mid;
		}
		return ans;
	}
}

namespace Flow{
	int head[maxn],num,dep[maxn];
	struct node{int to,pre;double v;}e[100010];
	queue<int>q;
	void init(){
		memset(head,0,sizeof(head));num=1;
	}
	void Insert(int from,int to,double v){
		e[++num].to=to;e[num].v=v;e[num].pre=head[from];head[from]=num;
		e[++num].to=from;e[num].v=0;e[num].pre=head[to];head[to]=num;
	}
	bool bfs(int s,int t){
		memset(dep,-1,sizeof(dep));
		dep[s]=0;q.push(s);
		while(!q.empty()){
			int now=q.front();q.pop();
			for(int i=head[now];i;i=e[i].pre){
				int to=e[i].to;
				if(dep[to]==-1&&dcmp(e[i].v)){
					dep[to]=dep[now]+1;
					q.push(to);
				}
			}
		}
		return dep[t]!=-1;
	}
	double dfs(int now,int t,double flow){
		if(now==t||!dcmp(flow))return flow;
		double rest=flow;
		for(int i=head[now];i;i=e[i].pre){
			int to=e[i].to;
			if(dep[to]==dep[now]+1&&dcmp(e[i].v)){
				double delta=dfs(to,t,min(e[i].v,rest));
				e[i].v-=delta;
				e[i^1].v+=delta;
				rest-=delta;
				if(!dcmp(rest))break;
			}
		}
		return flow-rest;
	}
	void dinic(int s,int t){
		while(bfs(s,t))maxflow+=dfs(s,t,INF);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%lf%lf",&E[i].x,&E[i].y,&E[i].a,&E[i].b);
		plan::Insert(E[i].x,E[i].y);
	}
	scanf("%d%d",&m1,&n1);
	for(int i=1;i<=n1;i++)dis[i]=plan::find(i);
	Flow::init();
	s=n+1,t=s+1;
	for(int i=1;i<=n1;i++){
		if(i&1)Flow::Insert(s,i,dis[i]);
		else Flow::Insert(i,t,dis[i]);
	}
	for(int i=1;i<=m1;i++){
		int x,y;scanf("%d%d",&x,&y);
		Flow::Insert(x,y,INF);
	}
	Flow::dinic(s,t);
	if(maxflow>1e8)puts("-1");
	else printf("%.1lf",maxflow);
}
