/*
	由于只满足三角关系，可知根据关系建图之后图为弦图。 
	那么问题转化成了弦图的最小染色。
	
	算法过程： 
	用MCS算法求出弦图的完美消除序列。 
	完美消除序列从后往前一次染色，给每个点染上可以染的最小颜色。 
	最大势算法 Maximum Cardinality Search 
	从n到1的顺序依次给点标号(标号为i的点出现在完美消除序列的第i个)。 
	设size[i]表示第i个点与多少个已标号的点相 邻，每次选择size[i]最大的未标号的点进行标号。
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 10010
using namespace std;
int n,m,ans,num,head[maxn],sz[maxn],flag[maxn],col[maxn],pt[maxn];
struct node{int to,pre;}e[2000010];
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		Insert(x,y);Insert(y,x);
	}
	for(int i=n;i>=1;i--){//用MCS算法求出弦图的完美消除序列 
		int cur=0;
		for(int j=1;j<=n;j++)
			if(!flag[j]&&sz[j]>=sz[cur])cur=j;
		flag[cur]=1;pt[i]=cur;
		for(int j=head[cur];j;j=e[j].pre)sz[e[j].to]++;
	}
	memset(flag,0,sizeof(flag));
	for(int i=n;i>=1;i--){//最大势算法 
		for(int j=head[pt[i]];j;j=e[j].pre)
			flag[col[e[j].to]]=i;
		col[pt[i]]=1;
		while(flag[col[pt[i]]]==i)col[pt[i]]++;
		ans=max(ans,col[pt[i]]);
	}
	printf("%d",ans);
	return 0;
}
