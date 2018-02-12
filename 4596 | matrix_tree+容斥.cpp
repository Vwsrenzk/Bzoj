/*
	题目大意： 
		只修 N- 1 条路将n个城市连接起来，有正好 N- 1 个建筑公司，每个建筑公司有能负责修建的路，选择 N-1 条能够连接所有城市的边，然后每条边都交给一
		个能够负责该边的建筑公司修建，并且每个建筑公司都恰好修一条边。
		求一共有多少种可能的方案
	题解：
		 matrix_tree+容斥原理
		 （计数问题先考虑容斥原理）
		 总方案就相当于任意选的方案-1个公司不选的方案+2个公司不选的方案……
		 用搜索来容斥，算方案的时候可以用矩阵树定理来算 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 1000000007
#define maxn 20
using namespace std;
int ans,n,head[maxn],num,f[maxn][maxn],a[maxn][maxn];
struct node{int from,to,pre;}e[maxn*maxn*2];
void Insert(int from,int to,int hum){
	e[++num].to=to;
	e[num].from=from;
	e[num].pre=head[hum];
	head[hum]=num;
}
int solve(int m){
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			a[i][j]=(f[i][j]+mod)%mod;
	int res=1;
	for(int i=1;i<=m;i++){
		for(int j=i+1;j<=m;j++){
			while(a[j][i]){
				int t=-a[i][i]/a[j][i];
				for(int k=i;k<=m;k++)a[i][k]=(a[i][k]+1LL*t*a[j][k]%mod)%mod;
				for(int k=i;k<=m;k++)swap(a[i][k],a[j][k]);
				res=-res;
			}
		}
		if(a[i][i]==0)return 0;
		res=1LL*res*a[i][i]%mod;
	}
	res=(res+mod)%mod;
	return res;
}
void dfs(int x,int y){
	if(x==n){
		ans+=((y%2==1)?-1:1)*solve(n-1);
		ans%=mod;
		return;
	}
	dfs(x+1,y);
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to,from=e[i].from;
		f[from][from]--;f[to][to]--;
		f[from][to]++;f[to][from]++;
	}
	dfs(x+1,y+1);
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to,from=e[i].from;
		f[from][from]++;f[to][to]++;
		f[from][to]--;f[to][from]--;
	}
}
int main(){
	scanf("%d",&n);
	int x,y,z;
	for(int i=1;i<n;i++){
		scanf("%d",&z);
		while(z--){
			scanf("%d%d",&x,&y);
			Insert(x,y,i);
			f[x][x]++;f[y][y]++;
			f[x][y]--;f[y][x]--;
		}
	}
	dfs(1,0);
	ans=(ans+mod)%mod;
	printf("%d",ans);
}
