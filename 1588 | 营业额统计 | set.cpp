#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;
set<int>s;
set<int>::iterator it;
int ans;
int main(){
    s.insert(-1000000000);s.insert(1000000000);
    int n,x;
    scanf("%d",&n);
    scanf("%d",&ans);
    s.insert(ans);
    ans=abs(ans);
    for(int i=2;i<=n;i++){
        scanf("%d",&x);
        it=s.lower_bound(x);
        int nxt=*it;
        int pre=*(--it);
        int mn=min(nxt-x,x-pre);
        int vis=s.count(x);
        if(vis)mn=0;
        ans+=mn;
        s.insert(x);
    }
    printf("%d",ans);
}
