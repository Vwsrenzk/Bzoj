#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
using namespace std;
int n,q,id,num,w[maxn],c[maxn],tot;
int head[maxn],dfn[maxn],dep[maxn],top[maxn],sz[maxn],fa[maxn],son[maxn];
int root[maxn],lc[maxn*20],rc[maxn*20],mx[maxn*20],sum[maxn*20];
struct node{int to,pre;}e[maxn*2];
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
//------------------------------------------------------------------------------树链剖分 
void dfs1(int now,int father){
	dep[now]=dep[father]+1;
	fa[now]=father;
	sz[now]=1;
	for(int i=head[now];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father)continue;
		dfs1(to,now);
		sz[now]+=sz[to];
		if((!son[now])||(sz[son[now]]<sz[to]))son[now]=to;
	}
}
void dfs2(int now,int father){
	top[now]=father;
	dfn[now]=++id;
	if(son[now])dfs2(son[now],father);
	for(int i=head[now];i;i=e[i].pre){
		int to=e[i].to;
		if((to==son[now])||(to==fa[now]))continue;
		dfs2(to,to);
	}
}
int LCA(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return x;
}
//------------------------------------------------------------------------------线段树 
void update(int k){
	mx[k]=max(mx[lc[k]],mx[rc[k]]);
	sum[k]=sum[lc[k]]+sum[rc[k]];
}
void modify(int &k,int l,int r,int opx,int opv){
	if(!k)k=++tot;
	if(l==r){mx[k]=sum[k]=opv;return;}
	int mid=(l+r)>>1;
	if(opx<=mid)modify(lc[k],l,mid,opx,opv);
	else modify(rc[k],mid+1,r,opx,opv);
	update(k);
}
int qsum(int k,int l,int r,int opl,int opr){
	if(l>=opl&&r<=opr)return sum[k];
	int mid=(l+r)>>1,res=0;
	if(opl<=mid)res+=qsum(lc[k],l,mid,opl,opr);
	if(opr>mid)res+=qsum(rc[k],mid+1,r,opl,opr);
	return res;
}
int qmax(int k,int l,int r,int opl,int opr){
	if(l>=opl&&r<=opr)return mx[k];
	int mid=(l+r)>>1,res=0;
	if(opl<=mid)res=max(res,qmax(lc[k],l,mid,opl,opr));
	if(opr>mid)res=max(res,qmax(rc[k],mid+1,r,opl,opr));
	return res;
}
//------------------------------------------------------------------------------
int query_sum(int k,int x,int y){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res+=qsum(root[k],1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	res+=qsum(root[k],1,n,dfn[x],dfn[y]);
	return res;
}
int query_max(int k,int x,int y){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res=max(res,qmax(root[k],1,n,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	res=max(res,qmax(root[k],1,n,dfn[x],dfn[y]));
	return res;
}
//------------------------------------------------------------------------------
int main(){
	scanf("%d%d",&n,&q);
	int x,y;
	for(int i=1;i<=n;i++)scanf("%d%d",&w[i],&c[i]);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		Insert(x,y);Insert(y,x);
	}
	dfs1(1,0);dfs2(1,1);
	for(int i=1;i<=n;i++)modify(root[c[i]],1,n,dfn[i],w[i]);
	scanf("%d",&q);
	while(q--){
		char ch[5];scanf("%s",ch+1);
		scanf("%d%d",&x,&y);
		if(ch[1]=='C'){
			if(ch[2]=='C'){//
				modify(root[c[x]],1,n,dfn[x],0);
				c[x]=y;
				modify(root[c[x]],1,n,dfn[x],w[x]);
			}
			else {
				w[x]=y;
				modify(root[c[x]],1,n,dfn[x],w[x]);
			}
		}
		else{
			int lca=LCA(x,y);
			if(ch[2]=='S'){
				int val=query_sum(c[x],x,lca)+query_sum(c[x],y,lca);
				if(c[x]==c[lca])val-=w[lca];
				printf("%d\n",val);
			}
			else {
				printf("%d\n",max(query_max(c[x],x,lca),query_max(c[x],y,lca)));
			}
		}
	}
	return 0;
}
