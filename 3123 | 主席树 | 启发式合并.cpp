#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 1000000000
#define maxn 100010
#define M 20000010
using namespace std;
bool flag[maxn];
int n,m,T,root[maxn],lc[M],rc[M],sum[M],siz,num,head[maxn];
int sz[maxn],belong[maxn],R[maxn],val[maxn],dep[maxn],fa[maxn][20];
struct node{int to,pre;}e[maxn*2];
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
void build(int l,int r,int x,int &y,int v){
	y=++siz;
	sum[y]=sum[x]+1;
	if(l==r)return;
	lc[y]=lc[x];rc[y]=rc[x];
	int mid=(l+r)>>1;
	if(v<=mid)build(l,mid,lc[x],lc[y],v);
	else build(mid+1,r,rc[x],rc[y],v);
}
void dfs(int x,int father,int now){
	flag[x]=1;sz[x]=1;belong[x]=now;
	fa[x][0]=father;dep[x]=dep[father]+1;
	for(int i=1;i<20;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	build(1,INF,root[father],root[x],val[x]);
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father)continue;
		dfs(to,x,now);
		sz[x]+=sz[to];
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int i,t=dep[x]-dep[y];
	for(int i=0;i<20;i++)if(t&(1<<i))x=fa[x][i];
	for(int i=19;i>=0;i--)
		if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return x==y?x:fa[x][0];
}
int query(int l,int r,int x1,int x2,int x3,int x4,int k){
	if(l==r)return l;
	int now=sum[lc[x1]]+sum[lc[x2]]-sum[lc[x3]]-sum[lc[x4]];
	int mid=(l+r)>>1;
	if(now>=k)return query(l,mid,lc[x1],lc[x2],lc[x3],lc[x4],k);
	else return query(mid+1,r,rc[x1],rc[x2],rc[x3],rc[x4],k-now);
}
int main(){
	int x,y,tot=0,k,ans=0;
	scanf("%d%d%d%d",&T,&n,&m,&T);
	for(int i=1;i<=n;i++)scanf("%d",&val[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		Insert(x,y);Insert(y,x);
	}
	for(int i=1;i<=n;i++)
		if(!flag[i]){dfs(i,0,++tot);R[tot]=i;}
	char ch[5];
	while(T--){
		scanf("%s",ch);
		if(ch[0]=='Q'){
			scanf("%d%d%d",&x,&y,&k);
			x^=ans,y^=ans,k^=ans;
			int lca=LCA(x,y);
			ans=query(1,INF,root[x],root[y],root[lca],root[fa[lca][0]],k);
			printf("%d\n",ans);
		}
		else{
			scanf("%d%d",&x,&y);
			x^=ans;y^=ans;
			int now1=R[belong[x]],now2=R[belong[y]];
			if(sz[now1]>sz[now2])swap(now1,now2),swap(x,y);
			Insert(x,y);Insert(y,x);fa[x][0]=y;
			sz[now2]+=sz[now1];dep[x]=dep[y]+1;
			dfs(x,y,belong[y]);
		}
	}
	return 0;
}
