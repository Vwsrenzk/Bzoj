#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 200010
#define INF 1000000000
using namespace std;
int n,ans,head[maxn],num,To[maxn][2],mx[maxn][2],f[maxn];
struct node{int to,pre,v;}e[maxn*2];
void Insert(int from,int to,int v){
	e[++num].to=to;
	e[num].v=v;
	e[num].pre=head[from];
	head[from]=num;
}
void update(int now,int to,int v){
	if(v>mx[now][0]){
		mx[now][0]=v;
		To[now][0]=to;
	}
	if(mx[now][0]>mx[now][1]){
		swap(mx[now][0],mx[now][1]);
		swap(To[now][0],To[now][1]);
	}
}
void dfs(int now,int father){
	f[now]=0;
	mx[now][1]=mx[now][0]=-INF;
	To[now][1]=To[now][0]=0;
	for(int i=head[now];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father)continue;
		dfs(to,now);
		int tmp=max(f[to],f[to]+mx[to][1]+e[i].v);
		f[now]+=tmp;
		update(now,to,-tmp+f[to]+e[i].v);
	}
}
void move_root(int now,int father){
	ans=max(ans,f[now]);
	for(int i=head[now];i;i=e[i].pre){
		int to=e[i].to;
		if(to==father)continue;
		int tmp=max(f[to],f[to]+mx[to][1]+e[i].v);
		int cur=max(f[now]-tmp,f[now]-tmp+(to==To[now][1]?mx[now][0]:mx[now][1])+e[i].v);
		f[to]+=cur;
		update(to,now,-cur-tmp+f[now]+e[i].v);
		move_root(to,now);
	}
}
int main(){
	scanf("%d",&n);
	int x,y,z;
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&z);
		Insert(x,y,z);Insert(y,x,z);
	}
	dfs(1,0);
	move_root(1,0);
	printf("%d",ans);
	return 0;
}
