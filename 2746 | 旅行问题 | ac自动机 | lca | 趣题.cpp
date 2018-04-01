#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define mod 1000000007
#define maxn 1000010
using namespace std;
int dis[maxn],st[maxn],ed[maxn*2],tim,sz=1,tr[maxn][27],dep[maxn],fail[maxn][20];
int n,m,s1,s2,l1,l2;
char s[maxn];
void Insert(){
	int len=strlen(s),now=1;
	for(int i=0;i<len;i++){
		int tmp=s[i]-'a';
		if(!tr[now][tmp]){
			tr[now][tmp]=++sz;
			dis[tr[now][tmp]]=(1LL*26*dis[now]+tmp)%mod;
		}
		now=tr[now][tmp];
		ed[++tim]=now;
	}
}
queue<int>q;
void build(){
	fail[1][0]=1;
	for(int i=0;i<26;i++)
		if(tr[1][i]){
			q.push(tr[1][i]);
			fail[tr[1][i]][0]=1;
		}
	while(!q.empty()){
		int now=q.front();q.pop();
		if(now!=1)dep[now]=dep[fail[now][0]]+1;
		for(int i=1;i<20;i++)fail[now][i]=fail[fail[now][i-1]][i-1];
		for(int i=0;i<26;i++){
			if(tr[now][i]){
				int p=fail[now][0];
				while(p!=1&&!tr[p][i])p=fail[p][0];
				if(tr[p][i])fail[tr[now][i]][0]=tr[p][i];
				else fail[tr[now][i]][0]=1;
				q.push(tr[now][i]);
			}
		}
	}
}
int getlca(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	int delta=dep[x]-dep[y];
	for(int i=19;i>=0;i--)
		if((1<<i)&delta)x=fail[x][i];
	for(int i=19;i>=0;i--){
		if(fail[x][i]!=fail[y][i])
			x=fail[x][i],y=fail[y][i];
	}
	if(x!=y)x=fail[x][0];
	return x;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		st[i]=tim;
		Insert();
	}
	build();
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&s1,&l1,&s2,&l2);
		int p1=ed[st[s1]+l1];
		int p2=ed[st[s2]+l2];
		int lca=getlca(p1,p2);
		printf("%d\n",dis[lca]);
	}
	return 0;
}
