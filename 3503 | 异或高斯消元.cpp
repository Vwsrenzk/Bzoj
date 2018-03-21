#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 2010
using namespace std;
int id[50][50],a[maxn][maxn],b[maxn],ans[maxn],n,m,cnt;
int dx[5]={0,0,0,1,-1};
int dy[5]={0,1,-1,0,0};
void Gauss(int n){
	for(int i=1;i<=n;i++){
		bool flag=0;
		for(int j=i;j<=n;j++)
			if(a[j][i]){
				for(int k=1;k<=n;k++)swap(a[i][k],a[j][k]);
				flag=1;break;
			}
		if(!flag)continue;
		for(int j=i+1;j<=n;j++)
			if(a[j][i])
				for(int k=i;k<=n;k++)a[j][k]^=a[i][k];
	}
	for(int i=n;i>=1;i--){
		ans[i]=a[i][i]?b[i]:1;
		if(ans[i])
			for(int j=1;j<=i-1;j++)if(a[j][i])b[j]^=1;
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)id[i][j]=++cnt;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=0;k<=4;k++){
				int t1=id[i][j];
				int t2=id[i+dx[k]][j+dy[k]];
				if(t2)a[t1][t2]=1;
			}
	Gauss(cnt);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			printf("%d ",ans[id[i][j]]);
		puts("");
	}
	return 0;
}
