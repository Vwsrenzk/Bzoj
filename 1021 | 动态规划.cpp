#include<iostream>
#include<cstdio>
#include<cstring>
#define INF 1000000000
#define maxn 1010
using namespace std;
int val[7]={0,100,50,20,10,5,1};
int cnt[maxn][maxn],d[maxn],e[maxn],sum,a,b,c,dp[3][maxn][maxn];
int abs(int x){return x>0?x:-x;}
int main(){
	scanf("%d%d%d",&a,&b,&c);
	for(int i=1;i<=3;i++)
		for(int j=1;j<=6;j++){
			scanf("%d",&cnt[i][j]);
			sum+=cnt[i][j]*val[j];
			d[i]+=cnt[i][j]*val[j];
			e[j]+=cnt[i][j];
		}
	int ta=d[1]-a+c,tb=d[2]-b+a;
	if(ta<0||tb<0||sum-ta-tb<0){puts("impossible");return 0;}
	memset(dp[0],0x3f,sizeof(dp[0]));
	int pre=0,now=0;dp[0][d[1]][d[2]]=0;
	for(int i=1;i<=6;i++){
		pre=now;now^=1;
		memset(dp[now],0x3f,sizeof(dp[now]));
		for(int j=0;j<=sum;j++)
			for(int k=0;j+k<=sum;k++){
				if(dp[pre][j][k]>INF)continue;
				dp[now][j][k]=min(dp[now][j][k],dp[pre][j][k]);
				for(int l=0;l<=e[i];l++)
					for(int m=0;m+l<=e[i];m++){
						int deltaa=l-cnt[1][i],deltab=m-cnt[2][i];
						int cost1=j+deltaa*val[i],cost2=k+deltab*val[i];
                        if(cost1<0||cost2<0||sum-cost1-cost2<0)continue;
                        dp[now][cost1][cost2]=min(dp[now][cost1][cost2],dp[pre][j][k]+(abs(deltaa)+abs(deltab)+abs(deltaa+deltab))/2);
					}
			}
	}
	if(dp[now][ta][tb]>INF)puts("impossible");
	else printf("%d",dp[now][ta][tb]);
	return 0;
}
