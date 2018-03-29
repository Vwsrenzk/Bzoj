#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 20010
#define INF 1000000000
#ifdef WIN32
#define PLL "%I64d"
#else 
#define PLL "%lld"
#endif
using namespace std;
struct node{
	int x,y,w,pos;
	bool operator < (const node &y)const{
		return w<y.w;
	}
}e[25][50010],d[50010],t[50010];
struct Node{int x,y;}q[50010];
int sum[maxn],fa[maxn],sz[maxn],c[50010],a[50010];
int n,m,Q;
long long ans[50010];
int find(int x){
	if(x==fa[x])return x;
	return fa[x]=find(fa[x]);
}
void clear(int tot){
	for(int i=1;i<=tot;i++){
		fa[d[i].x]=d[i].x;
		fa[d[i].y]=d[i].y;
		sz[d[i].x]=sz[d[i].y]=1;
	}
}
void merge(int x,int y){
	if(sz[x]<sz[y])sz[y]+=sz[x],fa[x]=y;
	else sz[x]+=sz[y],fa[y]=x;
}
void contraction(int &tot,long long &cnt){
	int tmp=0;
	clear(tot);
	sort(d+1,d+tot+1);
	for(int i=1;i<=tot;i++)
		if(find(d[i].x)!=find(d[i].y)){
			merge(fa[d[i].x],fa[d[i].y]);
			t[++tmp]=d[i];
		}
	for(int i=1;i<=tmp;i++){
		fa[t[i].x]=t[i].x;
		fa[t[i].y]=t[i].y;
		sz[t[i].x]=sz[t[i].y]=1;
	}
	for(int i=1;i<=tmp;i++)
		if(t[i].w!=-INF&&find(t[i].x)!=find(t[i].y)){
			merge(fa[t[i].x],fa[t[i].y]);
			cnt+=t[i].w;
		}
	tmp=0;
	for(int i=1;i<=tot;i++)
		if(find(d[i].x)!=find(d[i].y)){
			t[++tmp]=d[i];
			c[d[i].pos]=tmp;
			t[tmp].x=fa[d[i].x];
			t[tmp].y=fa[d[i].y];
		}
	for(int i=1;i<=tmp;i++)d[i]=t[i];
	tot=tmp;
}
void reduction(int &tot){
	int tmp=0;
	clear(tot);
	sort(d+1,d+tot+1);
	for(int i=1;i<=tot;i++){
		if(find(d[i].x)!=find(d[i].y)){
			merge(fa[d[i].x],fa[d[i].y]);
			t[++tmp]=d[i];
			c[d[i].pos]=tmp;
		}
		else if(d[i].w==INF){
			t[++tmp]=d[i];
			c[d[i].pos]=tmp;
		}
	}
	for(int i=1;i<=tmp;i++)d[i]=t[i];
	tot=tmp;
}
void solve(int l,int r,int now,long long cnt){
	int tot=sum[now];
	if(l==r)a[q[l].x]=q[l].y;//第k个道路的修建代价修改为d
	for(int i=1;i<=tot;i++)e[now][i].w=a[e[now][i].pos];
	for(int i=1;i<=tot;i++)d[i]=e[now][i],c[d[i].pos]=i;
	if(l==r){
		ans[l]=cnt;
		clear(tot);
		sort(d+1,d+1+tot);
		for(int i=1;i<=tot;i++)
			if(find(d[i].x)!=find(d[i].y)){
				merge(fa[d[i].x],fa[d[i].y]);
				ans[l]+=d[i].w;
			}
		return;
	}
	for(int i=l;i<=r;i++)d[c[q[i].x]].w=-INF;
	contraction(tot,cnt);
	for(int i=l;i<=r;i++)d[c[q[i].x]].w=INF;
	reduction(tot);
	for(int i=1;i<=tot;i++)e[now+1][i]=d[i];
	sum[now+1]=tot;
	int mid=(l+r)>>1;
	solve(l,mid,now+1,cnt);
	solve(mid+1,r,now+1,cnt);
}
int main(){
	scanf("%d%d%d",&n,&m,&Q);
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&a[i]);
		e[0][i].x=x;e[0][i].y=y;
		e[0][i].w=a[i];e[0][i].pos=i;
	}
	for(int i=1;i<=Q;i++)
		scanf("%d%d",&q[i].x,&q[i].y);
	sum[0]=m;
	solve(1,Q,0,0);
	for(int i=1;i<=Q;i++)printf(PLL"\n",ans[i]);
	return 0;
}
/*
2001: [Hnoi2010]City 城市建设

Time Limit: 20 Sec  Memory Limit: 162 MB
Submit: 1557  Solved: 781
[Submit][Status][Discuss]
Description

PS国是一个拥有诸多城市的大国，国王Louis为城市的交通建设可谓绞尽脑汁。Louis可以在某些城市之间修建道路，在不同的城市之间修建道路需要不同的花费。Louis希望建造最少的道路使得国内所有的城市连通。但是由于某些因素，城市之间修建道路需要的花费会随着时间而改变，Louis会不断得到某道路的修建代价改变的消息，他希望每得到一条消息后能立即知道使城市连通的最小花费总和， Louis决定求助于你来完成这个任务。

Input

文件第一行包含三个整数N,M,Q，分别表示城市的数目，可以修建的道路个数，及收到的消息个数。 接下来M行，第i+1行有三个用空格隔开的整数Xi,Yi,Zi(1≤Xi,Yi≤n, 0≤Zi≤50000000)，表示在城市Xi与城市Yi之间修建道路的代价为Zi。接下来Q行，每行包含两个数k,d，表示输入的第k个道路的修建代价修改为d(即将Zk修改为d)。

Output

输出包含Q行，第i行输出得知前i条消息后使城市连通的最小花费总和。

Sample Input

5 5 3

1 2 1

2 3 2

3 4 3

4 5 4

5 1 5

1 6

1 1

5 3



Sample Output

14

10

9

HINT

【数据规模】 对于20%的数据, n≤1000,m≤6000,Q≤6000。 有20%的数据，n≤1000,m≤50000,Q≤8000,修改后的代价不会比之前的代价低。 对于100%的数据, n≤20000,m≤50000,Q≤50000。
两个关键的操作：
  Reduction(删除无用边)：
  把待修改的边标为INF，做一遍MST，把做完后不在MST中的非INF边删去（因为这些边在原图的情况下肯定更不可能选进MST的边集，即无用边）；
  Contraction(缩必须边)：
  把待修改的边标为-INF，做一遍MST，在MST中的非-INF边为必须边（因为这些边在原图的情况下也一定会被选进MST），缩点。
讲课的时候说经过R-C-R的过程，图的规模的变化就是：(n,m) -> (n,n + k - 1) -> (k + 1,n + k - 1) -> (k + 1,2 * k)。不过我已经忘了k是啥了= =反正意思就说图就缩小了很多。但是zigzag神犇的程序里面只有C-R，可能只要这样就能很优了吧。
在做contraction的时候，缩了的边权也要统计起来。当l == r的时候要使修改操作生效（因为前面的操作会影响后面的答案），并统计此时的MST的答案。
还有很巧妙的就是，他记录了每一层的图，这样回溯的时候还原起来会方便一些。还有一个数组记录第i个元素在当前表中的位置，能方便修改边权之类的操作。
*/
