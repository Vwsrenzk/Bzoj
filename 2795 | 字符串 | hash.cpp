#include<iostream>
#include<cstdio>
#include<cstring>
#define p 31
#define maxn 500010
using namespace std;
int n,m,count[maxn][27],ans;
long long Hash[maxn],base[maxn];
char s[maxn];
void get_hash(){
	base[0]=1;
	for(int i=1;i<=n;i++){
		Hash[i]=Hash[i-1]*p+s[i]-'a';
		base[i]=base[i-1]*p;
	}
}
int gcd(int x,int y){
	if(y==0)return x;
	return gcd(y,x%y);
}
void getans(int l,int r,int t){
	int len=r-l+1-t;
	long long Hash1=Hash[r]-Hash[r-len]*base[len];
	long long Hash2=Hash[l+len-1]-Hash[l-1]*base[len];
	if(Hash1==Hash2)ans=min(ans,t);
}
int main(){
	scanf("%d%s%d",&n,s+1,&m);
	get_hash();
	for(int i=1;i<=n;i++)
		for(int j=0;j<26;j++)
			count[i][j]=count[i-1][j]+(s[i]-'a'==j);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		int len;
		len=ans=y-x+1;
		int vgcd=y-x+1;
		for(int i=0;i<26;i++)
			vgcd=gcd(vgcd,count[y][i]-count[x-1][i]);
		for(int i=1;i*i<=vgcd;i++){
			if(vgcd%i)continue;
			getans(x,y,len/i);
			getans(x,y,len/(vgcd/i));
		}
		printf("%d\n",ans);
	}
}
