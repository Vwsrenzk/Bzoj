#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 30
using namespace std;
int n,m,A,B,tot,d[maxn],head[maxn*maxn],num;
double p[maxn],a[maxn*maxn][maxn*maxn];
struct node{int to,pre;}e[maxn*maxn*maxn*maxn];
int count(int x,int y){return (x-1)*n+y;}
void Insert(int from,int to){
	e[++num].to=to;
	e[num].pre=head[from];
	head[from]=num;
}
void build(int x1,int x2){
	a[count(x1,x2)][count(x1,x2)]--;
	for(int i=head[x1];i;i=e[i].pre){
		for(int j=head[x2];j;j=e[j].pre){
			int y1=e[i].to,y2=e[j].to;
			int c1=count(x1,x2),c2=count(y1,y2);
			if(y1!=y2){
				if(y1==x1&&y2==x2)a[c1][c2]+=p[y1]*p[y2];
				else if(y1==x1)a[c1][c2]+=p[y1]*(1-p[y2])/d[y2];
				else if(y2==x2)a[c1][c2]+=p[y2]*(1-p[y1])/d[y1];
				else a[c1][c2]+=(1-p[y1])*(1-p[y2])/d[y1]/d[y2];
			}
		}
	}
}
void Gauss(){
	int now=1;
	for(int i=1;i<=tot;i++){
		int tmp=now;
		while(!a[tmp][now]&&tmp<=tot)tmp++;
		for(int j=1;j<=tot+1;j++)swap(a[now][j],a[tmp][j]);
		for(int j=1;j<=tot;j++){
			if(j==now)continue;
			double t=a[j][now]/a[now][now];
			for(int k=1;k<=tot+1;k++)a[j][k]-=t*a[now][k];
		}
		now++;
	}
}
int main(){
	scanf("%d%d%d%d",&n,&m,&A,&B);
	tot=n*n;
	a[count(A,B)][tot+1]=-1;
	for(int i=1;i<=n;i++)Insert(i,i);
	int x,y;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		d[x]++;d[y]++;
		Insert(x,y);Insert(y,x);
	}
	for(int i=1;i<=n;i++)scanf("%lf",&p[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)build(i,j);
	Gauss();
	for(int i=1;i<=n;i++){
		int tmp=count(i,i);
		printf("%.6lf",a[tmp][tot+1]/a[tmp][tmp]);
		if(i!=n)printf(" ");
	}
	return 0;
}
