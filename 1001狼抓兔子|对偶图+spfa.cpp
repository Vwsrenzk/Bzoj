#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define maxn (1010*1010*2)
using namespace std;
int n,m,head[maxn],num,dis[maxn],S=0,T;
struct node{int to,pre,v;}e[maxn*6+10];
bool vis[maxn];
void Insert(int from,int to,int v){
    e[++num].to=to;
    e[num].v=v;
    e[num].pre=head[from];
    head[from]=num;
}
deque<int>q;
void spfa(){
    memset(dis,0x3f,sizeof(dis));
    q.push_back(S);
    vis[S]=1;dis[S]=0;
    while(!q.empty()){
        int now=q.front();q.pop_front();vis[now]=0;
        for(int i=head[now];i;i=e[i].pre){
            int to=e[i].to;
            if(dis[to]>dis[now]+e[i].v){
                dis[to]=dis[now]+e[i].v;
                if(!vis[to]){
                    vis[to]=1;
                    if(!q.empty()&&dis[to]<dis[q.front()])q.push_front(to);
                    else q.push_back(to);
                }
            }
        }
    }
}
int main(){
    //freopen("Cola.txt","r",stdin);
    scanf("%d%d",&n,&m);
    T=(n-1)*(m-1)*2+1;
    int x,y,z;
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++){
            scanf("%d",&z);
            if(i==1){x=T,y=j*2;}
            else if(i==n){x=S,y=(n-2)*(m-1)*2+j*2-1;}
            else{x=(i-1)*(m-1)*2+j*2-m*2+1;y=x+m*2-1;}
            Insert(x,y,z);Insert(y,x,z);
        }
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++){
            scanf("%d",&z);
            if(j==1){x=S;y=(i-1)*(m-1)*2+1;}
            else if(j==m){x=T;y=i*(m-1)*2;}
            else{x=(i-1)*(m-1)*2+(j-1)*2;y=x+1;}
            Insert(x,y,z);Insert(y,x,z);
        }
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++){
            scanf("%d",&z);
            x=(i-1)*(m-1)*2+j*2-1;y=x+1;
            Insert(x,y,z);Insert(y,x,z);
        }
    spfa();
    printf("%d",dis[T]);
}
