#include<iostream>
#include<cstdio>
#define maxn 300010
using namespace std;
int dep[maxn],dead[maxn],n,m,rt[maxn],ed[maxn],beg[maxn];
int num,head[maxn];
long long a[maxn],v[maxn],d[maxn];
struct node{
	int l,r;
	long long lc,lp,v;
	int dis;
}t[maxn];
struct Node{int to,pre;}e[maxn*2];
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
long long qread(){
	long long i=0,j=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
	return i*j;
}
void get(int r,long long mul,long long plu){//加标记 
	if(!r)return;
	t[r].v*=mul;t[r].v+=plu;
	t[r].lp*=mul;t[r].lc*=mul;t[r].lp+=plu;
}
void pushdown(int r){
	get(t[r].l,t[r].lc,t[r].lp);//下放 
	get(t[r].r,t[r].lc,t[r].lp);
	t[r].lc=1;t[r].lp=0;
}
int Merge(int r1,int r2){//合并以r1和r2为根的两个堆 
	if(r1==0||r2==0)return r1+r2;
	pushdown(r1);pushdown(r2);
	if(t[r1].v>t[r2].v)swap(r1,r2);//保证r1.v<r2.v,将r2合并到r1下面 
	t[r1].r=Merge(t[r1].r,r2);
	if(t[t[r1].l].dis<t[t[r1].r].dis)swap(t[r1].l,t[r1].r);
	t[r1].dis=t[t[r1].r].dis+1;
	return r1;
}
int pop(int r){
	return Merge(t[r].l,t[r].r);
}
void dfs(int x,int father){
	dep[x]=dep[father]+1;
	for(int i=head[x];i;i=e[i].pre)
		dfs(e[i].to,x);
	for(int i=head[x];i;i=e[i].pre)
		rt[x]=Merge(rt[x],rt[e[i].to]);
	while(rt[x]&&t[rt[x]].v<d[x]){
		pushdown(rt[x]);
		dead[x]++;
		ed[rt[x]]=x;
		rt[x]=pop(rt[x]);
	}
	if(!a[x])get(rt[x],1,v[x]);
	else get(rt[x],v[x],0);
}
int main(){
	n=qread();m=qread();
	for(int i=1;i<=n;i++)d[i]=qread();
	for(int i=2;i<=n;i++){
		int x=qread();
		Insert(x,i);
		a[i]=qread();v[i]=qread();
	}
	for(int i=1;i<=m;i++)t[i].lp=0,t[i].lc=1;
	for(int i=1;i<=m;i++){
		t[i].v=qread();beg[i]=qread();
		rt[beg[i]]=Merge(rt[beg[i]],i);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)printf("%d\n",dead[i]);
	for(int i=1;i<=m;i++)printf("%d\n",dep[beg[i]]-dep[ed[i]]);
	return 0;
}
