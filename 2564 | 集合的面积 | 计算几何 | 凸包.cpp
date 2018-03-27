/*
Description

　　对于一个平面上点的集合P={(xi,yi )}，定义集合P的面积F(P)为点集P的凸包的面积。
　　对于两个点集A和B，定义集合的和为：
　　A+B={(xiA+xjB,yiA+yjB ):(xiA,yiA )∈A,(xjB,yjB )∈B}
　　现在给定一个N个点的集合A和一个M个点的集合B，求2F(A+B)。
　
Input

　第一行包含用空格隔开的两个整数，分别为N和M；
　　第二行包含N个不同的数对，表示A集合中的N个点的坐标；
　　第三行包含M个不同的数对，表示B集合中的M个点的坐标。

　
Output

　一共输出一行一个整数，2F(A+B)。

Sample Input

4 5

0 0 2 1 0 1 2 0

0 0 1 0 0 2 1 2 0 1

Sample Output

18

数据规模和约定

　　对于30%的数据满足N ≤ 200，M ≤ 200；

　　对于100%的数据满足N ≤ 10^5，M ≤ 10^5，|xi|, |yi| ≤ 10^8。
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 100010
using namespace std;
int top;
struct node{
	long long x,y;
	node operator - (const node &b)const{
		node res;res.x=x-b.x;res.y=y-b.y;
		return res;
	}
	node operator + (const node &b)const{
		node res;res.x=x+b.x;res.y=y+b.y;
		return res;
	}
	long long operator * (const node &b)const{
		return x*b.y-y*b.x;
	}
	bool operator < (const node &b)const{
//		if(x!=b.x)return x<b.x;
//		return y<b.y;
		if(y!=b.y)return y<b.y;
		return x<b.x;
	}
}p[maxn*2],s[3][maxn*2],sta[maxn*10];
long long qread(){
	long long i=0,j=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
	return i*j;
}
long long dist(node a){
	return a.x*a.x+a.y*a.y;
}
long long Cross(node a,node b,node c){
	return (a-b)*(c-b);
}
bool cmp(node a,node b){
	long long t=(p[1]-a)*(p[1]-b);
	if(t==0)return dist(p[1]-a)<dist(p[1]-b);
	return t>0;
}
int tubao(int n,int id){
	int r=0;
	sort(p+1,p+n+1);
	for(int i=1;i<=n;i++){
		while(r>1&&Cross(s[id][r],s[id][r-1],p[i])>=0)r--;
		s[id][++r]=p[i];
	}
	int rr=r;
	for(int i=n-1;i>=1;i--){
		while(r>rr&&Cross(s[id][r],s[id][r-1],p[i])>=0)r--;
		s[id][++r]=p[i];
	}
	reverse(s[id]+1,s[id]+r+1);
	return r;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)p[i].x=qread(),p[i].y=qread();
	n=tubao(n,1);
	for(int i=1;i<=m;i++)p[i].x=qread(),p[i].y=qread();
	m=tubao(m,2);n--;m--;
	top=1;
	sta[top]=s[1][1]+s[2][1];
	for(int i=1,j=1;i<=n||j<=m;){
		node x=s[1][(i-1)%n+1]+s[2][j%m+1],y=s[1][i%n+1]+s[2][(j-1)%m+1];
		if((x-sta[top])*(y-sta[top])>=0)sta[++top]=x,j++;
		else sta[++top]=y,i++;
	}
	long long ans=0;
	for(int i=2;i<top;i++)
		ans+=(sta[i]-sta[1])*(sta[i+1]-sta[1]);
	cout<<ans;
	return 0;
}
