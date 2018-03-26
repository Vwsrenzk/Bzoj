/*
  强行将矩阵中的数值作为边权，跑最大生成树，检验是否满足矩阵
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 1000000000
#define maxn 1010
using namespace std;
int f[maxn][maxn],n,m,fa[100010],vis[maxn],num,head[maxn];
struct Node{int from,to;}E[300010];
struct node{int to,pre,v;}e[300010*2];
int qread(){
	int i=0,j=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
	return i*j;
}
bool cmp(Node x,Node y){return f[x.from][x.to]>f[y.from][y.to];}
int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
void Insert(int from,int to,int v){
	e[++num].to=to;
	e[num].v=v;
	e[num].pre=head[from];
	head[from]=num;
}
bool pd(int x,int y){
	if(x==y&&f[x][y])return 0;
	if(x==y&&f[x][y]==0)return 1;
	if(vis[y]!=f[x][y])return 0;
	if(f[x][y]!=f[y][x])return 0;
	return 1;
}
void dfs(int now,int w){
	vis[now]=w;
	for(int i=head[now];i;i=e[i].pre){
		int to=e[i].to;
		if(vis[to]==-1)dfs(to,min(w,e[i].v));
	}
}
int main(){
	int T;scanf("%d",&T);
	int flag,cnt,Case=0;
	while(T--){
		Case++;
		n=qread();m=qread();
		num=0;memset(head,0,sizeof(head));
		int x,y;
		for(int i=1;i<=m;i++)
			E[i].from=qread(),E[i].to=qread();
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			f[i][j]=qread();
		sort(E+1,E+m+1,cmp);
		cnt=0;
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1;i<=m;i++){
			int f1=find(E[i].from),f2=find(E[i].to);
			if(f1!=f2){
				cnt++;
				Insert(E[i].from,E[i].to,f[E[i].from][E[i].to]);
				Insert(E[i].to,E[i].from,f[E[i].from][E[i].to]);
				fa[f1]=f2;
				if(cnt==n-1)break;
			}
		}
		flag=0;
		for(int i=1;i<=n;i++){
			if(flag)break;
			memset(vis,-1,sizeof(vis));
			dfs(i,INF);
			for(int j=1;j<=i;j++){
				if(!pd(i,j)){flag=1;break;}
			}
		}
		if(flag)printf("Case #%d: No\n",Case);
		else printf("Case #%d: Yes\n",Case);
	}
}
