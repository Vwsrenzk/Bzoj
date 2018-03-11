#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 200010
#define INF 1000000000
using namespace std;
int fa[maxn],son[maxn][2],val[maxn],mx[maxn],rev[maxn],st[maxn];
int p[maxn],n,m,ans=INF;
struct node{int u,v,a,b;}e[maxn];
bool cmp(node x,node y){return x.a<y.a;}
bool isroot(int x){
	return (son[fa[x]][0]!=x)&&(son[fa[x]][1]!=x);
}
int find(int x){
	if(p[x]==x)return x;
	return p[x]=find(p[x]);
}
void pushup(int x){
	int l=son[x][0],r=son[x][1];
	mx[x]=x;
	if(val[mx[l]]>val[mx[x]])mx[x]=mx[l];
	if(val[mx[r]]>val[mx[x]])mx[x]=mx[r];
}
void pushdown(int x){
	if(rev[x]){
		rev[x]^=1;
		swap(son[x][1],son[x][0]);
		rev[son[x][1]]^=1;rev[son[x][0]]^=1;
	}
}
void rotate(int x){
	int y=fa[x],z=fa[fa[x]],l,r;
	if(son[y][0]==x)l=0;else l=1;r=l^1;
	if(!isroot(y))son[z][son[z][1]==y]=x;
	fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
	son[y][l]=son[x][r];son[x][r]=y;
	pushup(y);pushup(x);
}
void splay(int x){
	int top=0;st[++top]=x;
	for(int i=x;!isroot(i);i=fa[i])st[++top]=fa[i];
	for(int i=top;i;i--)pushdown(st[i]);
	while(!isroot(x)){
		int y=fa[x],z=fa[fa[x]];
		if(!isroot(y)){
			if((son[y][0]==x)^(son[z][0]==y))rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x){
	for(int t=0;x;x=fa[x]){splay(x);son[x][1]=t;pushup(x);t=x;}
}
void reroot(int x){
	access(x);splay(x);rev[x]^=1;
}
int query(int x,int y){
	reroot(x);access(y);splay(y);
	return mx[y];
}
void cut(int x,int y){
	reroot(x);
	access(y);
	splay(y);
	fa[x]=son[y][0]=0;
	pushup(y);
}
void join(int x,int y){
	reroot(x);fa[x]=y;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].a,&e[i].b);
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=n;i++)p[i]=i;
	for(int i=1;i<=m;i++){
		int u=e[i].u,v=e[i].v,a=e[i].a,b=e[i].b;
		if(find(u)==find(v)){
			int t=query(u,v);
			if(val[t]>e[i].b){
				cut(t,e[t-n].u);
				cut(t,e[t-n].v);
			}
			else{
				if(find(1)==find(n))
					ans=min(ans,e[i].a+val[query(1,n)]);
				continue;
			}
		}
		else p[find(u)]=find(v);
		val[i+n]=e[i].b;mx[i+n]=n+i;
		join(i+n,e[i].u);join(i+n,e[i].v);
		if(find(1)==find(n))ans=min(ans,e[i].a+val[query(1,n)]);
	}
	if(find(1)==find(n))printf("%d",ans);
	else puts("-1");
	return 0;
}
