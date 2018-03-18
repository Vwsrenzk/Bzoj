#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 500010
#define eps 1e-6
using namespace std;
int n,head[maxn],num;
double f[maxn],g[maxn],h[maxn],w[maxn];
struct node{int to,pre;double v;}e[maxn*2];
void Insert(int from,int to,double v){
	e[++num].to=to;
	e[num].v=v;
	e[num].pre=head[from];
	head[from]=num;
}
void dfs1(int now,int father){
	for(int i=head[now];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father)continue;
		dfs1(to,now);
		h[to]=f[to]+(1-f[to])*(1-e[i].v);
		f[now]*=h[to];
	}
}
void dfs2(int now,int father){
	for(int i=head[now];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father)continue;
		double t=h[to]<eps?0:g[now]*f[now]/h[to];
		g[to]=t+(1-t)*(1-e[i].v);
		dfs2(to,now);
	}
}
int main(){
	scanf("%d",&n);
	int x,y;double z;
	for(int i=1;i<n;i++){
		scanf("%d%d%lf",&x,&y,&z);
		z/=100.0;
		Insert(x,y,z);Insert(y,x,z);
	}
	for(int i=1;i<=n;i++){scanf("%lf",&z);f[i]=1-z/100.0;}
	dfs1(1,0);
	g[1]=1;
	dfs2(1,0);
	double ans=0;
	for(int i=1;i<=n;i++)ans+=1-f[i]*g[i];
	printf("%.6lf",ans);
	return 0;
}
