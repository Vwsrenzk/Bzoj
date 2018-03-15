#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 3010
using namespace std;
long long sum[maxn],f[maxn][maxn];
int n,m,q[maxn],head,tail;
int sqr(int x){return x*x;}
double get(int i,int x,int y){
	return (double)(f[i][x]+sqr(sum[x])-(f[i][y]+sqr(sum[y])))/(double)(sum[x]-sum[y]);
}
int main(){
	scanf("%d%d",&n,&m);
	int x;
	for(int i=1;i<=n;i++){scanf("%d",&x);sum[i]=sum[i-1]+x;}
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=m;i++){
		head=tail=1;
		for(int j=1;j<=n;j++){
			while(head<tail&&get(i-1,q[tail],q[tail-1])>get(i-1,j,q[tail]))tail--;
			q[++tail]=j;
			while(head<tail&&get(i-1,q[head+1],q[head])<(double)(sum[j]<<1))head++;
			f[i][j]=f[i-1][q[head]]+sqr(sum[j]-sum[q[head]]);
		}
	}
	printf("%lld",f[m][n]*m-sqr(sum[n]));
	return 0;
}
