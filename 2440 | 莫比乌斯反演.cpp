#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
int T,mul[50010],p[50010],cnt;
long long n;
bool vis[50010];

long long check(long long mid){
	int range=sqrt(mid);
	long long res=0;
	for(int i=1;i<=range;i++){
		res+=mid/(i*i)*mul[i];
	}
	return res;
}
long long find(int k){
	long long l=k,r=1644934081,ans=0;
	while(l<=r){
		long long mid=(l+r)>>1;
		long long now=check(mid);
		if(now>=k)r=mid-1,ans=mid;
		else l=mid+1;
	}
	return ans;
}
void prepare(){
	mul[1]=1;
	for(int i=2;i<=50000;i++){
		if(!vis[i]){p[++cnt]=i;mul[i]=-1;}
		for(int j=1;j<=cnt&&i*p[j]<=50000;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0){mul[i*p[j]]=0;break;}
			else mul[i*p[j]]=-mul[i];
		}
	}
}
int main(){
	prepare();
	scanf("%d",&T);
	while(T--){
		cin>>n; 
		cout<<find(n)<<endl;
	}
}
