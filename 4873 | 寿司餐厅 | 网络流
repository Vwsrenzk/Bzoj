#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 10010
#define INF 1000000000
using namespace std;
int a[110],id[110][110],v[110][110],head[maxn],num=1,n,m,S,T,tot,dis[maxn];
struct node{int to,pre,v;}e[maxn*10];
void Insert(int from,int to,int v){
	e[++num].to=to;e[num].v=v;e[num].pre=head[from];head[from]=num;
	e[++num].to=from;e[num].v=0;e[num].pre=head[to];head[to]=num;
}
bool bfs(){
	queue<int>q;
	memset(dis,-1,sizeof(dis));
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
int dinic(int x,int flow){
	if(x==T||flow==0)return flow;
	int rest=flow;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if((dis[to]==dis[x]+1)&&(e[i].v>0)){
			int delta=dinic(to,min(e[i].v,rest));
			if(!delta)dis[to]=-1;
			e[i].v-=delta;
			e[i^1].v+=delta;
			rest-=delta;
		}
	}
	return flow-rest;
}
int main(){
	scanf("%d%d",&n,&m);
	int k=0,sum=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),k=max(k,a[i]);
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++){
			scanf("%d",&v[i][j]);
			id[i][j]=++tot;
		}
	S=0,T=tot+k+1;
	for(int i=1;i<=k;i++)Insert(tot+i,T,m*i*i);
	for(int i=1;i<=n;i++)Insert(id[i][i],tot+a[i],INF),v[i][i]-=a[i];
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++){
			if(v[i][j]>0){Insert(S,id[i][j],v[i][j]);sum+=v[i][j];}
			else if(v[i][j]<0){Insert(id[i][j],T,-v[i][j]);}
			if(j>i){Insert(id[i][j],id[i][j-1],INF);Insert(id[i][j],id[i+1][j],INF);}
		}
	while(bfs()){
		sum-=dinic(S,INF);
	}
	printf("%d",sum);
	return 0;
}
