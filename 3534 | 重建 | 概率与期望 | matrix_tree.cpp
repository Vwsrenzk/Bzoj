/*
3534: [Sdoi2014]重建

Time Limit: 10 Sec  Memory Limit: 512 MBSec  Special Judge
Submit: 1205  Solved: 590
[Submit][Status][Discuss]
Description

  T国有N个城市，用若干双向道路连接。一对城市之间至多存在一条道路。
    在一次洪水之后，一些道路受损无法通行。虽然已经有人开始调查道路的损毁情况，但直到现在几乎没有消息传回。
    辛运的是，此前T国政府调查过每条道路的强度，现在他们希望只利用这些信息估计灾情。具体地，给定每条道路在洪水后仍能通行的概率，请计算仍能通行的道路恰有N-1条，且能联通所有城市的概率。

Input

  输入的第一行包含整数N。
  接下来N行，每行N个实数，第i+l行，列的数G[i][j]表示城市i与j之
间仍有道路联通的概率。
    输入保证G[i][j]=G[j][i]，且G[i][j]=0；G[i][j]至多包含两位小数。

Output


    输出一个任意位数的实数表示答案。
    你的答案与标准答案相对误差不超过10^(-4)即视为正确。


Sample Input



    3

    0 0.5 0.5

    0.5 0 0.5

    0.5 0.5 0

Sample Output

    0.375
HINT

1 < N < =50


数据保证答案非零时，答案不小于10^-4
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define maxn 55
#define eps 1e-8
using namespace std;
int n;
double a[maxn][maxn];
double Gauss(int n){
	double res=1;
	for(int i=1;i<=n;i++){
		int k=i;
		for(int j=i+1;j<=n;j++){if(fabs(a[j][i])>fabs(a[k][i]))k=j;}
		if(i!=k){for(int j=1;j<=n;j++)swap(a[i][j],a[k][j]);}
		if(fabs(a[i][i])<eps)return 0;
		for(int j=i+1;j<=n;j++){
			double t=a[j][i]/a[i][i];
			for(int k=i;k<=n;k++)a[j][k]-=a[i][k]*t;
		}
		res*=a[i][i];
	}
	return fabs(res);
}
int main(){
	double tmp=1.0,ans;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			scanf("%lf",&a[i][j]);
			if(i==j)continue;
			if(a[i][j]>1.0-eps)a[i][j]-=eps;
			if(i<j)tmp*=1-a[i][j];
			a[i][j]/=1-a[i][j];
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)a[i][i]+=a[i][j],a[i][j]=-a[i][j];
	ans=Gauss(n-1)*tmp;
	printf("%.10lf",ans);
	return ans;
}
