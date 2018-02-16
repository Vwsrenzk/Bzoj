#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 400001
using namespace std;
struct node{
    int from,to,pre;
}e[maxn];
int n,m,k,num;
int fa[maxn],head[maxn],fire[maxn],tot[maxn];
bool use[maxn];
void Insert(int from,int to){
    e[++num].to=to;
    e[num].from=from;
    e[num].pre=head[from];
    head[from]=num;
}
int find(int x){
    if(fa[x]==x)return x;
    return fa[x]=find(fa[x]);
}
int main(){
    scanf("%d%d",&n,&m);int x,y;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        Insert(x,y);Insert(y,x);
    }
    scanf("%d",&k);
    for(int i=1;i<=k;i++){
        scanf("%d",&x);
        use[x]=1;fire[i]=x;
    }
    for(int i=0;i<n;i++)fa[i]=i;
    int block=n-k,kk=0;
    for(int i=1;i<=num;i++){
        if(!use[e[i].from]&&!use[e[i].to]&&find(e[i].from)!=find(e[i].to)){
            block--;
            fa[find(e[i].from)]=find(e[i].to);
        }
    }
    tot[++kk]=block;
    for(int i=k;i>=1;i--){
        block++;
        use[fire[i]]=0;
        for(int j=head[fire[i]];j;j=e[j].pre){
            if(!use[e[j].to]&&find(fire[i])!=find(e[j].to)){
                block--;
                fa[find(fire[i])]=find(e[j].to);
            }
        }
        tot[++kk]=block;
    }
    for(int i=kk;i>=1;i--)printf("%d\n",tot[i]);
    return 0;
}
