#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1000010
using namespace std;
int n1,n2,fail[maxn],nxt[maxn],top;
char s1[maxn],s2[maxn],s3[maxn];
void getfail(){
	fail[1]=0;
	for(int i=2;i<=n2;i++){
		int p=fail[i-1];
		while(p&&(s2[p+1]!=s2[i]))p=fail[p];
		if(s2[p+1]==s2[i])p++;
		fail[i]=p;
	}
}
int main(){
	scanf("%s%s",s1+1,s2+1);
	n1=strlen(s1+1);n2=strlen(s2+1);
	getfail();
	for(int i=1;i<=n1;i++){
		s3[++top]=s1[i];
		int p=nxt[top-1];
		while(p&&s1[i]!=s2[p+1])p=fail[p];
		if(s1[i]==s2[p+1])p++;
		nxt[top]=p;
		if(p==n2)top-=n2;
	}
	for(int i=1;i<=top;i++)printf("%c",s3[i]);
	return 0;
}
