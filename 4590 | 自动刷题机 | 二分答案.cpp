#include<iostream>
#include<cstdio>
#define maxn 100010
using namespace std;
int a[maxn],n,k;
int check(long long x){
    int cnt=0;
    long long sum=0;
    for(int i=1;i<=n;i++){
        sum+=a[i];
        if(sum<0)sum=0;
        if(sum>=x){
            cnt++;
            sum=0;
        }
    }
    return cnt;
}
long long mx,ans1,ans2;
int abs(int x){return x>0?x:-x;}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),mx+=abs(a[i]);
    long long l=1,r=mx;
    while(l<=r){
        long long mid=(l+r)>>1;
        if(check(mid)<=k)ans1=mid,r=mid-1;
        else l=mid+1;
    }
    l=1,r=mx;
    while(l<=r){
        long long mid=(l+r)>>1;
        if(check(mid)>=k)ans2=mid,l=mid+1;
        else r=mid-1;
    }
    if(check(ans1)!=k||check(ans2)!=k){
        puts("-1");return 0;
    }
    printf("%lld %lld",ans1,ans2);
    return 0;
