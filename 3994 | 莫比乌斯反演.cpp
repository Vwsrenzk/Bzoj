#include<iostream>
#include<cstdio>
#define maxn 50010
using namespace std;
int T,n,m;
long long f[maxn],mu[maxn],sum[maxn],p[maxn],cnt;
bool vis[maxn];
void prepare(){
	mu[1]=1;
	for(int i=2;i<=50000;i++){
		if(!vis[i]){vis[i]=1;p[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&i*p[j]<=50000;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0){mu[i*p[j]]=0;break;}
			else mu[i*p[j]]=-mu[i];
		}
	}
	for(int i=1;i<=50000;i++)sum[i]=sum[i-1]+mu[i];
	for(int i=1;i<=50000;i++)
		for(int j=1,k;j<=i;j=k+1){
			k=i/(i/j);
			f[i]+=1LL*(k-j+1)*(i/j);
		}
}
int main(){
	prepare();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		if(n>m)swap(n,m);
		long long ans=0;
		for(int i=1,j;i<=n;i=j+1){
			j=min(n/(n/i),m/(m/i));
			ans+=(sum[j]-sum[i-1])*f[n/i]*f[m/i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
