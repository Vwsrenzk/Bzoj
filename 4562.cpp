#include<iostream>
#include<cstdio>
#include<queue>
#define maxn 100010
using namespace std;
int dis[maxn],n,m,head[maxn],num,chu[maxn],ru[maxn],du[maxn];
struct node{int to,pre;}e[maxn*2];
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
queue<int>q;
int main(){
	scanf("%d%d",&n,&m);
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		Insert(x,y);chu[x]++;ru[y]++;du[x]++;du[y]++;
	}
	for(int i=1;i<=n;i++)
		if(ru[i]==0){
			q.push(i);
			dis[i]=1;
		}
	while(!q.empty()){
		int now=q.front();q.pop();
		for(int i=head[now];i;i=e[i].pre){
			int to=e[i].to;
			dis[to]+=dis[now];
			ru[to]--;
			if(ru[to]==0)q.push(to);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(!du[i])continue;
		if(chu[i]==0)ans+=dis[i];
	}
	cout<<ans;
	return 0;
}
