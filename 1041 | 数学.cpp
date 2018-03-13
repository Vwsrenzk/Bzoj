#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
long long R,ans=0;
long long gcd(long long x,long long y){
	if(y==0)return x;
	return gcd(y,x%y);
}
bool check(long long y,double x){
	if(x==floor(x)){
		long long xx=(long long)floor(x);
		if(gcd(xx*xx,y*y)==1 && xx*xx!=y*y)return 1;
	}
	return 0;
}
int main(){
	cin>>R;
	for(long long d=1;d<=sqrt(R*2);d++){
		if(R*2%d)continue;
		for(long long a=1;a<=sqrt(R*2/(2*d));a++){
			double b=sqrt((2*R)/d-a*a);
			if(check(a,b))ans++;
		}
		if(d!=(2*R)/d){
			for(long long a=1;a<=sqrt(d/2);a++){
				double b=sqrt(d-a*a);
				if(check(a,b))ans++;
			}
		}
	}
	cout<<ans*4+4;
	return 0;
}
