#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 310
using namespace std;
double p[maxn],a[maxn][maxn],ans[maxn];
char st[maxn][maxn];
int n,m,fail[maxn][maxn];
void kmp(char *s,int *f){
	for(int i=2,j=0;i<=m;i++){
		while(j&&s[j+1]!=s[i])j=f[j];
		if(s[j+1]==s[i])j++;
		f[i]=j;
	}
}
double Calc(int y,int x){
	double ans=0;int j=0;
	for(int i=1;i<=m;i++){
		while(j&&st[y][j+1]!=st[x][i])j=fail[y][j];
		if(st[y][j+1]==st[x][i])j++;
	}
	while(j)ans+=p[m-j],j=fail[y][j];
	return ans;
}
void Gauss(){
	for(int i=1;i<=n+1;i++){
		for(int j=i;j<=n+1;j++)
			if(a[j][i]){
				if(j!=i)
				for(int k=i;k<=n+2;k++)
					swap(a[j][k],a[i][k]);
				break;
			}
		for(int j=i+1;j<=n+1;j++){
			double delta=a[j][i]/a[i][i];
			for(int k=i;k<=n+2;k++)
				a[j][k]=a[j][k]-a[i][k]*delta;
		}
	}
	for(int i=n+1;i;i--){
		for(int j=i+1;j<=n+1;j++)
			a[i][n+2]-=a[i][j]*ans[j];
		ans[i]=a[i][n+2]/a[i][i];
	}
}
int main(){
	scanf("%d%d",&n,&m);p[0]=1;
	for(int i=1;i<=m;i++)p[i]=p[i-1]/2;
	for(int i=1;i<=n;i++)
		scanf("%s",st[i]+1),a[i][n+1]=-p[m];
	for(int i=1;i<=n;i++)a[n+1][i]=1;
	a[n+1][n+2]=1;
	for(int i=1;i<=n;i++)kmp(st[i],fail[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		a[i][j]=Calc(i,j);
	Gauss();
	for(int i=1;i<=n;i++)printf("%.10lf\n",ans[i]);
	return 0;
}
