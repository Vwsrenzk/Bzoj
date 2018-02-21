#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 100010
using namespace std;
struct node{
	int n,m,a,id;
	bool operator < (const node &x)const{
		return a<x.a;
	}
}q[40010];
bool vis[maxn];
int p[maxn],mu[maxn],t[maxn],ans[maxn],T,cnt,mx;
pair<int,int>F[maxn];
void prepare(){
	mu[1]=1;
	for(int i=2;i<=mx;i++){
		if(!vis[i]){p[++cnt]=i;mu[i]=-1;}
		for(int j=1;j<=cnt&&(i*p[j]<=mx);j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0){mu[i*p[j]]=0;break;}
			else mu[i*p[j]]=-mu[i];
		}
	}
	for(int i=1;i<=mx;i++)
		for(int j=i;j<=mx;j+=i)F[j].first+=i;
	for(int i=1;i<=mx;i++)F[i].second=i;
}
int add(int x,int val){
	for(int i=x;i<=mx;i+=i&(-i))t[i]+=val;
}
int query(int x){
	int tmp=0;
	for(int i=x;i;i-=i&(-i))tmp+=t[i];
	return tmp;
}
void solve(int x){
	int id=q[x].id,n=q[x].n,m=q[x].m;
	for(int i=1,j;i<=q[x].n;i=j+1){
		j=min(n/(n/i),m/(m/i));
		ans[id]+=(n/i)*(m/i)*(query(j)-query(i-1));
	}
}
int main(){
	scanf("%d",&T);
	for(int i=1;i<=T;i++){
		scanf("%d%d%d",&q[i].n,&q[i].m,&q[i].a);
		q[i].id=i;
		if(q[i].n>q[i].m)swap(q[i].n,q[i].m);
		mx=max(mx,q[i].n);
	}
	prepare();
	sort(q+1,q+T+1);
	sort(F+1,F+mx+1);
	int now=0;
	for(int i=1;i<=T;i++){
		while(now+1<=mx&&F[now+1].first<=q[i].a){
			now++;
			for(int j=F[now].second;j<=mx;j+=F[now].second)
				add(j,F[now].first*mu[j/F[now].second]);
		}
		solve(i);
	}
	for(int i=1;i<=T;i++)printf("%d\n",ans[i]&0x7fffffff);
	return 0;
}
