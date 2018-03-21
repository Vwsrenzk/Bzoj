#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 120
#define INF 1000000000
using namespace std;
int head[maxn],num,n,S,T,dis[maxn],a[maxn];
struct node{int to,pre,v;}e[maxn*maxn];
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
		if(dis[to]==dis[x]+1&&e[i].v>0){
			int delta=dinic(to,min(e[i].v,rest));
			e[i].v-=delta;
			e[i^1].v+=delta;
			rest-=delta;
		}
	}
	return flow-rest;
}
int main(){
	int Case;scanf("%d",&Case);
	while(Case--){
		memset(head,0,sizeof(head));num=1;
		scanf("%d",&n);
		S=0,T=n*2+1;
		int x,cnt=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i])Insert(S,i,1);
			else Insert(i+n,T,1),cnt++;
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			if(!a[i])continue;
			if(!x)Insert(i+n,T,1),cnt++;
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				scanf("%d",&x);
				if(x||i==j)Insert(i,j+n,1);
			}
		int ans=0;
 		while(bfs()){
			ans+=dinic(S,INF);
		}
		if(ans<cnt)puts("T_T");
		else puts("^_^");
	}
	return 0;
}
