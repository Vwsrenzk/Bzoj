#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 50010
using namespace std;
int head[maxn],num,n,m,cnt;
long long w[200010],dx[maxn],a[200010],b[70],ans;
bool vis[maxn];
struct node{int to,pre;}e[200010];
void Insert(int from,int to,long long v){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
	w[num]=v;
}
void dfs(int x){
	vis[x]=1;
	for(int i=head[x];i;i=e[i].pre){
		int to=e[i].to;
		if(!vis[to])dx[to]=dx[x]^w[i],dfs(to);
		else a[++cnt]=dx[to]^dx[x]^w[i];
	}
}
int main(){
	scanf("%d%d",&n,&m);
	int x,y;
	long long z;
	for(int i=1;i<=m;i++){
		scanf("%d%d%lld",&x,&y,&z);
		Insert(x,y,z);Insert(y,x,z);
	}
	dfs(1);
	ans=dx[n];
	for(int i=1;i<=cnt;i++)
		for(int j=63;j>=0;j--)
			if((a[i]>>j)&1){
				if(b[j])a[i]^=b[j];
				else{
					b[j]=a[i];
					for(int k=j-1;k>=0;k--)
						if(((b[j]>>k)&1)&&b[k])b[j]^=b[k];
					for(int k=j+1;k<=63;k++)
						if((b[k]>>j)&1)b[k]^=b[j];
					break;
				}
			}
	for(int i=63;i>=0;i--)
		if((ans^b[i])>ans)ans^=b[i];
	printf("%lld",ans);
	return 0;
}
