/*
	题目大意： 
	有 n 段路，每段路长 si，并有参数 ki, vi，该人在每段路上均匀速骑车.
	若骑车速度为 v，则阻力为 F = ki*(v-vi)^2.
	设初始能量为 E，求到达目的地的最短时间.
	
	题解：
	题目求的是\sum_{i=1}^{n}\frac{si}{vi}的最小值
	限制是\sum_{i=1}^{n}ki*si*(vi-{vi}'^{2})=E
	那么我们想到最小二乘法求多项式函数的最值
	具体求法：
	http://blog.csdn.net/acdreamers/article/details/41413445 
*/ 
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#define maxn 10010
#define INF 1000000009
#define eps 0.000000000001
using namespace std;
int n;
double E,si[maxn],ki[maxn],vi[maxn],v[maxn];
double ans;
double check(double limit){
    double l=0,r=INF,mid,t,sum=0;
    for(int i=1;i<=n;i++){
        l=vi[i],r=INF;
        while(r-l>eps){
            mid=(l+r)/2.0;
            t=2*limit*ki[i]*mid*mid*(mid-vi[i]);
            if(t>1)r=mid;
            else l=mid;
        }
        v[i]=(l+r)/2.0;
    }
    for(int i=1;i<=n;i++)sum+=ki[i]*(v[i]-vi[i])*(v[i]-vi[i])*si[i];
    return sum;
}
int main(){
    double l=0,r=INF,mid;
    scanf("%d%lf",&n,&E);
    for(int i=1;i<=n;i++)scanf("%lf%lf%lf",&si[i],&ki[i],&vi[i]);
    while(r-l>eps){//二分答案 
        mid=(l+r)/2.0;
        if(check(mid)>=E)l=mid;
        else r=mid;
    }
    for(int i=1;i<=n;i++)ans+=si[i]/v[i];
    printf("%.8lf",ans);
    return 0;
}
