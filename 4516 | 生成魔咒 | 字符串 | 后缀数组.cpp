#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 200010
using namespace std;
int n,bin[25],lg2[maxn],f[17][maxn],num[maxn];
int sa[maxn],rnk[maxn],q[maxn],hgt[maxn],sum[maxn],c[2][maxn];
struct node{int x,id;}a[maxn];
bool cmp(node u,node v){return u.x<v.x;}
void solve_sa(){
	sort(a+1,a+n+1,cmp);
	int cnt=0;
	for(int i=1;i<=n;i++){//离散化 
		if(i==1||a[i].x!=a[i-1].x)cnt++;
		rnk[a[i].id]=num[a[i].id]=cnt;
	}
	for(int i=1;i<=n;i++)sum[rnk[i]]++;
	for(int i=2;i<=cnt;i++)sum[i]+=sum[i-1];
	for(int i=n;i;i--)sa[sum[rnk[i]]--]=i;
	for(int k=1;cnt<n;k<<=1){
		for(int i=1;i<=k;i++)q[i]=n-k+i;
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=n-k;i++)sum[rnk[i+k]]++;
		sum[0]=k;
		for(int i=1;i<=cnt;i++)sum[i]+=sum[i-1];
		for(int i=n-k;i;i--)q[sum[rnk[i+k]]--]=i;
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=n;i++)sum[rnk[i]]++;
		for(int i=2;i<=cnt;i++)sum[i]+=sum[i-1];
		for(int i=n;i;i--)sa[sum[rnk[q[i]]]--]=q[i];
		cnt=0;memcpy(q,rnk,sizeof(rnk[0])*(n+1));
		for(int i=1;i<=n;i++){
			if(i==1||q[sa[i]]!=q[sa[i-1]]||q[sa[i]+k]!=q[sa[i-1]+k])cnt++;
			rnk[sa[i]]=cnt;
		}
	}
}
void solve_hgt(){
	int i,j,k=0;
	for(i=1;i<=n;i++){
		if(k)k--;
		j=sa[rnk[i]-1];
		while(num[j+k]==num[i+k])k++;
		hgt[rnk[i]]=k;
	}
}
int lcp(int x,int y){
	if(!x||x>n)return 0;
	if(x>y)swap(x,y);
	x++;
	int k=lg2[y-x+1];
	return min(f[k][x],f[k][y-bin[k]+1]);
}
void ins(int k,int x){
	int i=x;
	while(i<=n){
		c[k][i]=max(c[k][i],x);
		i+=i&-i;
	}
}
int find(int k,int x){
	int t=0;
	while(x){
		t=max(t,c[k][x]);
		x-=x&-x;
	}
	return t;
}
int main(){
	scanf("%d",&n);
	for(int i=n;i;i--){scanf("%d",&a[i].x);a[i].id=i;}
	solve_sa();solve_hgt();
	memcpy(f[0],hgt,sizeof(hgt));
	lg2[1]=0;bin[0]=1;bin[1]=2;
	for(int i=1;i<=16;i++){//rmq维护区间最小值 
		bin[i+1]=bin[i]<<1;
		for(int j=bin[i];j<bin[i+1];j++)lg2[j]=i;
		for(int j=1;j<=n;j++){
			f[i][j]=f[i-1][j];
			if(j+bin[i-1]<=n)
			f[i][j]=min(f[i][j],f[i-1][j+bin[i-1]]);
		}
	}
	int t1,t2;long long ans=0;
	for(int i=n;i;i--){
		ans+=n-i+1;
		t1=find(0,rnk[i]-1);
		t2=n-find(1,n-rnk[i])+1;
		ans-=max(lcp(t1,rnk[i]),lcp(t2,rnk[i]));
		printf("%lld\n",ans);
		ins(0,rnk[i]);
		ins(1,n-rnk[i]+1);
	}
	return 0;
}
