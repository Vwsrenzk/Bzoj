/*
	假设当前神秘数为ans,则[1,ans-1]一定能用S集合中的数表示。
	然后ans从1开始，每次求小于ans的数的和get,ans变为get+1。
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
using namespace std;
int n,m,sz,mx;
int lc[maxn*40],rc[maxn*40],sum[maxn*40],root[maxn],a[maxn];
void build(int l,int r,int x,int &y,int v){
	y=++sz;
	sum[y]=sum[x]+v;
	if(l==r)return;
	int mid=(l+r)>>1;
	lc[y]=lc[x];rc[y]=rc[x];
	if(v<=mid)build(l,mid,lc[x],lc[y],v);
	else build(mid+1,r,rc[x],rc[y],v);
}
int query(int l,int r,int x,int y,int v){
	if(v>=r)return sum[y]-sum[x];
	int mid=(l+r)>>1;
	if(v<=mid)return query(l,mid,lc[x],lc[y],v);
	else return sum[lc[y]]-sum[lc[x]]+query(mid+1,r,rc[x],rc[y],v);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),mx=max(mx,a[i]);
	for(int i=1;i<=n;i++)build(1,mx,root[i-1],root[i],a[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int l,r,ans=1;
		scanf("%d%d",&l,&r);
		while(1){
			int sum=query(1,mx,root[l-1],root[r],ans);//求区间中小于等于ans的数的和 
			if(sum<ans)break;//说明有空 
			ans=sum+1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
