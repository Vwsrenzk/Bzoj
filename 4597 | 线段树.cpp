#include<iostream>
#include<cstdio>
#include<cstdlib>
#define mod 1000000007
#define maxn 100010
using namespace std;
struct Segment_tree{
	int l,r;
	long long sum,tag;
}tr[maxn*4];
long long a[maxn],inv[maxn],sum[maxn];
int n,m,T;
long long qread(){
	long long i=0,j=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
	return i*j;
}
int Pow(int x,int y){
	int res=1;
	while(y){
		if(y&1)res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}
void build(int k,int l,int r){
	tr[k].l=l;tr[k].r=r;tr[k].tag=1;
	if(l==r){
		if(l!=n)tr[k].sum=(2LL*Pow(3,n-l-1)%mod)*sum[l]%mod;
		else tr[k].sum=sum[n];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	tr[k].sum=(tr[k<<1].sum+tr[k<<1|1].sum)%mod;
}
void add(int k,long long x){
	tr[k].tag=tr[k].tag*x%mod;
	tr[k].sum=tr[k].sum*x%mod;
}
void pushdown(int k){
	if(tr[k].l==tr[k].r||!tr[k].tag)return;
	add(k<<1,tr[k].tag);
	add(k<<1|1,tr[k].tag);
	tr[k].tag=1;
}
void modify(int k,int l,int r,int opl,int opr,long long x){
	if(l>=opl&&r<=opr){
		add(k,x);
		return;
	}
	pushdown(k);
	int mid=(l+r)>>1;
	if(opl<=mid)modify(k<<1,l,mid,opl,opr,x);
	if(opr>mid)modify(k<<1|1,mid+1,r,opl,opr,x);
	tr[k].sum=(tr[k<<1].sum+tr[k<<1|1].sum)%mod;
}
int main(){
	for(int i=1;i<=10000;i++)inv[i]=Pow(i,mod-2);
	scanf("%d%d",&n,&T);
	for(int i=1;i<=n;i++)a[i]=qread();
	sum[0]=1;
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]*a[i]%mod;
	build(1,1,n);
	while(T--){
		int pos;
		long long x;
		scanf("%d",&pos);x=qread();
		modify(1,1,n,pos,n,inv[a[pos]]*x%mod);
		a[pos]=x;
//		cout<<tr[1].sum<<endl;
		printf("%lld\n",tr[1].sum);
	}
	return 0;
}
