#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
using namespace std;
long long A,B,C,t[maxn],b[maxn];
int n,m;
long long qread(){
    long long i=0,j=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
    while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
    return i*j;
}
long long Judge(long long x){
    long long cost=0;
    if(A<B){
        long long rest=0,need=0;
        for(int i=1;i<=m;i++)if(b[i]<x)rest+=x-b[i];
        for(int i=1;i<=m;i++)if(b[i]>x)need+=b[i]-x;
        if(rest>=need)cost+=need*A;
        else cost+=rest*A+(need-rest)*B;
    }
    else
    for(int i=1;i<=m;i++)
        if(b[i]>x)cost+=(b[i]-x)*B;
    for(int i=1;i<=n;i++)
        if(t[i]<x)cost+=(x-t[i])*C;
    return cost;
}
int main(){
    A=qread();B=qread();C=qread();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)t[i]=qread();
    for(int i=1;i<=m;i++)b[i]=qread();
    if(C==1e16){
        long long mn=1e18;
        for(int i=1;i<=n;i++)mn=min(mn,t[i]);
        printf("%lld",Judge(mn));
        return 0;
    }
    int l=1,r=1e5;
    while(l+2<r){
        int mid1=(2*l+r)/3,mid2=(2*r+l)/3;
        long long val1=Judge(mid1);
        long long val2=Judge(mid2);
        if(val1==val2)l=mid1,r=mid2;
        else if(val1<val2)r=mid2;
        else l=mid1;
    }
    long long val1=Judge(l),val2=Judge(r);
    long long val3=Judge((2*l+r)/3);
    long long val4=Judge((2*r+l)/3);
    long long ans=min(min(val1,val2),min(val3,val4));
    printf("%lld",ans);
}
