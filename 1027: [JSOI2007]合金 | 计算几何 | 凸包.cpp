/*
	题目大意：
	有n种材料，每种材料由3种金属合成，比例为ai:bi:ci
	有m种合金需要合成，每种合金也需要一定比例的三种金属，问要满足所有合金都合成，最少需要多少材料 
	
	题解： 
	若只有两种材料，那么可以合成两点线段上的所有的点
	推广到多种材料：
	若用户点在材料点构成的凸包内，则可以合成
	所以题目转化为 求材料点 组成的 能包含所有用户点 的 最小环
	用Floyd
	枚举每两对材料点，若所有用户点在在线段的左侧或在线段
	则f[i][j]=1表示i到j之间有一条边
	叉积判断点在直线的哪一侧
	所以如果是在 直线上，还要特判是否在线段上
*/ 
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 510
#define eps 0.0000000001
#define INF 1000000007
using namespace std;
double x[maxn],y[maxn],a[maxn],b[maxn];
int f[maxn][maxn];
int n,m;
int floyed(){
    for(int k=1;k<=m;k++){
        for(int i=1;i<=m;i++){
            if(f[i][k]<INF)
            for(int j=1;j<=m;j++){
                f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
            }
        }
    }
    int ans=INF;
    for(int i=1;i<=m;i++)ans=min(ans,f[i][i]);
    if(ans==INF)return -1;
    return ans;
}
int main(){
    scanf("%d%d",&m,&n);
    double p;
    for(int i=1;i<=m;i++)scanf("%lf%lf%lf",&x[i],&y[i],&p);
    for(int i=1;i<=n;i++)scanf("%lf%lf%lf",&a[i],&b[i],&p);
    for(int i=1;i<=m;i++)for(int j=1;j<=m;j++)f[i][j]=INF;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++){
            bool flag=1;
            for(int k=1;k<=n;k++){
                double X1=a[k]-x[i],Y1=b[k]-y[i];
                double X2=a[k]-x[j],Y2=b[k]-y[j];
                double tmp=X1*Y2-X2*Y1;
                if(tmp>eps){flag=0;break;}
                if(tmp>-eps && tmp<eps && X1*X2+Y1*Y2>=eps){flag=0;break;}
            }
            if(flag)f[i][j]=1;
        }
    printf("%d\n",floyed());
    return 0;
}
