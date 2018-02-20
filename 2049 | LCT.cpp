#include<iostream>
#include<cstdio>
#define maxn 100010
using namespace std;
int st[maxn],c[maxn][2],fa[maxn],n,m;
bool rev[maxn];
bool isroot(int x){
	return (c[fa[x]][0]!=x)&&(c[fa[x]][1]!=x);
}
void pushdown(int x){
	if(rev[x]){
		rev[x]^=1;rev[c[x][0]]^=1;rev[c[x][1]]^=1;
		swap(c[x][0],c[x][1]);
	}
}
void rotate(int x){
	int y=fa[x],z=fa[fa[x]],l,r;
	if(c[y][0]==x)l=0;else l=1;r=l^1;
	if(!isroot(y))c[z][c[z][1]==y]=x;
	fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
	c[y][l]=c[x][r];c[x][r]=y;
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
	for(int t=0;x;x=fa[x])splay(x),c[x][1]=t,t=x;
}
void reroot(int x){
	access(x);splay(x);rev[x]^=1;
}
void link(int x,int y){
	reroot(x);fa[x]=y;splay(x);
}
void cut(int x,int y){
	reroot(x);
	access(y);splay(y);c[y][0]=fa[x]=0;
}
int find(int x){
	access(x);splay(x);
	while(c[x][0])x=c[x][0];
	return x;
}
int main(){
	scanf("%d%d",&n,&m);
	char s[10];int x,y;
	while(m--){
		scanf("%s%d%d",s,&x,&y);
		if(s[0]=='C')link(x,y);
		else if(s[0]=='D')cut(x,y);
		else{
			if(find(x)==find(y))puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
