#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 500010
#define mod 201314
using namespace std;
int son[maxn],top[maxn],fa[maxn],sz[maxn],dfn[maxn],dep[maxn];
int n,head[maxn],m,id,num;
struct node{int to,pre;}e[maxn*2];
struct question{int r,flag,num;}a[maxn*2];
struct ques{int z,id,ans1,ans2;}q[maxn];
struct Segment{int l,r,v,lazy;}tr[maxn];
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
void dfs1(int x,int father){
	sz[x]=1;
	fa[x]=father;
	dep[x]=dep[father]+1;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father)continue;
		dfs1(to,x);
		sz[x]+=sz[to];
		if(!son[x]||(sz[son[x]]<sz[to]))son[x]=to;
	}
}
void dfs2(int x,int father){
	dfn[x]=++id;
	top[x]=father;
	if(son[x])dfs2(son[x],father);
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if((to==son[x])||(to==fa[x]))continue;
		dfs2(to,to);
	} 
}
void build(int l,int r,int k){
	tr[k].l=l;tr[k].r=r;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(l,mid,k<<1);build(mid+1,r,k<<1|1);
}
bool cmpa(question x,question y){
	return x.r<y.r;
}
void pushdown(int k){
	int l=k<<1,r=k<<1|1;
	tr[l].lazy+=tr[k].lazy;
	tr[r].lazy+=tr[k].lazy;
	tr[l].v+=1LL*(tr[l].r-tr[l].l+1)*tr[k].lazy%mod;tr[l].v%=mod;
	tr[r].v+=1LL*(tr[r].r-tr[r].l+1)*tr[k].lazy%mod;tr[r].v%=mod;
	tr[k].lazy=0;
}
void modify(int k,int l,int r,int opl,int opr){
	if(l>=opl&&r<=opr){
		tr[k].lazy++;tr[k].lazy%=mod;
		tr[k].v+=(tr[k].r-tr[k].l+1);tr[k].v%=mod;
		return;
	}
	if(tr[k].lazy)pushdown(k);
	int mid=(l+r)>>1;
	if(opl<=mid)modify(k<<1,l,mid,opl,opr);
	if(opr>mid)modify(k<<1|1,mid+1,r,opl,opr);
	tr[k].v=(tr[k<<1].v+tr[k<<1|1].v)%mod;
}
void update_sum(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		modify(1,1,n,dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y); 
	modify(1,1,n,dfn[x],dfn[y]);
}
int query(int k,int l,int r,int opl,int opr){
	if(l>=opl&&r<=opr)return tr[k].v;
	if(tr[k].lazy)pushdown(k);
	int mid=(l+r)>>1;
	int res=0;
	if(opl<=mid)res+=query(k<<1,l,mid,opl,opr);res%=mod;
	if(opr>mid)res+=query(k<<1|1,mid+1,r,opl,opr);res%=mod;
	return res;
}
int query_sum(int x,int y){
	int res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res+=query(1,1,n,dfn[top[x]],dfn[x]);
		res%=mod;
		x=fa[top[x]]; 
	}
	if(dep[x]>dep[y])swap(x,y);
	res+=query(1,1,n,dfn[x],dfn[y]);
	res%=mod;
	return res;
}
int main(){
	scanf("%d%d",&n,&m);
	int x,y,z;
	for(int i=2;i<=n;i++){
		scanf("%d",&x);
		x++;
		Insert(x,i);Insert(i,x);
	}
	dfs1(1,0);dfs2(1,1);
	build(1,n,1);
	int l,r,tot=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&l,&r,&q[i].z);
		l++;r++;q[i].z++;
		q[i].id=i;
		a[++tot].r=l-1;a[tot].num=i;a[tot].flag=0;
		a[++tot].r=r;a[tot].num=i;a[tot].flag=1;
	}
	sort(a+1,a+tot+1,cmpa);
	int now=0;
	for(int i=1;i<=tot;i++){
		while(now<a[i].r){
			now++;
			update_sum(1,now);
		}
		int t=a[i].num;
		if(!a[i].flag)q[t].ans1=query_sum(1,q[t].z);
		else q[t].ans2=query_sum(1,q[t].z);
	}
	for(int i=1;i<=m;i++){
		int ans=(q[i].ans2-q[i].ans1+mod)%mod;
		printf("%d\n",ans);
	}
}
