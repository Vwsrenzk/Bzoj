#include<iostream>
#include<cstdio>
using namespace std;
int ans,dp[50],a[100010],n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		int tmp=0;
		for(int j=0;j<=30;j++)
			if(a[i]&(1<<j))tmp=max(tmp,dp[j]+1);
		for(int j=0;j<=30;j++)
			if(a[i]&(1<<j))dp[j]=tmp;
		ans=max(ans,tmp);
	}
	printf("%d",ans);
	return 0;
}
