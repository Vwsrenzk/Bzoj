#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 55
#define INF 1000000000
using namespace std;
int head[maxn],num,a1,a2,an,b1,b2,bn,n,S,T,ans,dis[maxn];
struct node{int to,pre,v;}e[100005];
char mp[maxn][maxn];
void Insert(int from,int to,int v){
	e[++num].to=to;e[num].v=v;e[num].pre=head[from];head[from]=num;
	e[++num].to=from;e[num].v=0;e[num].pre=head[to];head[to]=num;
}
void build(){
	memset(head,0,sizeof(head));num=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(mp[i][j]=='O')Insert(i,j,2);
			if(mp[i][j]=='N')Insert(i,j,INF);
		}
	}
}
bool bfs(){
	memset(dis,-1,sizeof(dis));
	queue<int>q;
	q.push(S);dis[S]=0;
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
void maxflow(){
	while(bfs()){
		ans+=dinic(S,INF);
	}
}
int main(){
	while(scanf("%d%d%d%d%d%d%d",&n,&a1,&a2,&an,&b1,&b2,&bn)!=EOF){
		a1++;a2++;b1++;b2++;
		S=0,T=n+1;
		for(int i=1;i<=n;i++)scanf("%s",mp[i]+1);
		build();
		Insert(S,a1,an*2);Insert(a2,T,an*2);
		Insert(S,b1,bn*2);Insert(b2,T,bn*2);
		bool flag=0;
		ans=0;
		maxflow();
		if(ans<2*(an+bn))flag=1;
		if(!flag){
			build();
			Insert(S,a1,an*2);Insert(a2,T,an*2);
			Insert(S,b2,bn*2);Insert(b1,T,bn*2);
			ans=0;
			maxflow();
			if(ans<2*(an+bn))flag=1;
		}
		if(flag)puts("No");
		else puts("Yes");
	}
}
