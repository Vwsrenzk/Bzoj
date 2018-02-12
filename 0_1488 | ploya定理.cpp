#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 65
#define mod 997
using namespace std;
int n,now,ans,dvd;
int a[maxn],b[maxn],mul[maxn],inv[maxn],t[maxn][maxn],mi[1800],f[maxn],c[maxn][maxn];
int Pow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}
int gcd(int x,int y){
	if(y==0)return x;
	return gcd(y,x%y);
}
void prepare(){
	mul[0]=1;
	for(int i=1;i<=n;i++)mul[i]=mul[i-1]*i%mod;
	mi[0]=1;
	for(int i=1;i<=n*(n-1)/2;i++)mi[i]=mi[i-1]*2%mod;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)t[i][j]=gcd(i,j);
	for(int i=1;i<=n;i++)inv[i]=Pow(mul[i],mod-2);
	for(int i=0;i<=n;i++)c[i][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
}
void dfs(int dep){
	if(!dep){
		int sum=0;
		for(int i=1;i<=now;i++)
			for(int j=i+1;j<=now;j++)
			sum+=t[a[i]][a[j]];
		for(int i=1;i<=now;i++)sum+=a[i]/2;
		int cnt=n,tot=1;
		for(int i=1;i<now;i++){
			tot=tot*c[cnt][a[i]]%mod;
			cnt-=a[i];
		}
		for(int i=1;i<=n;i++)
			if(b[i])tot=tot*inv[b[i]]%mod;
		for(int i=1;i<=now;i++)
			tot=tot*mul[a[i]-1]%mod;
		ans=(ans+tot*mi[sum])%mod;
		return;
	}
	for(int i=a[now];i<=dep;i++){
		a[++now]=i;
		++b[a[now]];
		dfs(dep-i);
		--b[a[now]];
		--now;
	}
}
int main(){
	scanf("%d",&n);prepare();
	now=0;a[0]=1;
	dfs(n);
	ans=ans*Pow(mul[n],mod-2)%mod;
	printf("%d",ans);
	return 0;
}
