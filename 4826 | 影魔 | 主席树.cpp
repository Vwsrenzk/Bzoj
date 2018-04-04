#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 200010
using namespace std;
int a[maxn],st[maxn][2],top,L[maxn],R[maxn],root[2][maxn];
struct node{int x,y;}A[maxn];
struct Node{int x,yl,yr;}B[maxn<<1];
long long num;
bool cmp1(node p,node q){return p.x<q.x;}
bool cmp2(Node p,Node q){return p.x<q.x;}
int qread(){
	int i=0,j=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
	return i*j;
}
struct TREE{
	int lc[maxn*30],rc[maxn*30],tag[maxn*30],tot;
	long long sum[maxn*30];
	void insert(int pre,int &k,int l,int r,int opl,int opr){
		k=++tot;
		tag[k]=tag[pre];
		sum[k]=sum[pre]+opr-opl+1;
		lc[k]=lc[pre];rc[k]=rc[pre];
		if(l>=opl&&r<=opr){tag[k]++;return;}
		int mid=(l+r)>>1;
		if(opr<=mid) insert(lc[pre],lc[k],l,mid,opl,opr);
		else if(opl>mid) insert(rc[pre],rc[k],mid+1,r,opl,opr);
		else {
			insert(lc[pre],lc[k],l,mid,opl,mid);
			insert(rc[pre],rc[k],mid+1,r,mid+1,opr);
		}
	}
	void query(int x,int pre,int l,int r,int opl,int opr){
		if(l>=opl&&r<=opr){num+=sum[x]-sum[pre];return;}
		int mid=(l+r)>>1;
		if(opr<=mid) {
			num+=(tag[x]-tag[pre])*(opr-opl+1);
			query(lc[x],lc[pre],l,mid,opl,opr);
		}
		else if(opl>mid) {
			num+=(tag[x]-tag[pre])*(opr-opl+1);
			query(rc[x],rc[pre],mid+1,r,opl,opr);
		}
		else {
			num+=(tag[x]-tag[pre])*(mid-opl+1);
			query(lc[x],lc[pre],l,mid,opl,mid);
			num+=(tag[x]-tag[pre])*(opr-mid);
			query(rc[x],rc[pre],mid+1,r,mid+1,opr);
		}
	}
}tr[2];
int main(){
	int n,m,p1,p2;
	n=qread();m=qread();p1=qread();p2=qread();
	for(int i=1;i<=n;i++)a[i]=qread();
	st[top][0]=n+1;st[top][1]=0;
	for(int i=1;i<=n;i++){
		while(top&&a[i]>st[top][0])top--;//维护递减的单调栈 
		L[i]=st[top][1];
		st[++top][0]=a[i];
		st[top][1]=i;
	}
	st[top=0][0]=n+1;
	st[top][1]=n+1;
	for(int i=n;i;i--){
		while(top&&a[i]>st[top][0])top--;
		R[i]=st[top][1];
		st[++top][0]=a[i];
		st[top][1]=i;
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(L[i]&&R[i]<=n){
			A[++cnt].x=L[i];
			A[cnt].y=R[i];
		}
	sort(A+1,A+cnt+1,cmp1);
	int now=1;
	for(int i=1;i<=cnt;i++){
		while(now+1<A[i].x)root[0][now+1]=root[0][now],now++;
		tr[0].insert(root[0][now],root[0][A[i].x],1,n,A[i].y,A[i].y);
		now=A[i].x;
	}
	while(now!=n)root[0][now+1]=root[0][now++];
	cnt=0;
	for(int i=1;i<=n;i++){
		if(R[i]!=i+1 && L[i]){
			B[++cnt].x=L[i];
			B[cnt].yl=i+1;
			B[cnt].yr=R[i]-1;
		}
		if(L[i]!=i-1 && R[i]<=n){
			B[++cnt].x=R[i];
			B[cnt].yl=L[i]+1;
			B[cnt].yr=i-1;
		}
	}
	sort(B+1,B+cnt+1,cmp2);
	now=1;
	for(int i=1;i<=cnt;i++){
		while(now+1<B[i].x)root[1][now+1]=root[1][now],now++;
		tr[1].insert(root[1][now],root[1][B[i].x],1,n,B[i].yl,B[i].yr);
		now=B[i].x;
	}
	while(now!=n)root[1][now+1]=root[1][now++];
	int l,r;
	long long ans;
	while(m--){
		l=qread();r=qread();
		num=0;
		tr[0].query(root[0][r],root[0][l-1],1,n,l,r);
		ans=num*p1;num=0;
		tr[1].query(root[1][r],root[1][l-1],1,n,l,r);
		ans+=num*p2;
		ans+=(r-l)*p1;
		printf("%lld\n",ans);
	}
	return 0;
}
