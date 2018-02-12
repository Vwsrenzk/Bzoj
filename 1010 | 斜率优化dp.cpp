#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 50010
using namespace std;
int q[maxn],n,l,c;
long long a[maxn],dp[maxn],g[maxn];
long long qread(){
	long long i=0,j=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
	return i*j;
}
double Slope(int k,int j){//斜率 
	return ((dp[j]+g[j]*g[j]+2*c*g[j])-(dp[k]+g[k]*g[k]+2*c*g[k]))/(2.0*(g[j]-g[k]));
}
int main(){
	scanf("%d%d",&n,&l);c=l+1;
	for(int i=1;i<=n;i++){
		a[i]=qread();
		g[i]=g[i-1]+a[i];
	}
	for(int i=1;i<=n;i++)g[i]+=i;
	int h=1,t=0;q[++t]=0;
	for(int i=1;i<=n;i++){
		while(h<t&&Slope(q[h],q[h+1])<=g[i])h++;
		int w=q[h];
		dp[i]=dp[w]+(g[i]-g[w]-c)*(g[i]-g[w]-c);
		while(h<t&&Slope(q[t],i)<Slope(q[t-1],q[t]))t--;
		q[++t]=i;
	}
	cout<<dp[n];
	return 0;
}
