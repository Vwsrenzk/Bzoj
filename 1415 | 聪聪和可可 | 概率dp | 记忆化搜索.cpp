#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 1000000000
#define maxn 1010
using namespace std;
int n,E,s,t,num;
int head[maxn],dis[maxn][maxn];
bool vis[maxn][maxn];
double dp[maxn][maxn];
struct node{int to,pre;}e[maxn*2];
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
void bfs(int x){
	queue<int>q;
	q.push(x);dis[x][x]=0;
	while(!q.empty()){
		int now=q.front();q.pop();
		for(int i=head[now];i;i=e[i].pre){
			int to=e[i].to;
			if(dis[x][to]>dis[x][now]+1){
				dis[x][to]=dis[x][now]+1;
				q.push(to);
			}
		}
	}
}
double dfs(int a,int b){
	if(a==b)return dp[a][b]=0;
	if(vis[a][b])return dp[a][b];
	vis[a][b]=1;
	int mins=INF,nxt=b;
	for(int i=head[b];i;i=e[i].pre){//聪聪走的第一步 
		int to=e[i].to;
		if(dis[to][a]==mins&&to<nxt)nxt=to;
		else if(dis[to][a]<mins){
			mins=dis[to][a];
			nxt=to;
		}
	}
	int nxtt=nxt;
	for(int i=head[nxt];i;i=e[i].pre){
		int to=e[i].to;
		if(dis[to][a]==mins&&to<nxtt)nxtt=to;
		else if(dis[to][a]<mins){
			mins=dis[to][a];
			nxtt=to;
		}
	}
	if(nxtt==a)return dp[a][b]=1.0;
	dp[a][b]=dfs(a,nxtt);//可可没有动 
	int cnt=1;
	for(int i=head[a];i;i=e[i].pre){
		int to=e[i].to;
		cnt++;
		dp[a][b]+=dfs(to,nxtt);
	}
	dp[a][b]/=cnt*1.0;
	dp[a][b]+=1;
	return dp[a][b];
}
int main(){
	memset(dis,0x3f,sizeof(dis));
	scanf("%d%d%d%d",&n,&E,&s,&t);
	int x,y;
	for(int i=1;i<=E;i++){
		scanf("%d%d",&x,&y);
		Insert(x,y);Insert(y,x);
	}
	for(int i=1;i<=n;i++)bfs(i);
	printf("%.3f",dfs(t,s));
	return 0;
}
