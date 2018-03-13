#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long f[110][2][2][2],g[110][2][2][2],bin[64];
long long n,m,mod,k;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		cin>>n>>m>>k>>mod;
		n--,m--;
		long long ans=0;
		bin[0]=1;
		for(int i=1;i<=63;i++)bin[i]=bin[i-1]*2LL%mod;
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		f[0][1][1][1]=1;g[0][1][1][1]=0;
		for(int i=0;i<=63;i++)
		for(int a=0;a<2;a++)
		for(int b=0;b<2;b++)
		for(int c=0;c<2;c++)
			if(f[i][a][b][c]){
				int p=((n&(1LL<<(63-i)))==0)?0:1;
				int q=((m&(1LL<<(63-i)))==0)?0:1;
				int t=((k&(1LL<<(63-i)))==0)?0:1;
				for(int x=0;x<2;x++){
					if(a&(x>p))continue;
					for(int y=0;y<2;y++){
						if(b&&(y>q))continue;
						int z=x^y;
						if(c&&(z<t))continue;
						int A=(a&&(x==p))?1:0;
						int B=(b&&(y==q))?1:0;
						int C=(c&&(z==t))?1:0;
						f[i+1][A][B][C]=(f[i+1][A][B][C]+f[i][a][b][c])%mod;
						g[i+1][A][B][C]=(g[i+1][A][B][C]+g[i][a][b][c]+((z==0)?0:bin[63-i])*f[i][a][b][c]%mod)%mod;
					}
				}
			}
		k%=mod;
		for(int a=0;a<2;a++)
		for(int b=0;b<2;b++)
		for(int c=0;c<2;c++)
		ans=(ans+g[64][a][b][c]-k*f[64][a][b][c]%mod+mod)%mod;
		cout<<ans<<endl;
	}
	return 0;
}
