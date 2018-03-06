#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
//by:MirrorGray
using namespace std;
const int N=411111;
ll d[N];
int vis[N],top,sta[N];
int tot=-1,head[N],ver[N],nxt[N],len[N],fr[N];
queue <int> q;

void add(int x,int y,int z){
    nxt[++tot]=head[x];
    head[x]=tot;
    ver[tot]=y;
    len[tot]=z;
}

int bfs(int x){
    memset(d,-1,sizeof(d));
    int ret=0;d[x]=0;q.push(x);
    while(!q.empty()){
        int x=q.front();q.pop();
        if(d[ret]<d[x])ret=x;
        for(int i=head[x];~i;i=nxt[i])if(d[ver[i]]==-1){
            d[ver[i]]=d[x]+len[i];
            fr[ver[i]]=i;
            q.push(ver[i]);
        }
    }
    return ret;
}

ll dfs(int x,int f){
    ll ret=0;
    for(int i=head[x];~i;i=nxt[i])if(ver[i]!=f&&!vis[i>>1])
    ret=max(ret,dfs(ver[i],x)+len[i]);
    return ret;
}

int main(){
    memset(head,-1,sizeof(head));
    int n;scanf("%d",&n);
    for(int i=1;i<n;i++){
        int a,b,c;scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);add(b,a,c);
    }
    int p1,p2;p2=bfs(p1=bfs(1));
    ll dis=d[p2];int tmp=p2;
    printf("%lld\n",dis);
    while(true){
        sta[++top]=tmp,vis[fr[tmp]>>1]=true;
        if(tmp==p1)break;
        tmp=ver[fr[tmp]^1];
    }
    p1=top,p2=0;
    for(int i=1;i<=top;i++){
        ll tmp=dfs(sta[i],-1);
        if(tmp&&tmp+max(dis-d[sta[i]],d[sta[i]])==dis){
            if(d[sta[i]]+tmp==dis)p1=min(p1,i);
            else p2=max(p2,i);
        }
    }
    if(p1==top)p1=0;if(p2==0)p2=top;
    printf("%d\n",p2-p1);
    return 0;
}
