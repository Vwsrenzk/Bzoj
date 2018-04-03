#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<set>
#define mod 1000000
using namespace std;
set<long long>s;
set<long long>::iterator it;
int now;
long long ans;
int main(){
	int n,opt,x;
	scanf("%d",&n);
	s.insert(100000000000000),s.insert(-100000000000000);
	while(n--){
		scanf("%d%d",&opt,&x);
		if(opt==0){//宠物 
			if(s.size()==2){
				now=1;
				s.insert(x);
			}
			else if(now==1){//宠物比较多 
				s.insert(x);
			}
			else {//人比较多 
				it=s.lower_bound(x);
				int nxt=*it;
				int pre=*(--it);
				int mn=min(x-pre,nxt-x);
				ans+=mn;
				if(x-pre==nxt-x) s.erase(nxt);
				else if(x-pre<nxt-x) s.erase(pre);
				else s.erase(nxt);
			}
		}
		else {
			if(s.size()==2){
				now=-1;
				s.insert(x);
			}
			else if(now==-1){s.insert(x);}
			else {
				it=s.lower_bound(x);
				int nxt=*it;
				int pre=*(--it);
				int mn=min(x-pre,nxt-x);
				ans+=mn;
				if(x-pre==nxt-x) s.erase(pre);
				else if(x-pre<nxt-x) s.erase(pre);
				else s.erase(nxt);
			}
		}
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
