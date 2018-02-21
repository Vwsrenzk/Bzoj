#include<iostream>
#include<cstdio>
#define maxn 10000010
using namespace std;
int T;
int p[664580],cnt,mu[maxn],sum[maxn];
bool vis[maxn];
void prepare(){
    mu[1]=1;
    for(int i=2;i<=9999991;i++){
        if(!vis[i]){p[++cnt]=i;mu[i]=-1;}
        for(int j=1;j<=cnt&&i*p[j]<=9999991;j++){
            vis[i*p[j]]=1;
            if(i%p[j]==0){mu[i*p[j]]=0;break;}
            else mu[i*p[j]]=-mu[i];
        }
    }
    for(int i=1;i<=10000000;i++)sum[i]=sum[i-1]+mu[i];
}
long long work(int n,int m){
    if(n>m)swap(n,m);
    long long res=0;
    for(int i=1,j;i<=n;i=j+1){
        j=min(n/(n/i),m/(m/i));
        res+=1LL*(sum[j]-sum[i-1])*(n/i)*(m/i);
    }
    return res;
}
int main(){
    prepare();
    int n,m;
    scanf("%d",&n);m=n;
    long long ans=0;
    for(int i=1;i<=cnt;i++){
        if(p[i]>n)break;
        ans+=work(n/p[i],m/p[i]);
    }
    printf("%lld\n",ans);
}
