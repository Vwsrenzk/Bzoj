/*注意access时要update*/
#include<iostream>
#include<cstdio>
#define maxn 3000010
using namespace std;
int n,q,v[maxn],w[maxn],st[maxn],fa[maxn],c[maxn][2];
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
void update(int x){
	v[x]=v[c[x][0]]+v[c[x][1]]+w[x];
}
void rotate(int x){
	int y=fa[x],z=fa[fa[x]],l,r;
	if(c[y][0]==x)l=0;else l=1;r=l^1;
	if(!isroot(y))c[z][c[z][1]==y]=x;
	fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
	c[y][l]=c[x][r];c[x][r]=y;
	update(y),update(x);
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
	for(int t=0;x;x=fa[x])splay(x),c[x][1]=t,t=x,update(x);
}
void reroot(int x){
	access(x);splay(x);rev[x]^=1;
}
int find(int x){
	access(x);splay(x);
	while(c[x][0])x=c[x][0];
	return x;
}
void link(int x,int y){
	reroot(x);fa[x]=y;splay(x);
}
int main(){
	scanf("%d",&n);
	int x,y;char s[15];
	for(int i=1;i<=n;i++)scanf("%d",&w[i]),v[i]=w[i];
	scanf("%d",&q);
	while(q--){
		scanf("%s%d%d",s,&x,&y);
		if(s[0]=='b'){
			if(find(x)==find(y))puts("no");
			else {
				puts("yes");
				link(x,y);
			}
		}
		if(s[0]=='p'){
			splay(x);w[x]=y;update(x);
		}
		if(s[0]=='e'){
			if(find(x)==find(y)){
				reroot(x);
				access(y);
				splay(y);
				printf("%d\n",v[y]);
			}
			else puts("impossible");
		}
	}
	return 0;
}
