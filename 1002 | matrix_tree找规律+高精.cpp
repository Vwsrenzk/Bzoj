/*
	题目大意：
		求n+1个点的完全图的生成树个数
	题解：
		由matrix_tree定理找规律可知f[i]=f[i-1]*3-f[i-2]+2;
		套上高精即可 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int a[101],b[101],c[101];
struct node{
    int zu[101],len;
    node operator * (const int x)const{
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(int i=1,j=len;i<=len;i++,j--)a[i]=zu[j];
        for(int i=1;i<=len;i++){
            b[i]+=a[i]*x;
            b[i+1]+=b[i]/10;
            b[i]%=10;
        }
        int l=len;
        while(b[l+1]){
            l++;
            b[l+1]+=b[l]/10;
            b[l]=b[l]%10;
        }
        node res;
        res.len=l;
        for(int i=1,j=l;i<=l;j--,i++)res.zu[i]=b[j];
        return res;
    }
    node operator + (const int x)const{
        memset(a,0,sizeof(a));
        for(int i=1,j=len;i<=len;j--,i++)a[i]=zu[j];
        a[1]+=x;
        int pos=1;
        while(a[pos]>=10){
            a[pos+1]++;
            a[pos]%=10;
            pos++;
        }
        int l;
        if(pos>len)l=pos;
        else l=len;
        node res;
        res.len=l;
        for(int i=1,j=l;i<=l;j--,i++)res.zu[i]=a[j];
        return res;
    }
    node operator - (const node x)const {
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        for(int i=1,j=len;i<=len;j--,i++)a[i]=zu[j];
        for(int i=1,j=x.len;i<=x.len;j--,i++)b[i]=x.zu[j];
        for(int i=1;i<=len;i++){
            a[i]-=b[i];
            if(a[i]<0){
                a[i]+=10;
                a[i+1]-=1;
            }
        }
        int l=len;
        while(a[l]==0)l--;
        node res;
        res.len=l;
        for(int i=1,j=l;i<=l;j--,i++)res.zu[i]=a[j];
        return res;
    }
}f[110];
int main(){
    int n;
    scanf("%d",&n);
    f[1].len=1;f[1].zu[1]=1;
    f[2].len=1;f[2].zu[1]=5;
    for(int i=3;i<=n;i++)
    	f[i]=f[i-1]*3-f[i-2]+2;
    for(int i=1;i<=f[n].len;i++)
        printf("%d",f[n].zu[i]);
    return 0;
}
