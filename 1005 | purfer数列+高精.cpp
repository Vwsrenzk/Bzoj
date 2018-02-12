/*
	题目大意：
		给出标号为1到N的点,以及某些点最终的度数,允许在任意两点间连线,可产生多少棵度数满足要求的树? 
	题解：
		purfer数列，具体见http://www.cnblogs.com/zhj5chengfeng/p/3278557.html 
		质因数分解，避免高精除法 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1010
using namespace std;
bool vis[maxn];
int p[maxn],cnt,d[maxn],n,num,sum,tot[maxn];
struct node{
	int len,zu[10003];
	node(){memset(zu,0,sizeof(zu));len=0;}
	node operator * (const int &b)const{
		node c;
		for(int i=1;i<=len;i++){
			c.zu[i]+=zu[i]*b;
			c.zu[i+1]+=c.zu[i]/10;
			c.zu[i]%=10;
		}
		c.len=len;
		while(c.zu[c.len+1]){
			c.len++;
			c.zu[c.len+1]+=c.zu[c.len]/10;
			c.zu[c.len]%=10;
		}
		return c;
	}
}ans;
void prepare(){
	for(int i=2;i<=n;i++){
		if(!vis[i])p[++num]=i;
		for(int j=1;j<=num&&i*p[j]<=n;j++){
			vis[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
void add(int x,int delta){
	for(int i=1;i<=num;i++){
		if(x==1)return;
		while(x%p[i]==0){
			x/=p[i];
			tot[i]+=delta;
		}
	}
}
int main(){
	scanf("%d",&n);
	int x;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		if(x!=-1){
			d[++cnt]=x;
			sum+=x-1;
		}
	}
	prepare();
	if(n==1){
		if(x>0)puts("0");
		else puts("1");
		return 0;
	}
	if(sum>n-2){puts("0");return 0;}
	int down=n-2-sum;
	for(int i=n-2;i>down;i--)add(i,1);
	for(int i=1;i<=cnt;i++)
		for(int j=d[i]-1;j>1;j--)add(j,-1);
	add(n-cnt,down);
	ans.len=1;ans.zu[1]=1;
	for(int i=1;i<=num;i++)
		for(int j=tot[i];j>=1;j--)
			ans=ans*p[i];
	for(int i=ans.len;i>=1;i--)
		printf("%d",ans.zu[i]);
	return 0;
}
