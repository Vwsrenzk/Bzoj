#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1000010
#define mod 1000000007
using namespace std;
int T,p[maxn],mu[maxn],cnt;
int f[maxn];
bool vis[maxn];
void prepare(){
	f[0]=0;
	f[1]=1;
	mu[1]=1;
	for(int i=2;i<=1000000;i++){
		f[i]=f[i-2]+f[i-1];
		if(f[i]>=mod)f[i]-=mod;
		if(!vis[i]){mu[i]=-1;p[++cnt]=i;}
		for(int j=1;j<=cnt&&i*p[j]<=1000000;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0){
				mu[i*p[j]]=0;
				break;
			}
			else mu[i*p[j]]=-mu[i];
		}
	}
	for(int i=1;i<=1000000;i++)mu[i]=mu[i-1]+mu[i];
}
int work(int n,int m,int d){
	int res=0;
	n/=d;m/=d;
	for(int i=1,j;i<=n;i=j+1){
		j=min(n/(n/i),m/(m/i));
		res+=1LL*(mu[j]-mu[i-1])*(n/i)*(m/i);
	}
	return res;
}
int Pow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}
int main(){
	int n,m;
	prepare();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		if(n>m)swap(n,m);
		int ans=1;
		for(int i=1;i<=n;i++){
			int mi=work(n,m,i);
			ans=1LL*ans*Pow(f[i],mi)%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
