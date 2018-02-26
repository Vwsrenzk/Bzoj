#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 200010
using namespace std;
int head[maxn],num,id,n,m;
int son[maxn],dep[maxn],fa[maxn],sz[maxn],top[maxn],dfn[maxn],belong[maxn],in[maxn],out[maxn];
struct node{int to,pre;}e[maxn*2];
struct Segment{int l,r,v,lazy;}tr[maxn*4];
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
void dfs1(int x,int father){
	dep[x]=dep[father]+1;
	sz[x]=1;
	fa[x]=father;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father)continue;
		dfs1(to,x);
		sz[x]+=sz[to];
		if(!son[x]||(sz[son[x]]<sz[to]))son[x]=to;
	}
}
void dfs2(int x,int father){
	dfn[x]=++id;belong[id]=x;
	in[x]=id;
	top[x]=father;
	if(son[x])dfs2(son[x],father);
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if((to==fa[x])||(to==son[x]))continue;
		dfs2(to,to);
	}
	out[x]=id;
}
void build(int l,int r,int k){
	tr[k].l=l;tr[k].r=r;
	if(l==r){tr[k].v=0;return;}
	int mid=(l+r)>>1;
	build(l,mid,k<<1);build(mid+1,r,k<<1|1);
	tr[k].v=0;
}
void pushdown(int k){
	if(tr[k].l==-1)return;
	int l=k<<1,r=k<<1|1;
	tr[l].lazy=tr[k].lazy;
	tr[r].lazy=tr[k].lazy;
	tr[l].v=(tr[l].r-tr[l].l+1)*tr[k].lazy;
	tr[r].v=(tr[r].r-tr[r].l+1)*tr[k].lazy;
	tr[k].lazy=-1;
}
int query(int k,int l,int r,int opx){
	if(l==r)return tr[k].v;
	if(tr[k].lazy!=-1)pushdown(k);
	int mid=(l+r)>>1;
	int res=-1;
	if(opx<=mid)res=query(k<<1,l,mid,opx);
	else res=query(k<<1|1,mid+1,r,opx);
	tr[k].v=tr[k<<1].v+tr[k<<1|1].v;
	return res;
}
void modify(int k,int l,int r,int opl,int opr,int w){
	if(l>=opl&&r<=opr){
		tr[k].lazy=w;
		tr[k].v=(tr[k].r-tr[k].l+1)*w;
		return;
	}
	if(tr[k].lazy!=-1)pushdown(k);
	int mid=(l+r)>>1;
	if(opl<=mid)modify(k<<1,l,mid,opl,opr,w);
	if(opr>mid)modify(k<<1|1,mid+1,r,opl,opr,w);
	tr[k].v=tr[k<<1].v+tr[k<<1|1].v;
}
int query_zakres(int k,int l,int r,int opl,int opr){
	if(l>=opl&&r<=opr)return tr[k].v;
	if(tr[k].lazy!=-1)pushdown(k);
	int mid=(l+r)>>1;
	int res=0;
	if(opl<=mid)res+=query_zakres(k<<1,l,mid,opl,opr);
	if(opr>mid)res+=query_zakres(k<<1|1,mid+1,r,opl,opr);
	tr[k].v=tr[k<<1].v+tr[k<<1|1].v;
	return res;
}
int find(int x,int w){//找第一个出现0的位置 
	while(top[x]!=1){
		if(query(1,1,n,dfn[fa[top[x]]])==w)x=fa[top[x]];
		else break;
	}
	int y=top[x];
	int r=dfn[x],l=dfn[y],ans=l;
	while(l<=r){
		int mid=(l+r)>>1;
		if(query(1,1,n,mid)==w)r=mid-1,ans=mid;
		else l=mid+1;
	}
	return ans;
}
void modify_sum(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		modify(1,1,n,dfn[top[x]],dfn[x],1);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	modify(1,1,n,dfn[x],dfn[y],1);
	return;
}
int main(){
	memset(tr,-1,sizeof(tr));
	scanf("%d",&n);
	int x;char ch[25];
	for(int i=2;i<=n;i++){
		scanf("%d",&x);x++;
		Insert(x,i);Insert(i,x);
	}
	dfs1(1,0);dfs2(1,1);
	build(1,n,1);
	int T;scanf("%d",&T);
	while(T--){
		scanf("%s%d",ch,&x);x++;
		if(ch[0]=='i'){
			if(query(1,1,n,dfn[x])==1){printf("%d\n",0);continue;}
			int pos=find(x,0);
			printf("%d\n",dep[x]-dep[belong[pos]]+1);
			modify_sum(belong[pos],x);
		}
		if(ch[0]=='u'){
			if(query(1,1,n,dfn[x])==0){printf("%d\n",0);continue;}
			printf("%d\n",query_zakres(1,1,n,in[x],out[x]));
			modify(1,1,n,in[x],out[x],0);
		}
	}
	return 0;
}
