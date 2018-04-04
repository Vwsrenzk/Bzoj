#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 20
using namespace std;
int n,k,S[maxn];
double dp[110][40010],P[maxn],p;
int main(){
	scanf("%d%d",&k,&n);
	int xx=0;
	for(int i=1;i<=n;i++){
		scanf("%lf",&P[i]);
		while(1){
			scanf("%d",&xx);
			if(xx==0)break;
			S[i]|=1<<(xx-1);
		}
	}
	p=1.0/(double)n;
	for(int i=k;i;i--){
		for(int s=0;s<(1<<n);s++){
			for(int j=1;j<=n;j++){
				double x=dp[i+1][s];
				if((s&S[j])==S[j]){
					x=max(x,dp[i+1][s|(1<<(j-1))]+P[j]);
				}
				dp[i][s]+=x*p;
			}
		}
	}
	printf("%.6lf",dp[1][0]);
	return 0;
}
