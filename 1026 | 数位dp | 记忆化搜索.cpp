#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int A,B,bin[20],dp[20][20],len;
int abs(int x){return x>0?x:-x;}
int dfs(int pos,int pre,bool lead,bool limit){
	if(pos==0)return 1;
	if(!lead&&!limit&&dp[pos][pre]>=0)return dp[pos][pre];
	int end=limit?bin[pos]:9,res=0;
	for(int i=0;i<=end;i++){
		if(!lead&&abs(i-pre)<2&&pos!=len)continue;
		res+=dfs(pos-1,i,lead&&i==0,limit&&i==end);
	}
	if(!lead&&!limit)dp[pos][pre]=res;
	return res;
}
int solve(int x){
	len=0;
	while(x){
		bin[++len]=x%10;
		x/=10;
	}
	return dfs(len,0,1,1);
}
int main(){
	memset(dp,-1,sizeof(dp));
	scanf("%d%d",&A,&B);
	printf("%d",solve(B)-solve(A-1));
	return 0;
}
