#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 4010
#define maxm 120010
#define INF 1000000000
using namespace std;
int head[maxn],dis[maxn],num=1,n,m,S,T;
int belong[maxn],st[maxn],dfn[maxn],low[maxn],in[maxn],top,cnt,group;
struct node{int from,to,pre,v;}e[maxm];
void Insert(int from,int to,int v){
	e[++num].to=to;e[num].v=v;e[num].pre=head[from];head[from]=num;e[num].from=from;
	e[++num].to=from;e[num].v=0;e[num].pre=head[to];head[to]=num;e[num].from=to;
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
		if(dis[to]==dis[x]+1&&e[i].v>0){
			int delta=dinic(to,min(e[i].v,rest));
			e[i].v-=delta;
			e[i^1].v+=delta;
			rest-=delta;
		}
	}
	return flow-rest;
}
void Tarjan(int u){
	cnt++;
	dfn[u]=low[u]=cnt;in[u]=1;st[++top]=u;
	for(int i=head[u];i;i=e[i].pre){
		if(e[i].v==0)continue;
		int v=e[i].to;
		if(!dfn[v]){
			Tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(in[v])low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		group++;
		while(top&&st[top]!=u){
			belong[st[top]]=group;
			in[st[top]]=0;
			top--;
		}
		belong[st[top]]=group;
		in[st[top]]=0;
		top--;
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&S,&T);
	int x,y,z;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		Insert(x,y,z);
	}
	int mxflow=0;
	while(bfs()){mxflow+=dinic(S,INF);}
	for(int i=1;i<=n;i++)
		if(!dfn[i])Tarjan(i);
	for(int i=2;i<=num;i+=2){
		if(e[i].v)puts("0 0");
		else {
			if(belong[e[i].from]!=belong[e[i].to])printf("1 ");
			else printf("0 ");
			if(belong[e[i].from]==belong[S]&&belong[e[i].to]==belong[T])puts("1");
			else puts("0");
		}
	}
	return 0;
}
/*
N个点M条边的图
每条边有流量
问所有最小割的边集并
问所有最小割的边集交
N<=4000 M<=60000

做网络流
将满流边剔除做强连通分量
一条边属于最小割的并当且仅当当前起点和终点不属于同一个强连通分量
一条边属于最小割的交当且仅当当前起点与源点属于同集合且终点与汇点属于同集合并且满足上一个条件

*/
