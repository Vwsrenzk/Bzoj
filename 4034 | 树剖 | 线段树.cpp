#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
using namespace std;
int head[maxn],in[maxn],out[maxn],dfn[maxn];
int dep[maxn],fa[maxn],son[maxn],sz[maxn],top[maxn],b[maxn];
long long val[maxn];
int num,id,n,m;
struct node{int to,pre;}e[maxn*2];
struct Segment{int l,r;long long v,lazy;}tr[maxn*4];
void Insert(int from,int to){
	e[++num].to=to;
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
		dfs1(to,x);
		sz[x]+=sz[to];
		if(!son[x]||(sz[son[x]]<sz[to]))son[x]=to;
	}
}
void dfs2(int x,int father){
	dfn[x]=++id;top[x]=father;
	in[x]=id;b[id]=x;
	if(son[x])dfs2(son[x],father);
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if((to==fa[x])||(to==son[x]))continue;
		dfs2(to,to);
	}
	out[x]=id;
}
void pushdown(int k){
	int l=k<<1,r=k<<1|1;
	tr[l].lazy+=tr[k].lazy;tr[r].lazy+=tr[k].lazy;
	tr[l].v+=(tr[l].r-tr[l].l+1)*tr[k].lazy;
	tr[r].v+=(tr[r].r-tr[r].l+1)*tr[k].lazy;
	tr[k].lazy=0;
}
void modify_point(int k,int l,int r,int id,long long v){
	if(l==r){
		tr[k].v+=v;
		return;
	}
	if(tr[k].lazy)pushdown(k);
	int mid=(l+r)>>1;
	if(id<=mid)modify_point(k<<1,l,mid,id,v);
	else modify_point(k<<1|1,mid+1,r,id,v);
	tr[k].v=tr[k<<1].v+tr[k<<1|1].v;
}
void modify_zakres(int k,int l,int r,int opl,int opr,long long v){
	if(l>=opl&&r<=opr){
		tr[k].lazy+=v;
		tr[k].v+=(tr[k].r-tr[k].l+1)*v;
		return;
	}
	if(tr[k].lazy)pushdown(k);
	int mid=(l+r)>>1;
	if(opl<=mid)modify_zakres(k<<1,l,mid,opl,opr,v);
	if(opr>mid)modify_zakres(k<<1|1,mid+1,r,opl,opr,v);
	tr[k].v=tr[k<<1].v+tr[k<<1|1].v;
}
void build(int l,int r,int k){
	tr[k].l=l;tr[k].r=r;
	if(l==r){
		tr[k].v=val[b[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,k<<1);build(mid+1,r,k<<1|1);
	tr[k].v=tr[k<<1].v+tr[k<<1|1].v;
}
long long query(int k,int l,int r,int opl,int opr){
	if(l>=opl&&r<=opr)return tr[k].v;
	if(tr[k].lazy)pushdown(k);
	int mid=(l+r)>>1;
	long long res=0;
	if(opl<=mid)res+=query(k<<1,l,mid,opl,opr);
	if(opr>mid)res+=query(k<<1|1,mid+1,r,opl,opr);
	return res;
}
long long query_sum(int x,int y){
	long long res=0;
	while(top[x]!=top[y]){
		res+=query(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	res+=query(1,1,n,1,dfn[x]);
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	int op,x,y;
	for(int i=1;i<=n;i++)scanf("%lld",&val[i]);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		Insert(x,y);Insert(y,x);
	}
	dfs1(1,0);dfs2(1,1);
	build(1,n,1);
	while(m--){
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d",&x,&y);
			modify_point(1,1,n,dfn[x],y);
		}
		if(op==2){
			scanf("%d%d",&x,&y);
			modify_zakres(1,1,n,in[x],out[x],y);
		}
		if(op==3){
			scanf("%d",&x);
			printf("%lld\n",query_sum(x,1));
		}
	}
}
