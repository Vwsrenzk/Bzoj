#include<iostream>
#include<cstdio>
#include<cstring>
#define INF 100000000
#define f(a,b,c) g[a][b][c+8]
using namespace std;
int bin[20],T,n,t[1010],b[1010],g[1010][256][16];
int cal(int x,int y){
	if(x==0)return 0;
	return t[x]^t[y];
}
int main(){
	bin[0]=1;
	for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d%d",&t[i],&b[i]);
		for(int i=1;i<=n+1;i++)
			for(int j=0;j<bin[8];j++)
				for(int k=-8;k<=7;k++)
					f(i,j,k)=INF;
		f(1,0,-1)=0;
		for(int i=1;i<=n;i++)
			for(int j=0;j<bin[8];j++)
				for(int k=-8;k<=7;k++)
					if(f(i,j,k)<INF){
						if(j&1)f(i+1,j>>1,k-1)=min(f(i+1,j>>1,k-1),f(i,j,k));
						else {
							int r=INF;
							for(int l=0;l<=7;l++)
								if((j&bin[l])==0){
									if(i+l>r)break;
									r=min(r,b[i+l]+i+l);
									f(i,j+bin[l],l)=min(f(i,j+bin[l],l),f(i,j,k)+cal(i+k,i+l));
								}
						}
					}
		int ans=INF;
		for(int k=-8;k<=-1;k++)
			ans=min(f(n+1,0,k),ans);
		printf("%d\n",ans);
	}
	return 0;
}
