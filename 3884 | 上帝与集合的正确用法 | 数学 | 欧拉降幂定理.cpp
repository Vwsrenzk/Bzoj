#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int getphi(int x){
	int res=x;
	for(int i=2;i*i<=x;i++)
		if(x%i==0){
			res/=i;res*=i-1;
			while(x%i==0)x/=i;
		}
	if(x!=1)res/=x,res*=x-1;
	return res;
}
int Pow(int x,int y,int p){
	int res=1;
	while(y){
		if(y&1)res=1LL*res*x%p;
		x=1LL*x*x%p;
		y>>=1;
	}
	return res;
}
int solve(int p){
	if(p==1)return 0;
	int tmp=0;
	while(!(p&1)){p>>=1;tmp++;}
	int phi=getphi(p);
	int res=solve(phi);
	res=(res+(phi-tmp%phi))%phi;
	res=Pow(2,res,p)%p;
	return res<<tmp;
}
int main(){
	int T,p;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&p);
		printf("%d\n",solve(p));
	}
	return 0;
}
