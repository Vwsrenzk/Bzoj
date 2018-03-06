#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;
long long p,a,b,x1,xn;
long long qread(){
    long long i=0,j=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')j=-1;ch=getchar();}
    while(ch<='9'&&ch>='0'){i=i*10+ch-'0';ch=getchar();}
    return i*j;
}
int Pow(int x,int y){
    int res=1;
    while(y){
        if(y&1)res=1LL*res*x%p;
        x=1LL*x*x%p;
        y>>=1;
    }
    return res;
}
void work1(){
    if(b==0){puts("-1");return;}
    int ans=0;
    ans=((xn-x1)%p+p)%p;
    ans=1LL*ans*Pow(b,p-2)%p;
    ans++;
    printf("%d\n",ans);
}
int bsgs(long long a,long long b){
    long long m,v,e=1;
    m=sqrt(p)+0.5;
    v=Pow(Pow(a,m),p-2);
    map<long long,long long>x;
    x[1]=0;
    for(int i=1;i<m;i++){
        e=e*a%p;
        if(!x.count(e))x[e]=i;
    }
    for(int i=0;i<m;i++){
        if(x.count(b))return i*m+x[b];
        b=b*v%p;
    }
    return -2;
}
int main(){
    int T;scanf("%d",&T);
    while(T--){
        p=qread();a=qread();b=qread();x1=qread();xn=qread();
        if(x1==xn){puts("1");continue;}
        if(a==0){
            if(xn==b)puts("2");
            else puts("-1");
            continue;
        }
        if(a==1){work1();continue;}
        long long aa=(xn*(1-a)-b)%p;
        int bb=Pow((x1*(1-a)-b)%p,p-2);
        printf("%d\n",bsgs(a,aa*bb%p)+1);
    }
    return 0;
}
