#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 1000000007
#define maxn 5000010
using namespace std;
long long n,m,k,T,p[maxn],cnt,f[maxn],g[maxn];
bool vis[maxn];
int Pow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}
void prepare(){
	f[1]=1;
	for(int i=2;i<=5000000;i++){
		if(!vis[i]){
			p[++cnt]=i;
			g[cnt]=Pow(i,k);
			f[i]=(g[cnt]-1+mod)%mod;
		}
		for(int j=1;j<=cnt&&i*p[j]<=5000000;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0){
				f[i*p[j]]=1LL*f[i]*g[j]%mod;
				break;
			}
			f[i*p[j]]=1LL*f[i]*f[p[j]]%mod;
		}
	}
	for(int i=1;i<=5000000;i++)f[i]=(f[i]+f[i-1])%mod;
}
int main(){
	scanf("%lld%lld",&T,&k);
	prepare();
	while(T--){
		scanf("%lld%lld",&n,&m);
		if(n>m)swap(n,m);
		long long ans=0;
		for(int i=1,j;i<=n;i=j+1){
			j=min(n/(n/i),m/(m/i));
			ans+=(n/i)*(m/i)%mod*(((f[j]-f[i-1])%mod+mod)%mod)%mod;
			ans%=mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
