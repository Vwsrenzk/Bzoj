#include<iostream>
#include<cstdio>
#define mod 1000000007
#define maxn 1000010
using namespace std;
int fac[maxn],inv[maxn],f[maxn];
int Pow(int x,int y){
    int res=1;
    while(y){
        if(y&1)res=1LL*res*x%mod;
        x=1LL*x*x%mod;
        y>>=1;
    }
    return res;
}
void prepare(){
    fac[0]=1;
    for(int i=1;i<=1000000;i++)fac[i]=1LL*fac[i-1]*i%mod;
    for(int i=1;i<=1000000;i++)inv[i]=Pow(fac[i],mod-2);
    f[0]=0;f[1]=0;f[2]=1;
    for(int i=3;i<=1000000;i++)f[i]=1LL*(i-1)*(f[i-1]+f[i-2])%mod;
}
int C(int n,int m){
    return 1LL*fac[n]*inv[m]%mod*1LL*inv[n-m]%mod;
}
int main(){
    int T;scanf("%d",&T);
    prepare();
    while(T--){
        int n,m;
        scanf("%d%d",&n,&m);
        if(m==0){
            printf("%d\n",f[n]);
            continue;
        }
        else if(m==n){
            puts("1");
            continue;
        }
        else {
            int ans=1LL*C(n,n-m)*f[n-m]%mod;
            printf("%d\n",ans);
        }
    }
    fclose(stdin);fclose(stdout);
    return 0;
}
