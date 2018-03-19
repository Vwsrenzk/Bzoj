#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define maxn 510
using namespace std;
int n,m,s[maxn*maxn*2],t[maxn*maxn*2];
double a[maxn][maxn],du[maxn],f[maxn*maxn*2],g[maxn];
void Gauss(int n,int m){
	for(int i=1;i<m;i++){//枚举每个变量 
		int k=i;
		for(int j=i+1;j<=n;j++)
			if(fabs(a[j][i])>fabs(a[k][i]))k=j;
		if(i!=k)for(int j=1;j<=m;j++)swap(a[i][j],a[k][j]);
		for(int j=i+1;j<=n;j++){
			double t=a[j][i]/a[i][i];
			for(int k=i;k<=m;k++)
				a[j][k]-=a[i][k]*t;
		}
	}
	for(int i=m-1;i;i--){
		for(int j=i+1;j<m;j++)a[i][m]-=a[i][j]*g[j];
		g[i]=a[i][m]/a[i][i];
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&s[i],&t[i]);
		du[s[i]]++;du[t[i]]++;
	}
	for(int i=1;i<n;i++)a[i][i]=-1.0;
	for(int i=1;i<=m;i++){
		a[s[i]][t[i]]+=1.0/du[t[i]];
		a[t[i]][s[i]]+=1.0/du[s[i]];
	}
	for(int i=1;i<=n;i++)a[n][i]=0;
	a[1][n+1]=-1;a[n][n]=1;
	Gauss(n,n+1);
	for(int i=1;i<=m;i++){
		f[i]=g[s[i]]/du[s[i]]+g[t[i]]/du[t[i]];
	}
	double ans=0;
	sort(f+1,f+m+1);
    for(int i=1;i<=m;i++)ans+=(m-i+1)*f[i];
    printf("%.3lf\n",ans);
}
