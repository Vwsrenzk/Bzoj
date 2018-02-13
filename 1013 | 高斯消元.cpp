/*
	令球心坐标为x1,x2...xn,假设当前第i个点坐标为a1,a2...,an，第i+1个点坐标为b1,b2...,bn，则由半径相等可得：
	(a1-x1)^2+(a2-x2)^2+...+(an-xn)^2=(b1-x1)^2+(b2-x2)^2+...+(bn-xn)^2
	化简可得:
	2(a1-b1)x1+2(a2-b2)x2+...+2(an-bn)xn=(a1^2+a2^2+...+an^2-b1^2-b2^2-...-b3^2)
	如此可得到n个n元一次方程组，用最简单的高斯消元搞一搞就好了。
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define maxn 15
using namespace std;
int n;
double pos[maxn][maxn],l[maxn][maxn];
void guess(){
	for(int i=1;i<=n;i++){
		int t=i;
		for(int j=i+1;j<=n;j++)
			if(fabs(l[j][i])>fabs(l[t][i]))t=j;
		if(t!=i)for(int j=i;j<=n+1;j++)swap(l[i][j],l[t][j]);
		for(int j=i+1;j<=n;j++){
			double x=l[j][i]/l[i][i];
			for(int k=i;k<=n+1;k++)l[j][k]-=l[i][k]*x;
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=i+1;j<=n;j++)l[i][n+1]-=l[j][n+1]*l[i][j];
		l[i][n+1]/=l[i][i];
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=n;j++){
			scanf("%lf",&pos[i][j]);
			if(i!=1){
				l[i-1][j]=2*(pos[i][j]-pos[i-1][j]);
				l[i-1][n+1]+=pos[i][j]*pos[i][j]-pos[i-1][j]*pos[i-1][j];
			}
		}
	guess();
	for(int i=1;i<=n;i++){
		printf("%.3lf",l[i][n+1]);
		if(i!=n)printf(" ");
	}
}
