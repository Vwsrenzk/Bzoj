#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
#define INF 1000000007
using namespace std;
long long n,k,sum[maxn],f[maxn],g[maxn];
int q[maxn];
long long qread(){
	long long i=0,j=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
	return i*j;
}
long long Calc(int j,int k){
	if(sum[j]==sum[k])return 0;
	return (g[j]-g[k]-sum[j]*sum[j]+sum[k]*sum[k])/(sum[k]-sum[j]);
}
int main(){
	n=qread();k=qread();
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+qread();
	for(int i=1;i<=k;i++){
		int h=0,t=0;
		for(int j=i;j<=n;j++){
			while(h<t&&Calc(q[h],q[h+1])<sum[j])h++;
			f[j]=g[q[h]]+sum[q[h]]*(sum[j]-sum[q[h]]);
			while(h<t&&Calc(q[t-1],q[t])>Calc(q[t],j))t--;
			q[++t]=j;
		}
		for(int j=i;j<=n;j++)g[j]=f[j];
	}
	cout<<f[n];
}
