#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 10000010
#ifdef WIN32
#define PLL "%I64d"
#else
#define PLL "%lld"
#endif
using namespace std;
int p[maxn],mu[maxn],cnt,f[maxn],sum[maxn];
bool vis[maxn];
void prepare(){
	mu[1]=1;
	for(int i=2;i<=10000000;i++){
		if(!vis[i]){mu[i]=-1;p[++cnt]=i;f[i]=1;}
		for(int j=1;j<=cnt&&i*p[j]<=10000000;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0){mu[i*p[j]]=0;f[i*p[j]]=mu[i];break;}
			else mu[i*p[j]]=-mu[i],f[i*p[j]]=-f[i]+mu[i];
		}
	}
	for(int i=1;i<=10000000;i++)sum[i]=sum[i-1]+f[i];
}
int main(){
	prepare();
	int T,n,m;scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		if(n>m)swap(n,m);
		long long ans=0;
		for(int i=1,j;i<=n;i=j+1){
			j=min(n/(n/i),m/(m/i));
			ans+=1LL*(sum[j]-sum[i-1])*(n/i)*(m/i);
		}
		printf(PLL"\n",ans);
	}
}
