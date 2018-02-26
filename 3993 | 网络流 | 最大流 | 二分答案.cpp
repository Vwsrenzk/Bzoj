#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#define eps 0.000001
#define maxn 110
#define INF 0x3f3f3f3f
using namespace std;
double a[maxn],b[maxn],sum,ans;
int n,m,S,T,head[maxn],num,dis[maxn];
bool c[maxn][maxn];
struct node{
	int to,pre;
	double v;
}e[maxn*maxn*2];
void Insert(int from,int to,double v){
	e[++num].to=to;e[num].v=v;e[num].pre=head[from];head[from]=num;
	e[++num].to=from;e[num].v=0;e[num].pre=head[to];head[to]=num;
}
queue<int>q;
bool bfs(){
	memset(dis,-1,sizeof(dis));
	dis[S]=0;q.push(S);
	while(!q.empty()){
		int now=q.front();q.pop();
		for(int i=head[now];i;i=e[i].pre){
			int to=e[i].to;
			if((dis[to]==-1)&&(e[i].v>0)){
				dis[to]=dis[now]+1;
				q.push(e[i].to);
			}
		}
	}
	return dis[T]!=-1;
}
double dinic(int x,double flow){
	if(x==T)return flow;
	double rest=flow,delta=0;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(e[i].v>0&&(dis[to]==dis[x]+1)){
			delta=dinic(to,min(rest,e[i].v));
			if(delta<eps)dis[to]=-1;
			e[i].v-=delta;
			e[i^1].v+=delta;
			rest-=delta;
		}
	}
	return flow-rest;
}
bool check(double t){
	memset(head,0,sizeof(head));num=1;
	memset(e,0,sizeof(e));
	for(int i=1;i<=m;i++)Insert(S,i,t*b[i]);
	for(int i=1;i<=n;i++)Insert(i+m,T,a[i]);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		if(c[i][j])Insert(i,j+m,INF);
	double maxflow=0;
	while(bfs())
		maxflow+=dinic(S,INF);
	if(fabs(maxflow-sum)<eps)return 1;
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	S=0;T=n+m+1;
	for(int i=1;i<=n;i++)scanf("%lf",&a[i]),sum+=a[i];
	for(int i=1;i<=m;i++)scanf("%lf",&b[i]);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)scanf("%d",&c[i][j]);
	double l=0,r=sum;
	while(r-l>eps){
		double mid=(l+r)/2.0;
		if(check(mid))ans=mid,r=mid;
		else l=mid;
	}
	printf("%.6lf",ans);
}
