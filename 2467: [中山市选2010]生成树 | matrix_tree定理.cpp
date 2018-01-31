/*
	题目大意：
		给定一个n五角形圈，求出n五角形圈的不同生成树的数目 
	题解：
		matrix_tree定理模板题 
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#define maxn 1010
#define mod 2007
using namespace std;
int n,f[maxn][maxn],cnt;
int solve(){
	for(int i=1;i<=cnt;i++)
		for(int j=1;j<=cnt;j++)
			f[i][j]=(f[i][j]+mod)%mod;
	int res=1;
	for(int i=1;i<=cnt;i++){
		for(int j=i+1;j<=cnt;j++){
			while(f[j][i]){
				int t=-f[i][i]/f[j][i];
				for(int k=i;k<=cnt;k++)f[i][k]=(f[i][k]+t*f[j][k])%mod;
				for(int k=i;k<=cnt;k++)swap(f[i][k],f[j][k]);
				res=-res;
			}
		}
		if(f[i][i]==0)return 0;
		res*=f[i][i];res%=mod;
	}
	res=(res+mod)%mod;
	return res;
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		memset(f,0,sizeof(f));
		for(int i=1;i<=n;i++){
			f[i][i]+=4;
			f[i][(i+1>n)?1:i+1]--;
			f[i][(i-1<1)?n:i-1]--;
		}
		cnt=n;
		for(int i=1;i<=n;i++){
			cnt++;
			f[i][cnt]--;f[cnt][i]--;
			f[cnt][cnt]+=2;
			f[cnt][cnt+1]--;
			f[cnt+1][cnt]--;

			cnt++;
			f[cnt][cnt]+=2;
			f[cnt][cnt+1]--;
			f[cnt+1][cnt]--;

			cnt++;
			f[cnt][cnt]+=2;
			f[cnt][(i+1>n)?1:i+1]--;
			f[(i+1>n)?1:i+1][cnt]--;
		}
		cnt--;
		printf("%d\n",solve());
	}
}
