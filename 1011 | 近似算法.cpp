#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define maxn 100005
using namespace std;
double a,m[maxn],sum[maxn],f[maxn];
int n;
int main(){
    scanf("%d%lf",&n,&a);
    for(int i=1;i<=n;i++){
        scanf("%lf",&m[i]);
        sum[i]=sum[i-1]+m[i];
    }
    for(int i=1;i<=n;i++){
        double s=a*i,mid;
        int lim=floor(s);
        if(lim<=100){
            for(int j=1;j<=lim;j++)
            f[i]+=m[i]*m[j]/(i-j);
        }
        else{
            int l2=lim/100;
            for(int j=l2;j<=l2*100;j+=l2){
                mid=(i-j+i-j+l2-1)*0.5;
                f[i]+=(sum[j]-sum[j-l2])*m[i]/mid;
            }
            for(int j=l2*100+1;j<=lim;j++)
                f[i]+=m[i]*m[j]/(i-j);
        }
    }
    for(int i=1;i<=n;i++)printf("%.6lf\n",f[i]);
}
