#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mod 2147483648LL
#define maxn 200010
using namespace std;
int n,m,cnt,w,k,h[maxn],l[maxn],hash[maxn],now[maxn];
long long c[maxn][11],tr[maxn],ans;
struct node{
	int x,y;
	bool operator < (const node &b)const{
		if(y!=b.y)return y<b.y;
		return x<b.x;
	}
}a[maxn];
void prepare(){
	c[0][0]=1;
	for(int i=1;i<=w;i++){
		c[i][0]=1;
		for(int j=1;j<=min(i,k);j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	}
}
int find(int x){
	int res=lower_bound(hash+1,hash+cnt+1,x)-hash;
	return res;
}
long long query(int pos){
	long long res=0;
	while(pos){
		res+=tr[pos];
		res%=mod;
		pos-=pos&(-pos);
	}
	return res;
}
void update(int pos,long long change){
	while(pos<=cnt){
		tr[pos]+=change;
		tr[pos]%=mod;
		pos+=pos&(-pos);
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&w);
	for(int i=1;i<=w;i++){
		scanf("%d%d",&a[i].x,&a[i].y);
		hash[++cnt]=a[i].x;
		hash[++cnt]=a[i].y;
	}
	scanf("%d",&k);
	prepare();
	sort(hash+1,hash+cnt+1);
	sort(a+1,a+w+1);
	for(int i=1;i<=w;i++){
		h[find(a[i].y)]++;
		l[find(a[i].x)]++;
	}
	int lf=0;
	for(int i=1;i<=w;i++){
		if(i>1&&a[i].y==a[i-1].y){
			lf++;
			long long t1=query(find(a[i].x)-1)-query(find(a[i-1].x));
			long long t2=c[lf][k]*c[h[find(a[i].y)]-lf][k]%mod;
			ans+=t1*t2%mod;
			ans%=mod;
		}
		else lf=0;
		int d=find(a[i].x);now[d]++;
		long long change=(c[now[d]][k]*c[l[d]-now[d]][k]-c[now[d]-1][k]*c[l[d]-now[d]+1][k])%mod;
		update(d,change);
	}
	if(ans<0)ans+=mod;
	cout<<ans;
	return 0;
}
