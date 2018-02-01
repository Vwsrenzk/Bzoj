/*
	题目大意：
		一个有n个结点的树，设它的结点分别为v1, v2, …, vn，已知第i个结点vi的度数为di，问满足这样的条件的不同的树有多少棵。给定n，d1, d2, …, dn，编程需要输出满足d(vi)=di的树的个数。 
	题解：
		purfer数列+质因数分解 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 160
using namespace std;
int n,d[maxn],num,p[maxn],tot[maxn];
long long ans=1;
bool vis[maxn];
void prepare(){
	for(int i=2;i<=n;i++){
		if(!vis[i])p[++num]=i;
		for(int j=1;j<=num&&i*p[j]<=n;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
void add(int x,int delta){
	for(int i=1;i<=num;i++){
		if(x==1)return;
		while(x%p[i]==0){
			x/=p[i];
			tot[i]+=delta;
		}
	}
}
long long Pow(long long x,long long y){
	long long res=1;
	while(y){
		if(y&1)res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
int main(){
	scanf("%d",&n);
	int sum=0;
	for(int i=1;i<=n;i++)scanf("%d",&d[i]),sum+=d[i]-1;
	if(sum!=n-2){puts("0");return 0;}
	if(n==1&&!d[1]){puts("1");return 0;}
	for(int i=1;i<=n;i++)
		if(!d[i]){puts("0");return 0;}
	prepare();
	for(int i=2;i<=n-2;i++)add(i,1);
	for(int i=1;i<=n;i++)
		for(int j=2;j<=d[i]-1;j++)add(j,-1);
	for(int i=num;i>=1;i--){
		if(tot[i]>0)ans*=Pow(p[i],tot[i]);
		if(tot[i]<0)ans/=Pow(p[i],tot[i]);
	}
	cout<<ans;
	return 0;
}
