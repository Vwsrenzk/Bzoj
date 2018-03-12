#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int p,K,r,n;
struct node{
	long long zu[50][50];
	node(){memset(zu,0,sizeof(zu));}
	node operator * (const node x)const{
		node res;
		for(int i=0;i<K;i++)
			for(int j=0;j<K;j++)
				for(int k=0;k<K;k++)
					res.zu[i][j]=(res.zu[i][j]+1LL*zu[i][k]*x.zu[k][j]%p)%p;
		return res;
	}
}C,X,R;
node Pow(node x,long long y){
	while(y){
		if(y&1)R=R*X;
		X=X*X;
		y>>=1;
	}
}
int main(){
	scanf("%d%d%d%d",&n,&p,&K,&r);
	C.zu[0][0]=1;
	for(int i=0;i<K;i++){
		X.zu[(i-1+K)%K][i]=1;
		X.zu[i][i]++;
		R.zu[i][i]=1;
	}
	Pow(X,1LL*n*K);
    printf("%lld\n",(C*R).zu[0][r]);  
    return 0;
}
