#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1000010
using namespace std;
int T,mod,n,n1,n2,m,a[maxn],prime[maxn],p[maxn];
long long ans;
long long Pow(long long x,int y,int mod){
	long long res=1;
	while(y){
		if(y&1)res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}
long long exgcd(long long a,long long b,long long &x,long long &y){
	if(!b)x=1,y=0;
	else exgcd(b,a%b,y,x),y-=a/b*x;
}
long long inv(long long a,long long b){
	if(!a)return 0;
	long long x=0,y=0;
	exgcd(a,b,x,y);
	x=(x%b+b)%b;
	if(!x)x+=b;
	return x;
}
long long mul(int n,int pi,int pk){
	if(!n)return 1;
	long long ans=1LL;
	if(n/pk){
		for(int i=2;i<=pk;i++)
			if(i%pi)ans=ans*(long long)i%pk;
		ans=Pow(ans,n/pk,pk);
	}
	for(int i=2;i<=n%pk;i++)
		if(i%pi)ans=ans*(long long)i%pk;
	return ans*mul(n/pi,pi,pk)%pk;
}
long long C(int n,int m,int pi,int pk){
	if(m>n)return 0;
	long long a=mul(n,pi,pk),b=mul(m,pi,pk),c=mul(n-m,pi,pk);
	int k=0;
	for(int i=n;i;i/=pi)k+=i/pi;//计算n!中质因子pi的个数 
	for(int i=m;i;i/=pi)k-=i/pi;
	for(int i=n-m;i;i/=pi)k-=i/pi;
	long long ans=a*inv(b,pk)%pk*inv(c,pk)%pk*Pow(pi,k,pk)%pk;
	return ans*(mod/pk)%mod*inv(mod/pk,pk)%mod;
}
long long exLucas(long long n,long long m){
	long long ans=0;
	for(int i=1;i<=p[0];i++)
		ans=(ans+C(n,m,p[i],prime[i]))%mod;
	return ans;
}
long long solve(int sta){
	int opt=0,now=m;
	for(int i=0;i<n1;i++)
		if((sta>>i)&1)++opt,now-=a[i+1];
	if(now<0)return 0;
	if(opt&1)opt=-1;
	else opt=1;
	return exLucas(now+n-1,n-1)*opt;
}
int main(){
	scanf("%d%d",&T,&mod);
	int x=mod;
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			p[++p[0]]=i;prime[p[0]]=1;
			while(x%i==0){prime[p[0]]*=i;x/=i;}
		}
	}
	if(x>1)p[++p[0]]=x,prime[p[0]]=x;
	while(T--){
		scanf("%d%d%d%d",&n,&n1,&n2,&m);
		m-=n;
		for(int i=1;i<=n1+n2;i++)scanf("%d",&a[i]);
		for(int i=n1+1;i<=n1+n2;i++)m-=a[i]-1;
		if(m<0){puts("0");continue;}
		ans=0;
		for(int i=0;i<(1<<n1);i++)
			ans=(ans+solve(i))%mod;
		ans=(ans%mod+mod)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
