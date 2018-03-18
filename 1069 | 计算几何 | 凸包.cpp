#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 2010
using namespace std;
int n,r,p1,p2,q[maxn];
double ans;
struct node{
	double x,y;
	bool operator < (const node &b)const{
		if(x!=b.x)return x<b.x;
		else return y<b.y;
	}
	node operator - (const node &b)const{
		return (node){x-b.x,y-b.y};
	}
	double operator * (const node &b)const{
		return x*b.y-y*b.x;
	}
}a[maxn];
double cross(int x,int y,int z){
	return (a[x]-a[y])*(a[z]-a[y]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf%lf",&a[i].x,&a[i].y);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		while(r>1&&cross(q[r],q[r-1],i)>=0)r--;
		q[++r]=i;
	}
	int rr=r;
	for(int i=n-1;i>=1;i--){
		while(r>rr&&cross(q[r],q[r-1],i)>=0)r--;
		q[++r]=i;
	}
	for(int i=1;i<r;i++){
		int p1=i+1,p2=i+3;
		for(int j=i+2;j<r-1;j++){
			while(p1<j-1&&cross(q[j],q[i],q[p1])<=cross(q[j],q[i],q[p1+1]))p1++;
			while(p2<=j||(p2<r-1&&cross(q[p2],q[i],q[j])<=cross(q[p2+1],q[i],q[j])))p2++;
			ans=max(ans,cross(q[j],q[i],q[p1])+cross(q[p2],q[i],q[j]));
		}
	}
	printf("%.3lf",ans/2);
	return 0;
}
