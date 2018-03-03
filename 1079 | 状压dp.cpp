#include<iostream>
#include<cstdio>
#define mod 1000000007
#define lon long long
using namespace std;
int s[6],dp[16][16][16][16][16][16],k;
int dfs(int a1,int a2,int a3,int a4,int a5,int last){
    if(dp[a1][a2][a3][a4][a5][last]) return dp[a1][a2][a3][a4][a5][last];
    if(a1+a2+a3+a4+a5==0) return dp[a1][a2][a3][a4][a5][last]=1;
    lon tot=0;
    if(a1) tot+=1LL*(a1-(last==2))*dfs(a1-1,a2,a3,a4,a5,1),tot%=mod;
    if(a2) tot+=1LL*(a2-(last==3))*dfs(a1+1,a2-1,a3,a4,a5,2),tot%=mod;
    if(a3) tot+=1LL*(a3-(last==4))*dfs(a1,a2+1,a3-1,a4,a5,3),tot%=mod;
    if(a4) tot+=1LL*(a4-(last==5))*dfs(a1,a2,a3+1,a4-1,a5,4),tot%=mod;
    if(a5) tot+=1LL*a5*dfs(a1,a2,a3,a4+1,a5-1,5),tot%=mod;
    return dp[a1][a2][a3][a4][a5][last]=tot;
}
int main(){
    scanf("%d",&k);
    for(int i=1;i<=k;i++){
        int x;scanf("%d",&x);
        s[x]++;
    }
    printf("%d",dfs(s[1],s[2],s[3],s[4],s[5],0));
    return 0;
}
