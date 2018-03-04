#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
double dfs(double x,double y,double n){
	if(n==1){
		if(x<y)swap(x,y);
		return x/y;
	}
	double ans=1000000007.0,ans1,ans2;
	double mx=x/n,my=y/n;
	for(double i=1;i<=n/2;i+=1.0){
		ans1=max(dfs(x-mx*i,y,n-i),dfs(mx*i,y,i));
		ans2=max(dfs(x,y-my*i,n-i),dfs(x,my*i,i));
		ans=min(ans,min(ans1,ans2));
	}
	return ans;
}
int main(){
	double x,y,n;
	scanf("%lf%lf%lf",&x,&y,&n);
	printf("%.6lf",dfs(x,y,n));
	return 0;
}
