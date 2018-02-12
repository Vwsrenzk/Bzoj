/*
	题目大意：
		一排纸牌，用红绿蓝三种颜色进行染色，三种纸牌都规定了数量，而且给定了几个置换，在每一个置换下所形成的方案属于同一种。问一共有几种方案
	题解：
		http://www.cnblogs.com/iwtwiioi/p/4114956.html
		polya+背包dp 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 65
using namespace std;
int p,m,R,B,G,n,ans,f[22][22][22];
int a[maxn],s[maxn],vis[maxn];
int Pow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1LL*res*x%p;
		x=1LL*x*x%p;
		y>>=1;
	}
	return res;
}
void add(int &a,int b){
	a=(a+b)%p;
	a=(a+p)%p;
}
int getans(){
	memset(f,0,sizeof(f));
	memset(s,0,sizeof(s));
	memset(vis,0,sizeof(vis));
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			cnt++;
			for(int x=i;!vis[x];x=a[x])
			vis[x]=1,++s[cnt];//s[i]表示第i个循环的大小 
		}
	}
	f[0][0][0]=1;
	for(int i=1;i<=cnt;i++)
		for(int r=R;r>=0;r--)
		for(int b=B;b>=0;b--)
		for(int g=G;g>=0;g--){
			if(r-s[i]>=0)add(f[r][b][g],f[r-s[i]][b][g]);
			if(b-s[i]>=0)add(f[r][b][g],f[r][b-s[i]][g]);
			if(g-s[i]>=0)add(f[r][b][g],f[r][b][g-s[i]]);
		}
	return f[R][B][G];
}
int main(){
	freopen("Cola.txt","r",stdin);
	scanf("%d%d%d%d%d",&R,&B,&G,&m,&p);
	n=R+B+G;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)scanf("%d",&a[j]);
		add(ans,getans());
	}
	for(int i=1;i<=n;i++)a[i]=i;
	add(ans,getans());
	ans*=Pow(m+1,p-2);
	printf("%d\n",ans%p);
	return 0;
}
