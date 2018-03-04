#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int SG,x,flag,n;
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);SG=flag=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			SG^=x;
			if(x!=1)flag=1;
		}
		if((SG==0&&flag==0)||(SG!=0&&flag==1))puts("John");
		else puts("Brother");
	}
	return 0;
}
