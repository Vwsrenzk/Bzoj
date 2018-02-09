/*
	题目大意：
		监狱有连续编号为1...N的N个房间，每个房间关押一个犯人，有M种宗教，每个犯人可能信仰其中一种。如果相邻房间的犯人的宗教相同，就可能发生越狱，求有多少种状态可能发生越狱
	题解：
		所有的情况-不合法的情况
		所有情况显然是m^n
		不合法的情况就是所有相邻的都不相同。第一个有m种选法，第二个有m-1种，第三个有m-1种……总共m*(m-1)^(n-1)种 
*/
#include<iostream>
#include<cstdio>
#define mod 100003
using namespace std;
long long n,m;
int Pow(long long x,long long y){
	int res=1;
	while(y){
		if(y&1)res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}
int main(){
	cin>>m>>n;
	int ans=(Pow(m,n)-1LL*m*Pow(m-1,n-1)%mod+mod)%mod;
	printf("%d",ans);
	return 0;
}
