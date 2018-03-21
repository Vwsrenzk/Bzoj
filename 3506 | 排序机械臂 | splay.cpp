#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
using namespace std;
int n,root,sz,size[maxn],fa[maxn],c[maxn][2],val[maxn],rev[maxn];
int top,st[maxn];
struct node{int v,id,pos;}a[maxn];
bool cmp1(node a,node b){
	if(a.v!=b.v)return a.v<b.v;
	return a.pos<b.pos;
}
bool cmp2(node a,node b){
	return a.pos<b.pos;
}
void update(int x){
	size[x]=size[c[x][0]]+size[c[x][1]]+1;
}
void pushdown(int x){
	if(rev[x]){
		int l=c[x][0],r=c[x][1];
		swap(c[x][0],c[x][1]);
		rev[l]^=1;rev[r]^=1;
		rev[x]=0;
	}
}
void rotate(int x,int &k){
	int y=fa[x],z=fa[fa[x]],l,r;
	if(c[y][0]==x)l=0;else l=1;r=l^1;
	if(y!=k)c[z][c[z][1]==y]=x;
	else k=x;
	fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
	c[y][l]=c[x][r];c[x][r]=y;
	update(y);update(x);
}
void splay(int x,int &k){
	top=0;
	for(int i=x;fa[i];i=fa[i])st[++top]=i;
	for(int i=top;i>=1;i--)pushdown(st[i]);
	while(x!=k){
		int y=fa[x],z=fa[fa[x]];
		if(y!=k){
			if((c[z][0]==y)^(c[y][0]==x))rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
int find(int x,int rk){
	if(!x)return 0;
	pushdown(x);
	if(rk==size[c[x][0]]+1)return x;
	else if(rk<=size[c[x][0]])return find(c[x][0],rk);
	else return find(c[x][1],rk-size[c[x][0]]-1);
}
void solve(int k){
	splay(k,root);
	printf("%d",size[c[root][0]]);
	if(k!=n+1)printf(" ");
	int x=find(root,k-1),y=find(root,size[c[root][0]]+2);
	splay(x,root);splay(y,c[x][1]);
	rev[c[y][0]]^=1;
}
void build(int l,int r,int f){
	if(l>r)return;
	int now=a[l].id,last=a[f].id;
	if(l==r){
		fa[now]=last;
		size[now]=1;
		if(l<f)c[last][0]=now;
		else c[last][1]=now;
	}
	else {
		int mid=(l+r)>>1;
		now=a[mid].id;
		build(l,mid-1,mid);build(mid+1,r,mid);
		fa[now]=last;
		update(now);
		if(mid<f)c[last][0]=now;
		else c[last][1]=now;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i+1].v);
		a[i+1].v++;
		a[i+1].pos=i;
	}
	sort(a+2,a+n+2,cmp1);
	for(int i=2;i<=n+1;i++)a[i].id=i;
	a[1].id=1;a[n+2].id=n+2;
	sort(a+2,a+n+2,cmp2);
	build(1,n+2,0);
	root=a[(n+3)>>1].id;
	for(int i=1;i<=n;i++)solve(i+1);
	return 0;
}
