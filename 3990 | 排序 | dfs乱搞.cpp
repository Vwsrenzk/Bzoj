#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int bin[20],fac[20],a[5010],n;
long long ans;
bool check(int x,int k){
	for(int i=1;i<bin[k];i++)if(a[x+i]!=a[x+i-1]+1)return 0;
	return 1;
}
void Rev(int x,int y,int k){
	for(int i=0;i<bin[k];i++)swap(a[x+i],a[y+i]);
}
void dfs(int k,int now){
	if(k==n+1){ans+=fac[now];return;}
	int t1=0,t2=0;
	for(int i=1;i<=bin[n];i+=bin[k])/*不是连续递增的段*/
		if(!check(i,k)){
			if(!t1)t1=i;
			else if(!t2)t2=i;
			else return;
		}
	if(!t1&&!t2)dfs(k+1,now);
	else if(t1&&!t2){
		Rev(t1,t1+bin[k-1],k-1);
		dfs(k+1,now+1);
		Rev(t1,t1+bin[k-1],k-1);
	}
	else {
		for(int x=0;x<=1;x++)
			for(int y=0;y<=1;y++){
				Rev(t1+x*bin[k-1],t2+y*bin[k-1],k-1);
				if(check(t1,k)&&check(t2,k)){
					dfs(k+1,now+1);
					Rev(t1+x*bin[k-1],t2+y*bin[k-1],k-1);
					break;
				}
				Rev(t1+x*bin[k-1],t2+y*bin[k-1],k-1);
			}
	}
}
int main(){
	bin[0]=fac[0]=1;
	for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
	for(int i=1;i<=12;i++)fac[i]=fac[i-1]*i;
	scanf("%d",&n);
	for(int i=1;i<=bin[n];i++)scanf("%d",&a[i]);
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}
