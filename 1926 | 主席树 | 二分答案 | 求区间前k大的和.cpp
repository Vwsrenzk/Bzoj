#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 500010
#define INF 1000
using namespace std;
int R,C,n,sz,m;
int lc[maxn*20],rc[maxn*20],root[maxn],sum[maxn*20],w[maxn*20],val[maxn];
void build(int l,int r,int x,int &y,int v){
	y=++sz;
	if(l==r){
		sum[y]=sum[x]+v;
		w[y]=w[x]+1;
		return;
	}
	int mid=(l+r)>>1;
	lc[y]=lc[x];rc[y]=rc[x];
	if(v<=mid)build(l,mid,lc[x],lc[y],v);
	else build(mid+1,r,rc[x],rc[y],v);
	sum[y]=sum[lc[y]]+sum[rc[y]];
	w[y]=w[lc[y]]+w[rc[y]];
}
int query(int l,int r,int x,int y,int k){
	if(l==r) return (sum[y]-sum[x])/(w[y]-w[x])*k;
	int mid=l+r>>1,tmp=w[lc[y]]-w[lc[x]];
	if(k<=tmp) return query(l,mid,lc[x],lc[y],k);
	return sum[lc[y]]-sum[lc[x]]+query(mid+1,r,rc[x],rc[y],k-tmp);
}
void work1(){
	for(int i=1;i<=n;i++){
		scanf("%d",&val[i]);
		build(1,INF,root[i-1],root[i],val[i]);
	}
	int xx,x,y,h;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d%d",&xx,&x,&xx,&y,&h);
		int len=y-x+1,ans;
		int l=1,r=len;
		int sum=query(1,INF,root[x-1],root[y],len);
		if(sum<h){puts("Poor QLW");continue;}
		while(l<=r){
			int mid=(l+r)>>1;
			int nowsum=sum;
			if(mid==len){
				ans=len;break;
			}
			int kk=query(1,INF,root[x-1],root[y],len-mid);
			nowsum-=kk;
			if(nowsum>=h)ans=mid,r=mid-1;
			else l=mid+1;
		}
		printf("%d\n",ans);
	}
}

int a[210][210][1010],b[210][210][1010];
void work2(){
	int x;
	for(int i=1;i<=R;i++)
		for(int j=1;j<=C;j++){
			scanf("%d",&x);
			for(int k=1;k<=1000;k++){
				a[i][j][k]=a[i-1][j][k]+a[i][j-1][k]-a[i-1][j-1][k];
				b[i][j][k]=b[i-1][j][k]+b[i][j-1][k]-b[i-1][j-1][k];
				if(x>=k)a[i][j][k]++,b[i][j][k]+=x;
			}
		}
	int x1,y1,x2,y2,h;
    while(m--){
        scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&h);
        int l=1,r=1000,ans=1001;
        while(l<=r){
            int mid=l+r>>1;
            if(b[x2][y2][mid]-b[x1-1][y2][mid]-b[x2][y1-1][mid]+b[x1-1][y1-1][mid]>=h)
                l=mid+1,ans=mid;
            else r=mid-1;
        }
        if(ans==1001) printf("Poor QLW\n");
        else {
            int sum1=b[x1-1][y1-1][ans]+b[x2][y2][ans]-b[x2][y1-1][ans]-b[x1-1][y2][ans]-h;
            int sum2=a[x1-1][y1-1][ans]+a[x2][y2][ans]-a[x2][y1-1][ans]-a[x1-1][y2][ans];
            printf("%d\n",sum2-sum1/ans);
        }
    }
}

int main(){
	scanf("%d%d%d",&R,&C,&m);n=C;
	if(R==1)work1();
	else work2();
	return 0;
}
