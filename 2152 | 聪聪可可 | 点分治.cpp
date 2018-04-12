#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 20010
using namespace std;
int n,root,sum,ans,t[5],head[maxn],f[maxn],vis[maxn];
int son[maxn],d[maxn],num;
struct node{int to,pre,v;}e[maxn*2];
void Insert(int from,int to,int v){
	e[++num].to=to;
	e[num].v=v;
	e[num].pre=head[from];
	head[from]=num;
}
int gcd(int x,int y){
	if(y==0)return x;
	return gcd(y,x%y);
}
void getroot(int x,int father){
	son[x]=1;f[x]=0;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father||vis[to])continue;
		getroot(to,x);
		son[x]+=son[to];
		f[x]=max(f[x],son[to]);
	}
	f[x]=max(f[x],sum-son[x]);
	if(f[x]<f[root])root=x;
}
void getdep(int x,int father){
	t[d[x]]++;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father||vis[to])continue;
		d[to]=(d[x]+e[i].v)%3;
		getdep(to,x);
	}
}
int cal(int x,int v){
	t[0]=t[1]=t[2]=0;d[x]=v;
	getdep(x,0);
	return t[1]*t[2]*2+t[0]*t[0];
}
void solve(int x){
	ans+=cal(x,0);vis[x]=1;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(vis[to])continue;
		ans-=cal(to,e[i].v);
		root=0;sum=son[to];
		getroot(to,0);
		solve(root);
	}
}
int qread(){
	int i=0,j=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
	return i*j;
}
int main(){
	scanf("%d",&n);
	int x,y,z;
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);z%=3;
		Insert(x,y,z);Insert(y,x,z);
	}
	sum=n;f[0]=n;
	getroot(1,0);
	solve(root);
	int t=gcd(ans,n*n);
	printf("%d/%d\n",ans/t,n*n/t);
	return 0;
}
