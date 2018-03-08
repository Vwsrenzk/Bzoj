#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 300010
using namespace std;
int tot,lim,num,n,m,root[maxn*2],lc[maxn*40],rc[maxn*40],to[maxn*2];
long long sum[maxn*40],w[maxn*40];
struct node{int pos,v;}e[maxn*2];
bool cmp(node x,node y){return x.pos<y.pos;}
void update(int x){
	w[x]=w[lc[x]]+w[rc[x]];
	sum[x]=sum[lc[x]]+sum[rc[x]];
}
void build(int l,int r,int x,int &y,int v){
	y=++tot;
	if(l==r){
		if(v>0)w[y]=w[x]+1;
		else w[y]=w[x]-1;
		sum[y]=sum[x]+v;
		return;
	}
	int mid=(l+r)>>1;
	lc[y]=lc[x];rc[y]=rc[x];
	if(abs(v)<=mid)build(l,mid,lc[x],lc[y],v);
	else build(mid+1,r,rc[x],rc[y],v);
	update(y);
}
long long query(int R,int k){
	int x=root[R],l=1,r=lim;
	if(w[x]<=k)return sum[x];
	long long ans=0;
	while(l<r){
		int mid=(l+r)>>1;
		if(w[lc[x]]>=k){
			r=mid;
			x=lc[x];
		}
		else{
			l=mid+1;
			ans+=sum[lc[x]];
			k-=w[lc[x]];
			x=rc[x];
		}
		if(l>=r)return ans+sum[x]/w[x]*k;
	}
	return ans;
}
int main(){
	scanf("%d%d",&n,&m);
	int s,t,w;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&s,&t,&w);
		e[++num].pos=s;e[num].v=w;
		e[++num].pos=t+1;e[num].v=-w;
		lim=max(lim,w);
	}
	sort(e+1,e+num+1,cmp);
	for(int i=1;i<=num;i++)build(1,lim,root[i-1],root[i],e[i].v);
	for(int i=num;i>=1;i--)
		if(e[i].pos!=e[i+1].pos)to[e[i].pos]=i;
	for(int i=1;i<=n;i++){if(!to[i])to[i]=to[i-1];}
	int x,a,b,c;
	long long pre=1,k;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&x,&a,&b,&c);
		k=(1LL*a*pre+b)%c+1;
		pre=query(to[x],k);
		printf("%lld\n",pre);
	}
	return 0;
}
