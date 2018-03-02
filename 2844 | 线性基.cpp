#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
#define mod 10086
using namespace std;
int n,a[maxn],b[40],c[40],cnt,rnk,q;
int Pow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
} 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=31;j>=0;j--)
			if((a[i]>>j)&1){
				if(b[j])a[i]^=b[j];
				else{
					b[j]=a[i];
					for(int k=j-1;k>=0;k--)
						if(((b[j]>>k)&1)&&b[k])b[j]^=b[k];
					for(int k=j+1;k<=31;k++)
						if((b[k]>>j)&1)b[k]^=b[j];
					break;
				}
			}
	scanf("%d",&q);
	for(int i=0;i<=31;i++)if(b[i])c[++cnt]=i;
	for(int i=1;i<=cnt;i++)if((q>>c[i])&1)rnk+=1<<(i-1);
	int ans=rnk%mod*Pow(2,n-cnt)%mod;
	ans=(ans+1)%mod;
	printf("%d",ans);
	return 0;
}
