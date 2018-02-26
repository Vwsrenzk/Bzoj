#include<iostream>
#include<cstdio>
#include<cmath>
#include<queue>
#include<cstring>
#define maxn 810
#define INF 1000000000
using namespace std;
int n,m,d,S,T,num=1,head[maxn],ans;
int map[21][21],dis[maxn];
struct node{int to,pre,v;}e[maxn*maxn*4];
int count(int x,int y){return (x-1)*m+y;}
void Insert(int from,int to,int v){
	e[++num].to=to;e[num].v=v;e[num].pre=head[from];head[from]=num;
	e[++num].to=from;e[num].v=0;e[num].pre=head[to];head[to]=num;
}
double dist(double x,double y,double xx,double yy){
	return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
}

bool bfs(){
	queue<int>q;
    for(int i=1;i<=T;i++)dis[i]=INF;
    q.push(S);dis[S]=0;
    while(!q.empty()){
        int x=q.front();q.pop();
        for(int i=head[x];i;i=e[i].pre){
            int to=e[i].to;
            if(e[i].v&&dis[to]>dis[x]+1){
                dis[to]=dis[x]+1;
                if(to==T)return true;
                q.push(to);
            }
        }
    }
    return dis[T]!=INF;
}
int dinic(int x,int flow){
	int rest=flow;
	if(x==T)return flow;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(dis[to]==dis[x]+1&&e[i].v){
			int delta=dinic(to,min(e[i].v,rest));
			if(delta==0)dis[to]=0;
			e[i].v-=delta;
			e[i^1].v+=delta;
			rest-=delta;
		}
	}
	return flow-rest;
}
int main(){
	scanf("%d%d%d",&n,&m,&d);
	S=0;T=2*n*m+1;
	char ch[25];
	for(int i=1;i<=n;i++){
		scanf("%s",ch+1);
		for(int j=1;j<=m;j++){
			map[i][j]=ch[j]-'0';
			if(map[i][j]&&(i-d<=0||i+d>n||j-d<=0||j+d>m))Insert(count(i,j)+n*m,T,INF);
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		if(map[i][j]==0)continue;
		for(int ii=1;ii<=n;ii++)
		for(int jj=1;jj<=m;jj++){
			if(i==ii&&j==jj)continue;
			if(dist(i,j,ii,jj)<=d)Insert(count(i,j)+m*n,count(ii,jj),INF);
		}
	}
	for(int i=1;i<=n;i++){
		scanf("%s",ch+1);
		for(int j=1;j<=m;j++)
			if(ch[j]=='L')Insert(S,count(i,j),1),ans++;
	}
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		if(map[i][j])Insert(count(i,j),count(i,j)+n*m,map[i][j]);
	while(bfs())ans-=dinic(S,INF);
	printf("%d",ans);
	return 0;
}
