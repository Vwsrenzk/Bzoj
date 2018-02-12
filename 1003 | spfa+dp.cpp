/*
	题目大意：
		一张图中有一些点在一些时间段不能同行，必须绕过这些点，而绕过需要付出费用，问n个时间内最少费用 
	题解： 
		本题有两个关键点：
		1.求一段时间内的共有dis
		2.dp求答案
			    
		dp[i]表示到第i天的最小花费
		dp[i]=min{dp[j]+f[j+1][i]*(i-j)+k} (0<=j<i)
		f[i][j]表示从第i天到第j天的最短路，预处理即可。  
*/
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<queue>
#include<iostream>
#include<algorithm>
#define INF 1000000000
using namespace std;
bool tag[21],a[21][110],vis[21];
int num,head[21],dis[21],q[21],f[110][110],dp[110];
struct node{
    int to,pre,v;
}e[1010];
int n,m,k,day,cnt;
void Insert(int from,int to,int v){
    e[++num].to=to;
    e[num].v=v;
    e[num].pre=head[from];
    head[from]=num;
}
void spfa(){
    memset(dis,0x3f,sizeof(dis));
    for(int i=2;i<=n;i++)dis[i]=INF;
    memset(vis,0,sizeof(vis));
    dis[1]=0;vis[1]=1;
    queue<int>q;q.push(1);
    while(!q.empty()){
        int now=q.front();q.pop();vis[now]=0;
        for(int i=head[now];i;i=e[i].pre){
            int to=e[i].to;
            if(dis[to]>dis[now]+e[i].v){
                dis[to]=dis[now]+e[i].v;
                if(!vis[to]&&!tag[to]){
                    vis[to]=1;q.push(to);
                }
            }
        }
    }
}
int main(){
    scanf("%d%d%d%d",&day,&n,&k,&m);
    int x,y,z,l,r;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        Insert(x,y,z);Insert(y,x,z);
    }
    scanf("%d",&cnt);
    for(int i=1;i<=cnt;i++){
        scanf("%d%d%d",&x,&l,&r);
        for(int j=l;j<=r;j++)a[x][j]=1;
    }
    for(int i=1;i<=day;i++){
        memset(tag,0,sizeof(tag));
        for(int j=i;j<=day;j++){
            for(int k=1;k<=n;k++)tag[k]|=a[k][j];
            spfa();
            f[i][j]=dis[n];
        }
    }
    dp[0]=-k;
    for(int i=1;i<=day;i++){
        dp[i]=INF;
        for(int j=0;j<i;j++)
            if(f[j+1][i]!=INF)dp[i]=min(dp[i],dp[j]+f[j+1][i]*(i-j)+k);
    }
    printf("%d\n",dp[day]);
    return 0;
}
