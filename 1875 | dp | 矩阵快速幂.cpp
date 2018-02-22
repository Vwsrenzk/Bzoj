#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 200
#define mod 45989
using namespace std;
int head[maxn],num=-1;
struct node{int to,pre,nxt;}e[maxn*2];
struct matrix{
	int n,m,zu[maxn][maxn];
	matrix(int n_,int m_){n=n_;m=m_;memset(zu,0,sizeof(zu));}
	matrix operator * (const matrix &x)const{
		matrix res(n,x.m);
		for(int i=0;i<=n;i++)
			for(int j=0;j<=x.m;j++)
				for(int k=0;k<=m;k++)
					res.zu[i][j]=(res.zu[i][j]+1LL*zu[i][k]*x.zu[k][j]%mod)%mod;
		return res;
	}
};
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
matrix Pow(matrix z,matrix x,int y){
	while(y){
		if(y&1)z=z*x;
		x=x*x;
		y>>=1;
	}
	return z;
}
int main(){
	memset(head,-1,sizeof(head));
	int n,m,x,y,tim,s,t;
	scanf("%d%d%d%d%d",&n,&m,&tim,&s,&t);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		Insert(x,y);Insert(y,x);
	}
	matrix a(num,num);matrix b(0,num);
	for(int i=head[s];i!=-1;i=e[i].pre){b.zu[0][i]++;}
	for(int i=0;i<=num;i++){
		int now=e[i].to;
		for(int j=head[now];j!=-1;j=e[j].pre)
			if(j!=(i^1))a.zu[i][j]++;
	}
	matrix ans=Pow(b,a,tim-1);
	int Ans=0;
	for(int i=0;i<=num;i++)
		if(e[i].to==t)Ans=(Ans+ans.zu[0][i])%mod;
	printf("%d",Ans);
	return 0;
}
