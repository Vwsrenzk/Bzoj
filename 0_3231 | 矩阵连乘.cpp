#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 20
using namespace std;
int K;
long long b[maxn],c[maxn],m,n,mod,ans;
long long qread(){
	long long i=0,j=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')i=i*10+ch-'0',ch=getchar();
	return i*j;
}
struct matrix{
	long long a[maxn][maxn];
	matrix(){memset(a,0,sizeof(a));}
	matrix operator * (const matrix &x)const{
		matrix res;
		for(int i=1;i<=K+1;i++)
			for(int j=1;j<=K+1;j++)
				for(int k=1;k<=K+1;k++)
					res.a[i][j]=(res.a[i][j]+a[i][k]*x.a[k][j]%mod)%mod;
		return res;
	}
}tmp1,tmp2;
matrix Pow(matrix x,long long y){
	y--;
	matrix res=x;
	while(y){
		if(y&1)res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
long long solve(long long x){
	if(!x)return tmp2.a[1][K+1];
	matrix T=Pow(tmp1,x);
	T=tmp2*T;
	return T.a[1][K+1];
}
int main(){
	scanf("%d",&K);
	for(int i=1;i<=K;i++)b[i]=qread();
	for(int i=1;i<=K;i++)c[i]=qread();
	m=qread(),n=qread(),mod=qread();
	for(int i=1;i<=K;i++)b[i]%=mod,c[i]%=mod,b[K+1]+=b[i],b[K+1]%=mod;
	for(int i=1;i<=K;i++)tmp1.a[i][1]=tmp1.a[i][K+1]=c[i];
	for(int i=2;i<=K;i++)tmp1.a[i-1][i]=1;
	tmp1.a[K+1][K+1]=1;
	for(int i=1;i<=K;i++)tmp2.a[1][i]=b[K-i+1];
	tmp2.a[1][K+1]=b[K+1];
	if(n<=K){
		for(int i=m;i<=n;i++)ans+=b[i],ans%=mod;
		cout<<ans;
		return 0;
	}
	ans=solve(n-K);
	if(m<=K)
		for(int i=1;i<m;i++)ans-=b[i];
	else ans-=solve(m-K-1);
	ans=(ans+mod)%mod;
	cout<<ans;
	return 0;
}
