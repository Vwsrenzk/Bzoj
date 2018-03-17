#include<iostream>
#include<cstdio>
#include<set>
#include<algorithm>
#define maxn 500010
using namespace std;
int n,ans,p[maxn],q[maxn];
char ch[maxn];
set<int>t;
void manacher(){
	int mx=0,id;
	for(int i=1;i<=n;i++){
		if(mx>=i)p[i]=min(mx-i,p[2*id-i]);
		else p[i]=0;
		while(ch[i+p[i]+1]==ch[i-p[i]])p[i]++;
		if(p[i]+i>mx)id=i,mx=p[i]+i;
	}
}
bool cmp(int a,int b){return (a-p[a])<(b-p[b]);}
int main(){
	scanf("%d",&n);
	scanf("%s",ch+1);
	ch[0]='#';
	manacher();
	for(int i=1;i<=n;i++)q[i]=i;
	sort(q+1,q+n+1,cmp);
	int now=1;
	for(int i=1;i<=n;i++){
		while(now<=n&&q[now]-p[q[now]]<=i){
			t.insert(q[now]);
			now++;
		}
		set<int>::iterator tmp=t.upper_bound(i+p[i]/2);
		if(tmp!=t.begin()){
			ans=max(ans,(*--tmp-i)*4);
		}
	}
	printf("%d\n",ans);
	return 0;
}
