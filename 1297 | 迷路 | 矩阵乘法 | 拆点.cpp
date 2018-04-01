#include<iostream>
#include<cstdio>
#include<cstring>
#define mod 2009
using namespace std;
int n,m,t;
struct matrix{
	int a[110][110];
	matrix(){memset(a,0,sizeof(a));}
	matrix operator * (const matrix &b)const{
		matrix res;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++){
					res.a[i][j]+=a[i][k]*b.a[k][j]%mod;
					res.a[i][j]%=mod;
				}
		return res;
	}
}a,map;
int count(int x,int y){
	return (y-1)*m+x;
}
void Power(int y){
	while(y){
		if(y&1)a=a*map;
		map=map*map;
		y>>=1;
	}
}
int main(){
	scanf("%d%d",&m,&t);n=m*9;
	for(int i=1;i<=m;i++)
		for(int j=2;j<=9;j++)
			map.a[count(i,j)][count(i,j-1)]=1;
	int x,last;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++){
			scanf("%1d",&x);
			if(x==0)continue;
			map.a[i][count(j,x)]=1;
		}
	for(int i=1;i<=n;i++)a.a[i][i]=1;
	Power(t);
	printf("%d",a.a[1][m]);
	return 0;
}
