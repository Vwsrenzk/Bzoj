#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 200010
using namespace std;
int n,m,nxt[maxn],fa[maxn],c[maxn][2],sz[maxn],st[maxn];
bool rev[maxn];
bool isroot(int x){
	return (c[fa[x]][0]!=x)&&(c[fa[x]][1]!=x);
}
void pushdown(int x){
	if(rev[x]){
		rev[x]^=1;rev[c[x][1]]^=1;rev[c[x][0]]^=1;
		swap(c[x][0],c[x][1]);
	}
}
void update(int x){
	sz[x]=sz[c[x][0]]+sz[c[x][1]]+1;
}
void rotate(int x){
	int y=fa[x],z=fa[fa[x]],l,r;
	if(c[y][0]==x)l=0;else l=1;r=l^1;
	if(!isroot(y))c[z][c[z][1]==y]=x;
	fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
	c[y][l]=c[x][r];c[x][r]=y;
	update(y);
}
void splay(int x){
	int top=0;st[++top]=x;
	for(int i=x;!isroot(i);i=fa[i])st[++top]=fa[i];
	for(int i=top;i;i--)pushdown(st[i]);
	while(!isroot(x)){
		int y=fa[x],z=fa[fa[x]];
		if(!isroot(y)){
			if((c[y][0]==x)^(c[z][0]==y))rotate(x);
			rotate(y);
		}
		rotate(x);
		update(x);
	}
}
void access(int x){
	for(int t=0;x;x=fa[x])splay(x),c[x][1]=t,t=x;
}
void reroot(int x){
	access(x);splay(x);rev[x]^=1;
}
void link(int x,int y){
	reroot(x);fa[x]=y;splay(x);
}
void cut(int x,int y){
	reroot(y);access(x);splay(x);c[x][0]=fa[y]=0;
}
int main(){
	scanf("%d",&n);
	int op,x,y;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		int t=x+i;
		if(t>n+1)t=n+1;
		sz[i]=1;
		fa[i]=nxt[i]=t;
	}
	sz[n+1]=1;
	scanf("%d",&m);
	while(m--){
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&x);x++;
			reroot(n+1);access(x);splay(x);
			printf("%d\n",sz[c[x][0]]);
		}
		else{
			scanf("%d%d",&x,&y);x++;
			y=x+y;
			if(y>n+1)y=n+1;
			cut(x,nxt[x]);link(x,y);nxt[x]=y;
		}
	}
}
