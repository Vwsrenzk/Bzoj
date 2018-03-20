#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 5010
using namespace std;
int head[maxn],num,cnt,ans,a,b,c,idx,vis[maxn],match[maxn];
struct node{int to,pre;}e[maxn];
struct Node{int x,y,z;}p[maxn];
void Insert(int from,int to){
	e[++num].to=to;e[num].pre=head[from];head[from]=num;
}
bool dfs(int x){
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(vis[to]!=idx){
			vis[to]=idx;
			if(!match[to]||dfs(match[to])){match[to]=x;return 1;}
		}
	}
	return 0;
}
int work(int sta){
	memset(head,0,sizeof(head));num=1;idx=0;
	memset(vis,0,sizeof(vis));
	memset(match,0,sizeof(match));
	for(int i=1;i<=cnt;i++)
		if(sta&(1<<(p[i].z-1)))Insert(p[i].x,p[i].y);
	int ans=0;
	while(sta){
		ans+=(sta&1);
		sta>>=1;
	}
	ans=c-ans;
	for(int i=1;i<=a;i++){
		++idx;
		if(dfs(i))ans++;
	}
	return ans;
}
int qread(){
	int i=0,j=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
	return i*j;
}
int main(){
	int T;T=qread();
	while(T--){
		cnt=0;
		a=qread();b=qread();c=qread();
		int w;
		for(int i=1;i<=a;i++)
			for(int j=1;j<=b;j++)
				for(int k=1;k<=c;k++){
					w=qread();
					if(w){
						p[++cnt].x=i;
						p[cnt].y=j;
						p[cnt].z=k;
					}
				}
		if(a<b&&a<c){
			for(int i=1;i<=cnt;i++)swap(p[i].x,p[i].z);
			swap(a,c);
		}
		else if(b<a&&b<c){
			for(int i=1;i<=cnt;i++)swap(p[i].y,p[i].z);
			swap(b,c);
		}
		ans=c;
		for(int i=0;i<=(1<<c)-1;i++){ans=min(ans,work(i));}
		printf("%d\n",ans);
	}
	return 0;
}
