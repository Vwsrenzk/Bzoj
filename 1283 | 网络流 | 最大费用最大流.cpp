/*
	题目大意： 
		给出一个长度为N的正整数序列Ci，求一个子序列，使得原序列中任意长度为M的子串中被选出的元素不超过K(K,M<=100) 个，并且选出的元素之和最大。
	题解：
		直接每个点依次排开，i->i+1连（k,0）【k是流量限制,0是费用】的边，然后对于一个区间[l,r]就l->r连（1,val）；然后源点->1连（k,0）,n->T一样，跑一边最大费用最大流即可。你想 经过每个点的流量都保证了不超过k啊 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 1e9
#define maxn 2010
using namespace std;
int n,m,k,head[maxn],num=1,s,t,cost[maxn],p[maxn],C[maxn];
bool vis[maxn];
struct node{int from,to,pre,c,cc;}e[maxn*maxn];
void Insert(int from,int to,int c,int cc){
	e[++num].to=to;
	e[num].from=from;
	e[num].c=c;
	e[num].cc=cc;
	e[num].pre=head[from];
	head[from]=num;
}
bool spfa(){
	queue<int>q;
	memset(cost,-1,sizeof(cost));
	memset(p,-1,sizeof(p));
	memset(vis,0,sizeof(vis));
	cost[s]=1;vis[s]=1;q.push(s);
	while(!q.empty()){
		int now=q.front();q.pop();vis[now]=0;
		for(int i=head[now];i;i=e[i].pre){
			int to=e[i].to;
			if(cost[to]<cost[now]+e[i].cc&&e[i].c){
				cost[to]=cost[now]+e[i].cc;
				p[to]=i;
				if(!vis[to])q.push(to),vis[to]=1;
			}
		}
	}
	return cost[t]!=-1;
}
int work(){
	int ans=0,maxflow=0;
	while(spfa()){
		maxflow=INF;
		for(int i=t;i!=s;i=e[p[i]].from)maxflow=min(maxflow,e[p[i]].c);
		for(int i=t;i!=s;i=e[p[i]].from){
			int now=p[i];
			ans+=e[now].cc*maxflow;
			e[now].c-=maxflow;
			e[now^1].c+=maxflow;
		}
	}
	return ans;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	s=0,t=n+1;
	for(int i=1;i<=n;i++)scanf("%d",&C[i]);
	for(int i=1;i<n;i++){
		Insert(i,i+1,k,0);
		Insert(i+1,i,0,0);
	}
	Insert(s,1,k,0);Insert(1,s,0,0);
	Insert(n,t,k,0);Insert(t,n,0,0);
	for(int i=1;i<=n;i++){
		if(i+m<=n){
			Insert(i,i+m,1,C[i]);
			Insert(i+m,i,0,-C[i]);
		}
		else {
			Insert(i,t,1,C[i]);
			Insert(t,i,0,-C[i]);
		}
	}
	printf("%d",work());
	return 0;
}
