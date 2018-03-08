#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 20010
using namespace std;
int n,m,a,b,c,d,sz,q[5];
int lc[maxn*40],rc[maxn*40],lmx[maxn*40],rmx[maxn*40],sum[maxn*40],root[maxn];
struct node{
	int id,val;
	bool operator < (const node x)const{
		return val<x.val;
	}
}s[maxn];
void update(int x){
	sum[x]=sum[lc[x]]+sum[rc[x]];
	lmx[x]=max(lmx[lc[x]],sum[lc[x]]+lmx[rc[x]]);
	rmx[x]=max(rmx[rc[x]],sum[rc[x]]+rmx[lc[x]]);
}
void build(int &x,int l,int r){
	x=++sz;
	if(l==r){
		sum[x]=lmx[x]=rmx[x]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(lc[x],l,mid);
	build(rc[x],mid+1,r);
	update(x);
}
void change(int l,int r,int x,int &y,int id){
	y=++sz;
	sum[y]=sum[x];
	if(l==r){
		sum[y]=-1;lmx[y]=rmx[y]=0;
		return;
	}
	int mid=(l+r)>>1;
	lc[y]=lc[x];rc[y]=rc[x];
	if(id<=mid)change(l,mid,lc[x],lc[y],id);
	else change(mid+1,r,rc[x],rc[y],id);
	update(y);
}
int query_s(int k,int l,int r,int opl,int opr){
	if(opl>opr)return 0;
	if(l>=opl&&r<=opr)return sum[k];
	int mid=(l+r)>>1;int ans=0;
	if(opl<=mid)ans+=query_s(lc[k],l,mid,opl,opr);
	if(opr>mid)ans+=query_s(rc[k],mid+1,r,opl,opr);
	return ans;
}
int query_r(int k,int l,int r,int opl,int opr){
	if(opl>opr)return 0;
	if(l>=opl&&r<=opr)return rmx[k];
	int mid=(l+r)>>1;
	int ans=0;
	if(opr>mid)ans=query_r(rc[k],mid+1,r,opl,opr);
	if(opl<=mid){
		int lmax=query_r(lc[k],l,mid,opl,opr);
		int rsum=query_s(rc[k],mid+1,r,mid+1,opr);
		ans=max(ans,lmax+rsum);
	}
	return ans;
}
int query_l(int k,int l,int r,int opl,int opr){
	if(opl>opr)return 0;
	if(l>=opl&&r<=opr)return lmx[k];
	int mid=(l+r)>>1;
	int ans=0;
	if(opl<=mid)ans=query_l(lc[k],l,mid,opl,opr);
	if(opr>mid){
		int rmax=query_l(rc[k],mid+1,r,opl,opr);
		int lsum=query_s(lc[k],l,mid,opl,mid);
		ans=max(ans,rmax+lsum);
	}
	return ans;
}
bool check(int x){
	int ab=query_r(root[x],1,n,a,b-1);
	int cd=query_l(root[x],1,n,c+1,d);
	int bc=query_s(root[x],1,n,b,c);
	return ab+cd+bc>=0;
}
int solve(){
	int l=1,r=n,mid,ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&s[i].val);
		s[i].id=i;
	}
	sort(s+1,s+n+1);
	build(root[1],1,n);
	for(int i=2;i<=n;i++)
		change(1,n,root[i-1],root[i],s[i-1].id);
	int Q;scanf("%d",&Q);
	int ans=0;
	while(Q--){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		q[1]=(a+ans)%n+1;q[2]=(b+ans)%n+1;
		q[3]=(c+ans)%n+1;q[4]=(d+ans)%n+1;
		sort(q+1,q+5);
		a=q[1];b=q[2];c=q[3];d=q[4];
		ans=s[solve()].val;
		printf("%d\n",ans);
	}
	return 0;
}
