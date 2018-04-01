#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int ans,n;
int SG(int x,int y){
	long long t=2;
	for(int i=0;;i++,t<<=1){
		if((x-1&t-1)<(t>>1)&&(y-1&t-1)<(t>>1))
		return i;
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		int x,y;ans=0;
		for(int i=1;i<=n/2;i++){
			scanf("%d%d",&x,&y);
			ans^=SG(x,y);
		}
		if(ans)puts("YES");
		else puts("NO");
	}
	return 0;
}
