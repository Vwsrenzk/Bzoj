#include<iostream>
#include<cstdio>
#define maxn 100010
using namespace std;
int n,m,tot,ans[maxn];
long long c[maxn][2];
bool flag[maxn];
struct node{int k,x,y,z,id;}a[maxn],b[maxn];
void add(int k,int x,int delta){
	while(x<=tot){
		c[x][k]+=delta;
		x+=(x&-x);
	}
}
long long getsum(int k,int x){
	long long res=0;
	while(x){
		res+=c[x][k];
		x-=(x&-x);
	}
	return res;
}
void modify(int x,int y,int z){
	add(0,x,z);
	add(1,x,z*(x-1));
	add(0,y+1,-z);
	add(1,y+1,-z*y);
}
long long query(int x,int y){
	return getsum(0,y)*y-getsum(1,y)-getsum(0,x-1)*(x-1)+getsum(1,x-1);
}
void solve(int x,int y,int l,int r){
	int j=x,k=x,mid=(l+r)>>1;
	if(l==r){
		for(int i=x;i<=y;i++)if(a[i].k)ans[a[i].id]=l;
		return;
	} 
	for(int i=x;i<=y;i++){
		if(a[i].k){
			long long tmp=query(a[i].x,a[i].y);
			if(tmp<a[i].z){
				flag[i]=0;
				a[i].z-=(int)tmp;
			}
			else {flag[i]=1;k++;}
		}
		else if(a[i].z<=mid){
			modify(a[i].x,a[i].y,1);
			flag[i]=1;k++;
		}
		else flag[i]=0;
	}
	for(int i=x;i<=y;i++)
		if(!a[i].k&&a[i].z<=mid)modify(a[i].x,a[i].y,-1);
	for(int i=x;i<=y;i++)
		if(flag[i])b[j++]=a[i];
		else b[k++]=a[i];
	for(int i=x;i<=y;i++)a[i]=b[i];
	solve(x,j-1,l,mid);
	solve(j,y,mid+1,r);
}
int main(){
	scanf("%d%d",&n,&m);int cnt=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&a[i].k,&a[i].x,&a[i].y,&a[i].z);
		a[i].k--;//操作类型 
		if(a[i].k)a[i].id=++cnt;
		else {
			a[i].z=n-a[i].z+1;
			tot=max(tot,a[i].z);
		}
	}
	solve(1,m,1,tot);
	for(int i=1;i<=cnt;i++)printf("%d\n",n-ans[i]+1);
	return 0;
}
