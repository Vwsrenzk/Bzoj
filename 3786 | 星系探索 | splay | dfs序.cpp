#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 200100
using namespace std;
int n,q,rt,top,num,tot;
int a[maxn],sta[maxn],head[maxn],fa[maxn],w[maxn],v[maxn],tag[maxn];
int c[maxn][2],t[maxn][2],s[maxn][2];
long long sum[maxn];
struct node{int to,pre;}e[maxn*2];
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
void dfs(int x){
	v[t[x][0]=++tot]=a[x];w[tot]=1;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(!t[to][0])dfs(to);
	}
	v[t[x][1]=++tot]=-a[x];w[tot]=-1;
}
void update(int k,long long z){
	if(!k)return;
	sum[k]+=1LL*(s[k][0]-s[k][1])*z;
	v[k]+=w[k]*z;
	tag[k]+=z;
}
void pushup(int k){
	if(!k)return;
	int l=c[k][0],r=c[k][1];
	s[k][0]=s[l][0]+s[r][0]+(w[k]==1);
	s[k][1]=s[l][1]+s[r][1]+(w[k]==-1);
	sum[k]=sum[l]+sum[r]+v[k];
}
void pushdown(int k){
	if(!k)return;
	if(!tag[k])return;
	update(c[k][0],tag[k]);
	update(c[k][1],tag[k]);
	tag[k]=0;
}
void build(int k,int l,int r){
	if(l>r)return;
	int mid=(l+r)>>1;
	fa[mid]=k;c[k][mid>k]=mid;
	if(l==r){sum[mid]=v[mid];s[mid][0]=(w[mid]==1);s[mid][1]=1-s[mid][0];return;}
	build(mid,l,mid-1);build(mid,mid+1,r);
	pushup(mid);
}
void rotate(int x,int &k){
	int y=fa[x],z=fa[fa[x]],l,r;
	if(c[y][1]==x)l=1;else l=0;r=l^1;
	if(y!=k)c[z][c[z][1]==y]=x;else k=x;
	fa[x]=z;fa[y]=x;fa[c[x][r]]=y;
	c[y][l]=c[x][r];c[x][r]=y;
	pushup(y);pushup(x);
} 
void splay(int x,int &k){
	top=0;
	for(int i=x;i;i=fa[i])sta[++top]=i;
	for(int i=top;i;i--)pushdown(sta[i]);
	while(x!=k){
		int y=fa[x],z=fa[fa[x]];
		if(y!=k){
			if((c[z][0]==y)^(c[y][0]==x))rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
int findmn(int x){
	while(c[x][0])x=c[x][0];
	return x;
}
int findmx(int x){
	while(c[x][1])x=c[x][1];
	return x;
}
void split(int x,int y){
	splay(x,rt);
	int t1=findmx(c[x][0]);
	splay(y,rt);
	int t2=findmn(c[y][1]);
	splay(t1,rt);
	splay(t2,c[t1][1]);
}
int main(){
	scanf("%d",&n);int x,y,z;
	for(int i=2;i<=n;i++){
		scanf("%d",&x);
		Insert(i,x);Insert(x,i);
	}
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	tot=1;dfs(1);
	build(0,1,2*n+2);
	rt=n+1;
	scanf("%d",&q);
	while(q--){
		char ch[5];
		scanf("%s",ch);
		if(ch[0]=='Q'){//计算x到根的权值和 
			scanf("%d",&x);
			splay(t[1][0],rt);splay(t[x][0],c[rt][1]);
			printf("%lld\n",sum[c[c[rt][1]][0]]+v[rt]+v[c[rt][1]]);
		}
		else if(ch[0]=='F'){//将x的父亲变成y 
			scanf("%d%d",&x,&y);
			splay(t[x][0],rt);splay(t[x][1],c[rt][1]);
			z=c[rt][1];
			v[rt]+=w[rt]*y;v[z]+=w[z]*y;
			update(c[z][0],y);
			pushup(z);pushup(rt);
		}
		else{//x的子树加上y 
			scanf("%d%d",&x,&y);
			split(t[x][0],t[x][1]);
			z=c[rt][1];
			int tmp=c[z][0];c[z][0]=0;
			pushup(z);pushup(rt);
			splay(t[y][0],rt);
			splay(findmn(c[rt][1]),c[rt][1]);
			z=c[rt][1];c[z][0]=tmp;
			fa[tmp]=z;
			pushup(z);pushup(rt);
		}
	}
}
