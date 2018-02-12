#include<iostream>
#include<cstdio>
#include<algorithm>
#define maxn 50010
using namespace std;
int top,n;
bool ans[maxn];
struct node{double x,y;int id;}st[maxn],line[maxn];
bool cmp(node a,node b){
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;
}
double Cross(node a,node b){return (b.y-a.y)/(a.x-b.x);}
void Insert(node a){
	while(top!=0){
		if(st[top].x==a.x)top--;
		else if((top>1)&&Cross(a,st[top-1])<=Cross(st[top],st[top-1]))top--;
		else break;
	}
	st[++top]=a;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&line[i].x,&line[i].y);
		line[i].id=i;
	}
	sort(line+1,line+n+1,cmp);
	for(int i=1;i<=n;i++)Insert(line[i]);
	for(int i=1;i<=top;i++)ans[st[i].id]=1;
	for(int i=1;i<=n;i++)
		if(ans[i])printf("%d ",i);
}
