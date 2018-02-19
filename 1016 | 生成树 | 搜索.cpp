#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 31011
#define maxn 1005
using namespace std;
int n,m,cnt,tot,ans=1,sum,fa[105];
struct edge{
	int x,y,v;
	bool operator < (const edge &w)const{
		return v<w.v;
	}
}e[maxn];
struct data{int l,r,v;}a[maxn];
int find(int x){
	if(fa[x]==x)return x;
	return find(fa[x]);
}
void dfs(int x,int now,int k){
	if(now==a[x].r+1){
		if(k==a[x].v)sum++;
		return;
	}
	int f1=find(e[now].x),f2=find(e[now].y);
	if(f1!=f2){
		fa[f1]=f2;
		dfs(x,now+1,k+1);
		fa[f1]=f1;fa[f2]=f2;
	}
	dfs(x,now+1,k);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].v);
	sort(e+1,e+m+1);
	for(int i=1;i<=m;i++){
		if(e[i].v!=e[i-1].v){a[++cnt].l=i;a[cnt-1].r=i-1;}
		int f1=find(e[i].x),f2=find(e[i].y);
		if(f1!=f2){fa[f1]=f2;a[cnt].v++;tot++;}
	}
	a[cnt].r=m;
	if(tot!=n-1){printf("0");return 0;}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=cnt;i++){
		sum=0;
		dfs(i,a[i].l,0);
		ans=ans*sum%mod;
		for(int j=a[i].l;j<=a[i].r;j++){
			int f1=find(e[j].x),f2=find(e[j].y);
			if(f1!=f2)fa[f1]=f2;
		}
	}
	printf("%d",ans);
	return 0;
}
