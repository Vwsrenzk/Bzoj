#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 50010
using namespace std;
int n,cnt;
struct node{
	int x,id;
	bool operator == (const node b)const{
		return x==b.x;
	}
}a[maxn];
bool cmp1(node u,node v){
	if(u.x!=v.x)return u.x<v.x;
	else return u.id<v.id;
}
bool cmp2(node u,node v){return u.id<v.id;}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&a[i].x),a[i].id=i;
		sort(a+1,a+n+1,cmp1);
		cnt=unique(a+1,a+n+1)-(a+1);
		sort(a+1,a+cnt+1,cmp2);
		for(int i=1;i<=cnt;i++)printf("%d ",a[i].x);
		puts("");
	}
	return 0;
}
