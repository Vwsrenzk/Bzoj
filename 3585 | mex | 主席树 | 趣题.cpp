/*
3585: mex

Time Limit: 20 Sec  Memory Limit: 128 MB
Submit: 1412  Solved: 712
[Submit][Status][Discuss]
Description

　　有一个长度为n的数组{a1,a2,...,an}。m次询问，每次询问一个区间内最小没有出现过的自然数。

Input

　　第一行n,m。
　　第二行为n个数。
　　从第三行开始，每行一个询问l,r。

Output

　　一行一个数，表示每个询问的答案。

Sample Input

5 5

2 1 0 2 1

3 3

2 3

2 4

1 2

3 5

Sample Output

1

2

3

0

3

HINT

数据规模和约定

　　对于100%的数据：

　　1<=n,m<=200000

　　0<=ai<=109

　　1<=l<=r<=n


　　对于30%的数据：


　　1<=n,m<=1000
  
  以权值为下标，
  minn[i]=j，表示i所代表的权值为[l,r]的区间，最早出现的位置为j
  例：0 2 1 0 1 3 2
  对于root[7]来说，
  [0,3]=1, 0最早出现在第1个位置
  [1,3]=2, 2最早出现在第2个位置
  查询[l,r]时，在root[r]里查询
  如果左子区间的minn>=l，说明权值小的左边一半都最早出现在l以后，就往右孩子找
  否则，说明权值小的左边一半有没有出现在l之后的，就往左孩子找
  因为是在root[r]里，所以保证不超过右边界
  对于10^9的权值，离散化？
  不。
  如果权值>n，直接让它=n
  因为此时<n中一定有没有出现的数
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 200010
using namespace std;
int root[maxn*20],lc[maxn*20],rc[maxn*20],mn[maxn*20];
int n,m,x,sz;
void build(int &now,int pre,int l,int r,int pos,int val){
	now=++sz;
	if(l==r){
		mn[now]=val;
		return;
	}
	int mid=(l+r)>>1;
	lc[now]=lc[pre];rc[now]=rc[pre];
	if(pos<=mid) build(lc[now],lc[pre],l,mid,pos,val);
	else build(rc[now],rc[pre],mid+1,r,pos,val);
	mn[now]=min(mn[lc[now]],mn[rc[now]]);
}
int query(int now,int l,int r,int pos){
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(mn[lc[now]]>=pos) return query(rc[now],mid+1,r,pos);
	else return query(lc[now],l,mid,pos);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(x>n)x=n;
		build(root[i],root[i-1],0,n,x,i);
	}
	int l,r;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&l,&r);
		printf("%d\n",query(root[r],0,n,l));
	}
}
