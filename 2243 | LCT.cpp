#include<iostream>
#include<cstdio>
#define maxn 200010
using namespace std;
int lc[maxn],rc[maxn],sum[maxn],c[maxn][2],v[maxn],fa[maxn],st[maxn];
bool rev[maxn],mark[maxn];
char ch[5];
bool isroot(int x){
	return (c[fa[x]][1]!=x)&&(c[fa[x]][0]!=x);
}
void update(int x,int c){
	if(!x)return;
	mark[x]=1;sum[x]=1;
	lc[x]=rc[x]=v[x]=c;
}
void pushup(int x){
	int l=c[x][0],r=c[x][1];
	sum[x]=sum[l]+sum[r]+1;
	if(l){if(rc[l]==v[x])sum[x]--;lc[x]=lc[l];}else lc[x]=v[x];
	if(r){if(lc[r]==v[x])sum[x]--;rc[x]=rc[r];}else rc[x]=v[x];
}
void Flip(int x){
	rev[x]^=1;int l=c[x][0],r=c[x][1];
	swap(lc[l],rc[l]);swap(lc[r],rc[r]);
}
void pushdown(int x){
	int l=c[x][0],r=c[x][1];
	if(rev[x]){
		rev[x]^=1;
		Flip(l);Flip(r);
		swap(c[x][0],c[x][1]);
	}
	if(mark[x]){
		mark[x]=0;
		update(l,v[x]);update(r,v[x]);
	}
}
void rotate(int x){
	int y=fa[x],z=fa[fa[x]],l,r;
	if(c[y][0]==x)l=0;else l=1;r=l^1;
	if(!isroot(y))c[z][c[z][1]==y]=x;
	fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
	c[y][l]=c[x][r];c[x][r]=y;
	pushup(y);pushup(x);
}
void splay(int x){
	int top=0;st[++top]=x;
	for(int i=x;!isroot(i);i=fa[i])st[++top]=fa[i];
	for(int i=top;i;i--)pushdown(st[i]);
	while(!isroot(x)){
		int y=fa[x],z=fa[fa[x]];
		if(!isroot(y)){
			if((c[y][0]==x)^(c[z][0]==y))rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x){
	for(int t=0;x;x=fa[x]){splay(x);c[x][1]=t;pushup(x);t=x;}
}
void reroot(int x){
	access(x);splay(x);rev[x]^=1;
}
void split(int x,int y){
	reroot(y);access(x);splay(x);
}
void link(int x,int y){
	reroot(x);fa[x]=y;
}
int main(){
	int n,m,x,y,z;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){scanf("%d",&x);lc[i]=rc[i]=v[i]=x;}
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		link(x,y);
	}
	for(int i=1;i<=m;i++){
		scanf("%s",ch);
		if(ch[0]=='Q'){
			scanf("%d%d",&x,&y);
			split(x,y);printf("%d\n",sum[x]);
		}
		else{
			scanf("%d%d%d",&x,&y,&z);
			split(x,y);update(x,z);
		}
	}
}
