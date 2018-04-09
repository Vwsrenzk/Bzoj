/*回文自动机：https://blog.csdn.net/u013368721/article/details/42100363”*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 300010
using namespace std;
char s[maxn];
int nxt[maxn][26],fail[maxn],str[maxn],cnt[maxn],len[maxn],sz=-1,last,tot,n;
int creat(int x){
	len[++sz]=x;return sz;
}
void prepare(){
	creat(0);
	creat(-1);
	str[0]=str[1]=-1;
	last=0;
	fail[0]=1;
}
int getfail(int x){
	while(str[n-len[x]-1]!=str[n])x=fail[x];
	return x;
}
void Insert(int c){
	str[++n]=c;
	int cur=getfail(last),now;
	if(!nxt[cur][c]){
		now=creat(len[cur]+2);
		fail[now]=nxt[getfail(fail[cur])][c];
		nxt[cur][c]=now;
	}
	last=nxt[cur][c];
	cnt[last]++;
}
void count(){
	for(int i=sz;i>=0;i--)cnt[fail[i]]+=cnt[i];
}
long long solve(){
	long long res=0;
	for(int i=sz;i>=0;i--)res=max(res,1LL*len[i]*cnt[i]);
	return res;
}
int main(){
	prepare();
	scanf("%s",s);
	int le=strlen(s);
	for(int i=0;i<le;i++)
		Insert(s[i]-'a');
	count();
	cout<<solve();
	return 0;
}
