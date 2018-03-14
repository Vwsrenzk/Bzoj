#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define maxn 100010
#define mod 100003
using namespace std;
int a[maxn],f[maxn],g[maxn],inv[maxn],p[maxn];
vector<int>v[maxn];
int n,m,k,tot;
int Pow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1LL*x*res%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}
int main(){
	int ans;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		if(!inv[i]){
			inv[i]=Pow(i,mod-2);
			p[++tot]=i;
		}
		for(int j=1;j<=tot&&i*p[j]<=n;j++){
			inv[i*p[j]]=1LL*inv[i]*inv[p[j]]%mod;
			if(i%p[j]==0)break;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=i)
			v[j].push_back(i);
	for(int i=n;i>=1;i--)
		if(a[i]){m++;for(int j=0;j<v[i].size();j++)a[v[i][j]]^=1;}
	g[n]=1;
	for(int i=1;i<=k;i++)g[i]=1;
	for(int i=n-1;i>k;i--)g[i]=(1LL*g[i+1]*(n-i)%mod*inv[i]+1LL*n*inv[i])%mod;
	for(int i=1;i<=k;i++)f[i]=i;
	for(int i=k+1;i<=m;i++)f[i]=f[i-1]+g[i];
	ans=f[m];
	for(int i=1;i<=n;i++)ans=1LL*ans*i%mod;
	printf("%d\n",ans);
	return 0;
}
