#include<iostream>
#include<cstdio>
#define maxn 5010
using namespace std;
struct node{int k,i,j;}op[10010];
struct edge{int to,pre;}e[200010];
int n,m,q,u[200010],v[200010],num,ans,tim,E[maxn][maxn];
int fa[maxn],id[maxn],tot,head[maxn],from[maxn];
bool del[maxn][maxn],have[maxn][maxn];
char ch[5];
int find(int x){
	if(x==fa[x])return fa[x];
	return fa[x]=find(fa[x]);
}
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
void dfs(int x,int y){
	from[x]=y;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(E[x][to]&&from[to]!=y)dfs(to,y);
	}
}
void add(int x,int y){
	if(from[x]!=from[y]){
		ans--;
		dfs(y,from[x]);
	}
	E[x][y]++;
	E[y][x]++;
	if(!have[x][y]){
		Insert(x,y);Insert(y,x);
		have[x][y]=have[y][x]=1;
	}
}
void deled(int x,int y){
	E[x][y]--;
	E[y][x]--;
	dfs(x,++tim);
	if(from[y]!=from[x])ans++;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)scanf("%d%d",&u[i],&v[i]);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%s",ch);
		if(ch[0]=='A'){
			scanf("%d%d",&op[i].i,&op[i].j);
		}
		else if(ch[0]=='D'){
			op[i].k=1;
			scanf("%d%d",&op[i].i,&op[i].j);
			del[op[i].i][op[i].j]=1;
			del[op[i].j][op[i].i]=1;
		}
		else op[i].k=2;
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
		if(!del[u[i]][v[i]]){
			int f1=find(u[i]),f2=find(v[i]);
			if(f1!=f2)fa[f1]=f2;
		}
	for(int i=1;i<=n;i++)fa[i]=find(i);
	for(int i=1;i<=n;i++){//缩点 
		if(!id[fa[i]])id[fa[i]]=++tot;
		fa[i]=id[fa[i]];
	}
	ans=tim=tot;
	for(int i=1;i<=tot;i++)from[i]=i;
	for(int i=1;i<=m;i++)
		if(fa[u[i]]!=fa[v[i]])add(fa[u[i]],fa[v[i]]);
	for(int i=1;i<=q;i++){
		op[i].i=fa[op[i].i];
		op[i].j=fa[op[i].j];
		if(op[i].k==0&&op[i].i!=op[i].j)add(op[i].i,op[i].j);
		if(op[i].k==1&&op[i].i!=op[i].j)deled(op[i].i,op[i].j);
		if(op[i].k==2)printf("%d\n",ans);
	}
	return 0;
}
