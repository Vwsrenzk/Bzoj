#include<iostream>
#include<cstdio>
#define maxn 50010
using namespace std;
int T,a,b,c,d,k;
long long p[maxn],cnt,mu[maxn],sum[maxn];
bool vis[maxn];
void prepare(){
	mu[1]=1;
	for(int i=2;i<=50000;i++){
		if(!vis[i]){p[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&i*p[j]<=50000;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0){mu[i*p[j]]=0;break;}
			else mu[i*p[j]]=-mu[i];
		}
	}
	for(int i=1;i<=50000;i++)sum[i]=sum[i-1]+mu[i];
}
long long work(long long n,long long m){
	if(!n||!m)return 0;
	long long res=0;
	if(n>m)swap(n,m);
	for(int i=1,j;i<=n;i=j+1){
		j=min(n/(n/i),m/(m/i));
		res+=(sum[j]-sum[i-1])*(n/i)*(m/i);
	}
	return res;
}
int main(){
	prepare();
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		long long a1=work(b/k,d/k);
		long long a2=work(b/k,(c-1)/k);
		long long a3=work((a-1)/k,d/k);
		long long a4=work((a-1)/k,(c-1)/k);
		int ans=a1-a2-a3+a4;
		printf("%d\n",ans);
	}
}
