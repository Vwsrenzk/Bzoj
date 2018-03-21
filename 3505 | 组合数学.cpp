#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long ans;
long long C(int x){
	return 1LL*(x-2)*(x-1)*x/6;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	n++;m++;
	ans=C(n*m);
	ans-=C(n)*m;ans-=C(m)*n;
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++){
			int tmp=__gcd(i,j)+1;
			if(tmp>2)ans-=1LL*(tmp-2)*2*(n-i)*(m-j);
		}
	cout<<ans;
	return 0;
}
