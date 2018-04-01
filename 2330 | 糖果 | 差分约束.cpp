#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 100010
using namespace std;
int head[maxn],num,n,k,dis[maxn],t[maxn],S;
bool vis[maxn];
struct node{int to,pre,v;}e[maxn*4];
void Insert(int from,int to,int v){
	e[++num].to=to;
	e[num].v=v;
	e[num].pre=head[from];
	head[from]=num;
}
queue<int>q;
bool spfa(){
	q.push(S);
	memset(vis,0,sizeof(vis));
	dis[S]=0;vis[S]=1;t[S]++;
	while(!q.empty()){
		int now=q.front();q.pop();vis[now]=0;
		for(int i=head[now];i;i=e[i].pre){
			int to=e[i].to;
			if(dis[to]<dis[now]+e[i].v){
				dis[to]=dis[now]+e[i].v;
				t[to]++;
				if(t[to]>=n)return 0;
				vis[to]=1;q.push(to);
			}
		}
	}
	return 1;
}
int main(){
	scanf("%d%d",&n,&k);
	int x,y,z;
	for(int i=1;i<=k;i++){
		scanf("%d%d%d",&z,&x,&y);
		if(z==1){Insert(x,y,0);Insert(y,x,0);}
		if(z==2){
			if(x==y){puts("-1");return 0;}
			Insert(x,y,1);
		}
		if(z==3)Insert(y,x,0);
		if(z==4){
			if(x==y){puts("-1");return 0;}
			Insert(y,x,1);
		}
		if(z==5)Insert(x,y,0);
	}
	for(int i=n;i>=1;i--)Insert(S,i,1);
	if(!spfa()){puts("-1");return 0;}
	long long ans=0;
	for(int i=1;i<=n;i++)ans+=dis[i];
	cout<<ans;
	return 0;
}
