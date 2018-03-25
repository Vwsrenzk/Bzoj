#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
using namespace std;
int n,a[maxn],pos[maxn],ans[maxn];
struct BIT{
	int s[maxn];
	void add(int pos,int v){
		while(pos<=n){
			s[pos]+=v;
			pos+=pos&(-pos);
		}
	}
	void update(int pos,int v){
		while(pos<=n){
			s[pos]=max(s[pos],v);
			pos+=pos&(-pos);
		}
	}
	int querys(int pos){
		int res=0;
		while(pos){
			res+=s[pos];
			pos-=pos&(-pos);
		}
		return res;
	}
	int query(int pos){
		int res=0;
		while(pos){
			res=max(res,s[pos]);
			pos-=pos&(-pos);
		}
		return res;
	}
}A,B;
int getpos(int x){
	int l=1,r=n,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(A.querys(mid)<x)l=mid+1;
		else r=mid-1,ans=mid;
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&pos[i]);
		pos[i]++;
		A.add(i,1);
	}
	for(int i=n;i;i--){
		int tmp=getpos(pos[i]);
		a[i]=tmp;
		A.add(tmp,-1);
	}
	for(int i=1;i<=n;i++){
		int tmp=B.query(a[i]-1)+1;
		ans[i]=max(ans[i-1],tmp);
		B.update(a[i],tmp);
	}
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}
