#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 25
using namespace std;
int n,m,mod,p[maxn];
char s[maxn];
struct matrix{
	int zu[maxn][maxn];
	matrix(){memset(zu,0,sizeof(zu));}
	matrix operator * (const matrix x)const{
		matrix res;
		for(int i=0;i<m;i++)
			for(int j=0;j<m;j++)
				for(int k=0;k<m;k++)
					res.zu[i][j]=(res.zu[i][j]+zu[i][k]*x.zu[k][j]%mod)%mod;
		return res;
	}
}a;
void kmp(){
	p[0]=-1;
	int j=-1;
	for(int i=1;i<=m;p[i++]=++j)
		while(j!=-1&&s[i]!=s[j+1])j=p[j];
}
matrix Pow(matrix x,int y){
	y--;matrix res=x;
	while(y){
		if(y&1)res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
int find(int j,int k){
	while(j!=-1&&s[j+1]!=char(k+'0'))j=p[j];
	return j+1;
}
int main(){
	scanf("%d%d%d",&n,&m,&mod);
	scanf("%s",s+1);
	kmp();
	for(int j=0;j<m;j++)
		for(int i=0;i<=9;i++)
			a.zu[j][find(j,i)]++;
	a=Pow(a,n);
	int ans=0;
	for(int i=0;i<m;i++)ans=(ans+a.zu[0][i])%mod;
	printf("%d",ans);
	return 0;
}
