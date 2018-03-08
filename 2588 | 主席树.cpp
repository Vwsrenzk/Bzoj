#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
using namespace std;
int num,n,m,sz,cnt;
int val[maxn],sum[maxn*40],lc[maxn*40],rc[maxn*40],root[maxn],a[maxn],b[maxn];
int fa[maxn][20],dep[maxn],head[maxn];
struct node{int to,pre;}e[maxn*2];
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
void build(int l,int r,int x,int &y,int v){
	y=++sz;
	if(l==r){
		sum[y]=sum[x]+1;
		return;
	}
	int mid=(l+r)>>1;
	lc[y]=lc[x];rc[y]=rc[x];
	if(v<=mid)build(l,mid,lc[x],lc[y],v);
	else build(mid+1,r,rc[x],rc[y],v);
	sum[y]=sum[lc[y]]+sum[rc[y]];
}
void dfs(int x,int father){
	dep[x]=dep[father]+1;
	fa[x][0]=father;
	build(1,cnt,root[father],root[x],a[x]);
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father)continue;
		dfs(to,x);
	}
}
void prepare(){
	for(int j=1;j<=18;j++)
		for(int i=1;i<=n;i++)
		fa[i][j]=fa[fa[i][j-1]][j-1];
}
int get(int x,int delta){
	for(int i=18;i>=0;i--)
		if(delta&(1<<i))x=fa[x][i];
	return x;
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	x=get(x,dep[x]-dep[y]);
	for(int i=18;i>=0;i--){
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	}
	if(x!=y)return fa[x][0];
	return x;
}
int query(int l,int r,int a,int b,int A,int B,int k){
	int tmp=sum[lc[a]]+sum[lc[b]]-sum[lc[A]]-sum[lc[B]];
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(k<=tmp)return query(l,mid,lc[a],lc[b],lc[A],lc[B],k);
	else return query(mid+1,r,rc[a],rc[b],rc[A],rc[B],k-tmp);
}
int main(){
	int ans=0,x,y,k;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	cnt=unique(b+1,b+n+1)-(b+1);
	for(int i=1;i<=n;i++){
		int tmp=lower_bound(b+1,b+cnt+1,a[i])-b;
		val[tmp]=a[i];a[i]=tmp;
	}
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		Insert(x,y);Insert(y,x);
	}
	dfs(1,0);prepare();
	while(m--){
		scanf("%d%d%d",&x,&y,&k);
		x=x^ans;
		int lca=LCA(x,y);
		ans=val[query(1,cnt,root[x],root[y],root[lca],root[fa[lca][0]],k)];
		if(m==0)printf("%d",ans);
		else printf("%d\n",ans);
	}
	return 0;
}
