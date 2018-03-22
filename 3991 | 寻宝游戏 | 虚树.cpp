#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define maxn 100010
using namespace std;
set<int>s;
set<int>::iterator it,qi,ho;
int num,head[maxn],dep[maxn],id,fa[maxn];
int son[maxn],sz[maxn],top[maxn],dfn[maxn],ra[maxn];
long long ans,g[maxn];
struct node{int to,pre,v;}e[maxn*2];
bool vis[maxn];
void Insert(int from,int to,int v){
	e[++num].to=to;
	e[num].v=v;
	e[num].pre=head[from];
	head[from]=num;
}
void dfs1(int x,int father){
	dep[x]=dep[father]+1;
	fa[x]=father;
	sz[x]=1;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father)continue;
		g[to]=g[x]+e[i].v;
		dfs1(to,x);
		if(sz[to]>sz[son[x]])son[x]=to;
		sz[x]+=sz[to];
	}
}
void dfs2(int x,int father){
	top[x]=father;
	dfn[x]=++id;ra[id]=x;
	if(son[x])dfs2(son[x],father);
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if((to==son[x])||(to==fa[x]))continue;
		dfs2(to,to);
	}
}
int lca(int a,int b){
	while(top[a]!=top[b]){
		if(dep[top[a]]<dep[top[b]])swap(a,b);
		a=fa[top[a]];
	}
	if(dep[a]>dep[b])swap(a,b);
	return a;
}
long long query(int x){
	it=s.find(dfn[x]);
	if(it==s.begin()){qi=s.end();qi--;}
	else {qi=it;qi--;}
	ho=it;ho++;
	if(ho==s.end())ho=s.begin();
	return g[ra[*ho]]+g[ra[*it]]*2+g[ra[*qi]]-g[lca(ra[*ho],ra[*it])]*2-g[lca(ra[*it],ra[*qi])]*2;
}
long long work(int x){
	it=s.find(dfn[x]);
	if(it==s.begin()){qi=s.end();qi--;}
	else{qi=it;qi--;}
	ho=it;ho++;
	if(ho==s.end())ho=s.begin();
	return g[ra[*ho]]+g[ra[*qi]]-2*g[lca(ra[*qi],ra[*ho])];
}
int main(){
	int n,m,x,y,z;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		Insert(x,y,z);Insert(y,x,z);
	}
	dfs1(1,0);dfs2(1,1);
	for(int i=1;i<=m;i++){
		scanf("%d",&x);
		if(vis[x]){//要删掉x 
			ans-=query(x);
			ans+=work(x);
			s.erase(dfn[x]);vis[x]=0;
		}
		else{
			vis[x]=1;
			s.insert(dfn[x]);
			ans-=work(x);
			ans+=query(x);
		}
		cout<<ans<<endl;
	}
	return 0;
}
