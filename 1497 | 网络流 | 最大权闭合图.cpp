#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 100010
#define INF 1000000000
using namespace std;
int n,m,dis[maxn],head[maxn],num=1,ans,S,T,cur[maxn];
struct node{int to,pre,v;}e[maxn*5];
void Insert(int from,int to,int v){
	e[++num].to=to;e[num].v=v;e[num].pre=head[from];head[from]=num;
	e[++num].to=from;e[num].v=0;e[num].pre=head[to];head[to]=num;
}
bool bfs(){
	for(int i=S;i<=T;i++)dis[i]=INF;
	queue<int>q;
	dis[S]=0;q.push(S);
	while(!q.empty()){
		int now=q.front();q.pop();
		for(int i=head[now];i;i=e[i].pre){
			int to=e[i].to;
			if(dis[to]>dis[now]+1&&e[i].v>0){
				dis[to]=dis[now]+1;
				if(to==T)return 1;
				q.push(to);
			}
		}
	}
	return dis[T]!=INF;
}
int dinic(int x,int flow){
	if(x==T)return flow;
	int rest=flow;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(dis[to]==dis[x]+1&&e[i].v>0){
			int delta=dinic(to,min(rest,e[i].v));
			e[i].v-=delta;
			e[i^1].v+=delta;
			rest-=delta;
		}
	}
	if(rest==flow)dis[x]=-1;
	return flow-rest;
}
int main(){
	scanf("%d%d",&n,&m);
	int x,y,z;
	S=0;T=n+m+1;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		Insert(i+m,T,x);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);ans+=z;
		Insert(S,i,z);
		Insert(i,x+m,INF);
		Insert(i,y+m,INF);
	}
	while(bfs())ans-=dinic(S,INF);
	printf("%d",ans);
	return 0;
}
