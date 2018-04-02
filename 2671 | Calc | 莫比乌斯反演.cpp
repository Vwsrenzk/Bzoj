#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 50010
using namespace std;
long long n,st[maxn],top;
int mu[maxn],p[maxn],cnt;
bool vis[maxn];
void prepare(){
	mu[1]=1;
	for(int i=2;i<=50000;i++){
		if(!vis[i]){mu[i]=-1;p[++cnt]=i;}
		for(int j=1;j<=cnt&&p[j]*i<=50000;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0){
				mu[i*p[j]]=0;
				break;
			}
			mu[p[j]*i]=-mu[i];
		}
	}
}
void get(long long n){
	long long i;top=0;
	for(i=1;i*i<n;i++)
		if(n%i==0)
		st[++top]=i,st[++top]=n/i;
	if(i*i==n)
		st[++top]=i;
	sort(st+1,st+top+1);
}
long long solve(){
	long long a,b,k,last,re=0;
	for(b=1;b*(b+1)<=n;b++){
		get(b);
		for(a=1;a<b&&b*(a+b)<=n;a=last+1){
			last=min(n/(n/b/(a+b))/b-b,b-1);
			long long cnt=0;
			for(k=1;st[k]<=last;k++)
				cnt+=mu[st[k]]*(last/st[k]-(a-1)/st[k]);
			re+=n/b/(a+b)*cnt;
		}
	}
	return re;
}
int main(){
	scanf("%d",&n);
	prepare();
	cout<<solve();
	return 0;
}
