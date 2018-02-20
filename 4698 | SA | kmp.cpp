#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 1000010
using namespace std;
int n,mn=2e9,mx=0,lt,rt=2e9,mid,ans=1;
int a[1010][1010],l[1010],b[maxn],id[maxn],tot,vis[1010],cnt;
int sa[maxn],ta[maxn],rk[maxn],ht[maxn],wa[maxn],wb[maxn],ca[maxn],cb[maxn];
void SA(){
	for(int i=1;i<=tot;i++)++ca[b[i]];
	for(int i=1;i<=mx;i++)ca[i]+=ca[i-1];
	for(int i=tot;i;i--)sa[ca[b[i]]--]=i;
	rk[sa[1]]=1;
	for(int i=2;i<=tot;i++)rk[sa[i]]=rk[sa[i-1]]+(b[sa[i]]!=b[sa[i-1]]);
	for(int k=1;rk[sa[tot]]<tot;k<<=1){
		memset(ca,0,sizeof(ca));
		memset(cb,0,sizeof(cb));
		for(int i=1;i<=tot;i++)++ca[wa[i]=rk[i]],++cb[wb[i]=(i+k<=tot?rk[i+k]:0)];
		for(int i=1;i<=tot;i++)ca[i]+=ca[i-1],cb[i]+=cb[i-1];
		for(int i=tot;i;i--)ta[cb[wb[i]]--]=i;
		for(int i=tot;i;i--)sa[ca[wa[ta[i]]]--]=ta[i];
		rk[sa[1]]=1;
		for(int i=2;i<=tot;i++)rk[sa[i]]=rk[sa[i-1]]+(wa[sa[i]]!=wa[sa[i-1]]||wb[sa[i]]!=wb[sa[i-1]]);
	}
	for(int i=1,j=0;i<=tot;i++){
		if(--j<0)j=0;
		while(b[i+j]==b[sa[rk[i]-1]+j])j++;
		ht[rk[i]]=j;
	}
}
bool check(int k){
	for(int i=1;i<=tot;i++){
		if(ht[i]<k)memset(vis,0,sizeof(vis)),cnt=0;
		if(!vis[id[sa[i]]])vis[id[sa[i]]]=1,++cnt;
		if(cnt==n)return 1;
	}
	return 0;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&l[i]);
		for(int j=1;j<=l[i];j++){
			scanf("%d",&a[i][j]);
			if(j>1)mx=max(mx,a[i][j]-a[i][j-1]);
		}
		rt=min(rt,l[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=2;j<=l[i];j++)
			b[++tot]=a[i][j]-a[i][j-1],id[tot]=i;
		b[++tot]=++mx;
	}
	for(int i=1;i<=tot;i++)mn=min(mn,b[i]);
	for(int i=1;i<=tot;i++)b[i]=b[i]-mn+1,mx=max(mx,b[i]);
	SA();
	while(lt<=rt){
		int mid=(lt+rt)>>1;
		if(check(mid))lt=mid+1,ans=mid+1;
		else rt=mid-1;
	}
	printf("%d",ans);
}
