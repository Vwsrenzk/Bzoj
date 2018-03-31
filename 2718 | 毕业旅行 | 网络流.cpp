#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 410
#define INF 1000000000
using namespace std;
int n,m,dis[maxn],head[maxn],num=1,mp[maxn][maxn],S,T;
struct node{int to,pre,v;}e[maxn*maxn];
void Insert(int from,int to,int v){
	e[++num].to=to;e[num].v=v;e[num].pre=head[from];head[from]=num;
	e[++num].to=from;e[num].v=0;e[num].pre=head[to];head[to]=num;
}
bool bfs(){
	queue<int>q;
	q.push(S);
	memset(dis,-1,sizeof(dis));
	dis[S]=0;
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
		if((dis[to]==dis[x]+1)&&e[i].v>0){
			int delta=dinic(to,min(rest,e[i].v));
			e[i].v-=delta;
			e[i^1].v+=delta;
			rest-=delta;
		}
	}
	return flow-rest;
}
int main(){
	scanf("%d%d",&n,&m);
	S=0;T=n+n+1;
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		mp[x][y]=1;
	}
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		mp[i][j]|=mp[i][k]&mp[k][j];
	for(int i=1;i<=n;i++){
		Insert(S,i,1);
		Insert(i+n,T,1);
		for(int j=1;j<=n;j++)
			if(mp[i][j])Insert(i,j+n,INF);
	}
	int ans=0;
	while(bfs()){
		ans+=dinic(S,INF);
	}
	printf("%d",n-ans);
	return 0;
}
/*
一个N个点DAG
选出尽量多的点
使得这些点互相不能到达
问最多能选多少个点
N<=200

一个点向所有它能到达的点连边
做二分图匹配
每条增广链对应一个可以选择的点
*/
