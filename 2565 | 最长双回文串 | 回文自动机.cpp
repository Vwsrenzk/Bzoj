/*不知道为啥要正着做一遍，反着做一遍*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
using namespace std;
char s[maxn];
int nxt[maxn][30],fail[maxn],len[maxn],str[maxn],sz=-1,last,n,a[maxn];
int creat(int l){
	len[++sz]=l;return sz;
}
void prepare(){
	last=n=0;sz=-1;
	memset(fail,0,sizeof(fail));
	memset(nxt,0,sizeof(nxt));
	creat(0);
	creat(-1);
	str[0]=-1;
	last=0;
	fail[0]=1;
}
int getfail(int x){
	while(str[n-len[x]-1]!=str[n])x=fail[x];
	return x;
}
void Insert(int c,int id){
	str[++n]=c;
	int cur=getfail(last),now;
	if(!nxt[cur][c]){
		now=creat(len[cur]+2);
		fail[now]=nxt[getfail(fail[cur])][c];
		nxt[cur][c]=now;
	}
	last=nxt[cur][c];
	a[id]=last;
}
int main(){
	prepare();
	scanf("%s",s);
	int l=strlen(s);
	for(int i=0;i<l;i++)
		Insert(s[i]-'a'+1,i);
	int ans=0;
	for(int i=0;i<l;i++)
		ans=max(ans,len[a[i]]+len[a[i-len[a[i]]]]);
	prepare();
	for(int i=l-1;i>=0;i--)
		Insert(s[i]-'a'+1,i);
	for(int i=0;i<l;i++)
		ans=max(ans,len[a[i]]+len[a[i+len[a[i]]]]);
	printf("%d",ans);
	return 0;
}
