#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn 200010
#define INF 1000000000
using namespace std;
int d,n1,n2,c1,c2,tc,a[maxn],sum;
deque<pair<int,int> >q;
int check(int x){
	q.clear();
	int res=x*(tc-c2);
	q.push_back(make_pair(1-n2,x));
	for(int i=1;i<=d;i++){
		if(i>n1)q.push_back(make_pair(i-n1,a[i-n1]));
		int now=a[i];
		while(now){
			if(q.empty())return INF;
			if(q.front().first+n2<=i){
				pair<int,int>x=q.front();q.pop_front();
				int t=min(now,x.second);
				x.second-=t;now-=t;res+=t*c2;
				if(x.second)q.push_front(x);
			}
			else {
				pair<int,int>x=q.back();q.pop_back();
				int t=min(now,x.second);
				x.second-=t;now-=t;res+=t*c1;
				if(x.second)q.push_back(x);
			}
		}
	}
	return res;
}
int main(){
	scanf("%d%d%d%d%d%d",&d,&n1,&n2,&c1,&c2,&tc);
	for(int i=1;i<=d;i++)scanf("%d",&a[i]),sum+=a[i];
	c1=min(c1,tc);c2=min(c2,tc);
	if(n1>n2)swap(n1,n2),swap(c1,c2);
	c2=min(c1,c2);
	int ans=INF,l=1,r=sum;
	while(r-l>=5){
		int mid1=(2*l+r)/3,mid2=(l+2*r)/3;
		int lc=check(mid1),rc=check(mid2);
		if(lc<rc)r=mid2;
		else l=mid1;
	}
	for(int i=l;i<=r;i++)ans=min(ans,check(i));
	printf("%d",ans);
	return 0;
}
