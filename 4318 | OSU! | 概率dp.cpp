#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
using namespace std;
int n;
double l[maxn],l2[maxn],f[maxn];
int main(){
	scanf("%d",&n);
	double x;
	for(int i=1;i<=n;i++){
		scanf("%lf",&x);
		l[i]=(l[i-1]+1)*x;
		l2[i]=(l2[i-1]+2*l[i-1]+1)*x;
		f[i]=f[i-1]+(3*l2[i-1]+3*l[i-1]+1)*x;
	}
	printf("%.1f",f[n]);
}
