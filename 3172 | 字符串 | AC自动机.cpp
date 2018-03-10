#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1000010
using namespace std;
char s[maxn];
int tr[maxn][27],n,h,t,q[maxn],fail[maxn],cnt[maxn],val[maxn],sz=1;
void Insert(int x){
	int now=1,len=strlen(s+1);
	for(int i=1;i<=len;i++){
		int tmp=s[i]-'a';
		if(!tr[now][tmp])tr[now][tmp]=++sz;
		now=tr[now][tmp];
		cnt[now]++;
	}
	val[x]=now;
}
void build_AC(){
	h=t=0;q[++t]=1;
	while(h<t){
		int now=q[++h];
		for(int i=0;i<26;i++){
			if(!tr[now][i])continue;
			int p=fail[now];
			while(!tr[p][i])p=fail[p];
			fail[tr[now][i]]=tr[p][i];
			q[++t]=tr[now][i];
		}
	}
}
void solve(){
	for(int i=t;i;i--)cnt[fail[q[i]]]+=cnt[q[i]];
	for(int i=1;i<=n;i++)printf("%d\n",cnt[val[i]]);
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<26;i++)tr[0][i]=1;
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		Insert(i);
	}
	build_AC();
	solve();
	return 0;
}
