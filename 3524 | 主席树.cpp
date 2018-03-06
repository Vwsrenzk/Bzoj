#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 500010
using namespace std;
int a[maxn],root[maxn*20],lc[maxn*20],rc[maxn*20],sum[maxn*20],tot,n,m;
void build(int l,int r,int x,int &y,int v){
	y=++tot;
	sum[y]=sum[x]+1;
	if(l==r)return;
	int mid=(l+r)>>1;
	lc[y]=lc[x];rc[y]=rc[x];
	if(v<=mid)build(l,mid,lc[x],lc[y],v);
	else build(mid+1,r,rc[x],rc[y],v);
}
int find(int x,int y){
	int l=1,r=n;
	int tmp=(y-x+1)/2;
	x=root[x-1];y=root[y];
	while(l!=r){
		if(sum[y]-sum[x]<tmp)return 0;
		int mid=(l+r)>>1;
		if(sum[lc[y]]-sum[lc[x]]>tmp){
			r=mid;x=lc[x];y=lc[y];
		}
		else if(sum[rc[y]]-sum[rc[x]]>tmp){
			l=mid+1;x=rc[x];y=rc[y];
		}
		else return 0;
	}
	return l;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		build(1,n,root[i-1],root[i],a[i]);
	}
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		printf("%d\n",find(x,y));
	}
}
