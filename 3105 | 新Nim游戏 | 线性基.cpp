#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 110
using namespace std;
int a[maxn],w[maxn],ins[30],sav[maxn],top,n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	long long tot=0;
	for(int i=1;i<=n;i++)tot+=a[i],w[i]=a[i];
	long long ans=0;
	for(int i=n;i>=1;i--){
		for(int j=29;j>=0;j--){
			if((a[i]>>j)&1){
				if(!ins[j]){
					ins[j]=i;
					for(int k=1;k<=top;k++)
						if((a[sav[k]]>>j)&1)a[sav[k]]^=a[i];
					sav[++top]=i;
					break;
				}
				else a[i]^=a[ins[j]];
			}
		}
		if(a[i])ans+=w[i];
	}
	if(ans!=0)printf("%lld",tot-ans);
	else puts("-1");
	return 0;
}
