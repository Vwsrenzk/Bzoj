#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long f[5][40];
int g[5][40],a[10],b[10],n;
int main(){
	char s[5];
	scanf("%d",&n);
	for(int i=1;i<=6;i++){
		scanf("%s",s+1);
		a[i]=s[1]-'A'+1;b[i]=s[2]-'A'+1;
	}
	for(int i=6;i>=1;i--)g[a[i]][1]=b[i];
	for(int i=1;i<=3;i++)f[i][1]=1LL;
	for(int i=2;i<=n;i++){
		for(int x=1;x<=3;x++){
			int y=g[x][i-1];int z=6-x-y;
			if(g[y][i-1]==z){
				f[x][i]=f[x][i-1]+1+f[y][i-1];
				g[x][i]=z;
			}
			else if(g[y][i-1]==x){
				f[x][i]=f[x][i-1]+1+f[y][i-1]+1+f[x][i-1];
				g[x][i]=y;
			}
		}
	}
	printf("%lld",f[1][n]);
	return 0;
}
