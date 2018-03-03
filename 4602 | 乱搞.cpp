#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define maxn 1010
#define eps 0.000001
using namespace std;
int T,n,m,head[maxn],num;
double tmp[maxn];
bool vis[maxn];
struct node{int to,pre;double v;}e[40010];
void Insert(int from,int to,double v){
	e[++num].to=to;
	e[num].v=v;
	e[num].pre=head[from];
	head[from]=num;
}
bool dfs(int x,double w){
	vis[x]=1;tmp[x]=w;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(!vis[to]){if(dfs(to,w*e[i].v))return 1;}
		else if(fabs(tmp[to]-w*e[i].v)>eps)return 1;
	}
	return 0;
}
int main(){
	scanf("%d",&T);
	int n,m;
	for(int cs=1;cs<=T;cs++){
		memset(head,0,sizeof(head));num=0;
		memset(e,0,sizeof(e));
		memset(vis,0,sizeof(vis));
		memset(tmp,0,sizeof(tmp));
		printf("Case #%d: ",cs);
		scanf("%d%d",&n,&m);
		int x,y;double z,c;
		for(int i=1;i<=m;i++){
			scanf("%d%d%lf%lf",&x,&y,&z,&c);
			Insert(x,y,c/z);Insert(y,x,z/c);
		}
		bool flag=0;
		for(int i=1;i<=n&&!flag;i++){
			if(!vis[i])flag|=dfs(i,1);
		}
		if(flag==0)puts("Yes");
		else puts("No");
	}
	return 0;
}
