#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1000010
using namespace std;
int n,nxt[maxn];
char s[maxn];
void getnxt(){
	nxt[0]=-1;
	int i=0,j=-1;
	while(i<n){
		if((j==-1)||(s[i]==s[j])){
			i++;j++;
			nxt[i]=j;
		}
		else j=nxt[j];
	}
}
int main(){
	scanf("%d%s",&n,s);
	getnxt();
	long long ans=0;
	for(int i=1;i<=n;i++){
		if(!nxt[i])continue;
		while(nxt[nxt[i]])nxt[i]=nxt[nxt[i]];
	}
	for(int i=1;i<=n;i++)
		if(nxt[i])ans+=i-nxt[i];
	cout<<ans;
}
