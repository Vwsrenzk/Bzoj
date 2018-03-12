#include<iostream>
#include<cstdio>
#define maxn 500010
using namespace std;
int n,m,p,c,a[maxn],phi[maxn],pn,val[maxn],tms[maxn];
int getphi(int n){
	int res=n;
	for(int i=2;i*i<=n;i++){
		if(n%i!=0)continue;
		res=res/i*(i-1);
		while(n%i==0)n/=i;
	}
	if(n!=1)res=res/n*(n-1);
	return res;
}
int Pow(int x,int y,int p,bool &ok){
	ok=0;
	int res=1;
	while(y){
		if(y&1)ok|=(1LL*res*x>=p),res=1LL*res*x%p;
		ok|=(1LL*x*x>=p&&y!=1);
		x=1LL*x*x%p;
		y>>=1;
	}
	return res;
}
int calc(int x,int p){
	int res=x;bool ok;
	if(res>=phi[p])res=res%phi[p]+phi[p];
	while(p--){
		x=res;
		res=Pow(c,x,phi[p],ok);
		if(ok)res+=phi[p];
	}
	return res%phi[0];
}
//-------------------------------------------------
void build(int k,int l,int r){
	if(l==r){
		val[k]=a[l]%phi[0];
		tms[k]=0;
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);build(k<<1|1,mid+1,r);
	val[k]=(val[k<<1]+val[k<<1|1])%phi[0];
	tms[k]=min(tms[k<<1],tms[k<<1|1]);
}
void modify(int k,int l,int r,int opl,int opr){
	if(tms[k]>=pn)return;
	if(l==r){
		tms[k]++;
		val[k]=calc(a[l],tms[k]);
		return;
	}
	int mid=(l+r)>>1;
	if(opl<=mid)modify(k<<1,l,mid,opl,opr);
	if(opr>mid)modify(k<<1|1,mid+1,r,opl,opr);
	val[k]=(val[k<<1]+val[k<<1|1])%phi[0];
	tms[k]=min(tms[k<<1],tms[k<<1|1]);
}
int query(int k,int l,int r,int opl,int opr){
	if(l>=opl&&r<=opr)return val[k];
	int mid=(l+r)>>1,res=0;
	if(opl<=mid)res+=query(k<<1,l,mid,opl,opr);
	if(opr>mid)res+=query(k<<1|1,mid+1,r,opl,opr);
	return res%phi[0];
}
//-------------------------------------------------
int main(){
	scanf("%d%d%d%d",&n,&m,&p,&c);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	phi[0]=p;
	while(p!=1){
		int t=getphi(p);
		phi[++pn]=t;
		p=t;
	}
	phi[++pn]=1;
	build(1,1,n);
	int op,l,r;
	while(m--){
		scanf("%d%d%d",&op,&l,&r);
		if(op==0)modify(1,1,n,l,r);
		else printf("%d\n",query(1,1,n,l,r));
	}
	return 0;
}
