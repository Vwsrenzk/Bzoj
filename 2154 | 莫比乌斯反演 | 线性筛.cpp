#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int N=1e7+10, MD=20101009;
int p[N], pcnt, n, m;
bool np[N];
ll g[N];
void init() {
    g[1]=1;
    int i, j, t;
    for(i=2; i<=n; ++i) {
        if(!np[i]) p[++pcnt]=i, g[i]=1-i;
        for(j=1; j<=pcnt; ++j) {
            t=p[j]*i; if(t>n) break;
            np[t]=1;
            if(i%p[j]==0) { g[t]=g[i]; break; }
            g[t]=g[i]*(1-p[j]);
        }
    }
    for(i=2; i<=n; ++i) g[i]*=i;
    for(i=1; i<=n; ++i) g[i]+=g[i-1], g[i]%=MD;
}
int main() {
    scanf("%d%d", &n, &m); if(n>m) swap(n, m);
    init();
    ll ans=0, t1, t2;
    for(int i=1, pos=0; i<=n; i=pos+1) {
        pos=min(n/(n/i), m/(m/i));
        t1=((ll)(n/i)*(n/i+1)/2)%MD;
        t2=((ll)(m/i)*(m/i+1)/2)%MD;
        ans+=((g[pos]-g[i-1])*((t1*t2)%MD))%MD;
        ans%=MD;
    }
    printf("%lld\n", ((ans%MD)+MD)%MD);
    return 0;
}
