/*注意long double的输入要用%Lf*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define eps 1e-7
using namespace std;
struct node{
	long double t[510];int w;
	bool operator < (const node b) const {
		return w<b.w;
	}
}a[510],p[510];
int n,m;
bool vis[510];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%Lf",&a[i].t[j]);
	for(int i=1;i<=n;i++)scanf("%d",&a[i].w);
	sort(a+1,a+n+1);
	int cnt=0,res=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(fabs(a[i].t[j])>=eps){
				if(!vis[j]){
					vis[j]=1;
					p[j]=a[i];
					res+=a[i].w;
					cnt++;
					break;
				}
				else{
					long double x=a[i].t[j]/p[j].t[j];
					for(int k=1;k<=m;k++)a[i].t[k]-=x*p[j].t[k];
				}
			}
	printf("%d %d",cnt,res);
	return 0;
}
