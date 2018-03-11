#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1010
using namespace std;
int p[maxn],cnt,n;
long long f[210][maxn];
bool vis[maxn];
void prepare(){
	for(int i=2;i<=1000;i++){
		if(!vis[i])p[++cnt]=i;
		for(int j=1;j<=cnt&&i*p[j]<=1000;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
int main(){
	prepare();
	scanf("%d",&n);
	for(int i=0;i<=cnt;i++)f[i][0]=1;
	for(int i=1;i<=n;i++)f[0][i]=1;
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<=n;j++){
			f[i][j]=f[i-1][j];
			for(int k=p[i];k<=j;k*=p[i])
				f[i][j]+=f[i-1][j-k];
		}
	printf("%lld",f[cnt][n]);
	return 0;
}
