#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int f[50][10],bin[50];
int A,B;
int abs(int x){return x>0?x:-x;}
void prepare(){
    for(int i=0;i<=9;i++)f[1][i]=1;
    for(int i=2;i<=12;i++)
        for(int j=0;j<=9;j++)
            for(int k=0;k<=9;k++)
                if(abs(j-k)>=2)f[i][j]+=f[i-1][k];
}
int solve(int x){
    if(x==0)return 0;
    int len=0;
    while(x){
        bin[++len]=x%10;
        x/=10;
    }
    int res=0;
    for(int i=1;i<len;i++)
        for(int j=1;j<=9;j++)res+=f[i][j];
    for(int i=1;i<bin[len];i++)res+=f[len][i];
    for(int i=len-1;i>=1;i--){
        for(int j=0;j<bin[i];j++)
            if(abs(bin[i+1]-j)>=2)res+=f[i][j];
        if(abs(bin[i]-bin[i+1])<2)break;
    }
    return res;
}
int main(){
    scanf("%d%d",&A,&B);
    prepare();
    printf("%d",solve(B+1)-solve(A));
}
