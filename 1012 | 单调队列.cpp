#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int q[200010],num[200010],n,mo,x,rem,t;
char ch[2];
int main(){
    scanf("%d%d",&n,&mo);
    int mark=0;//代表这是第几个输进去的数字 
    for(int i=1;i<=n;i++){
        scanf("%s%d",ch,&x);
        if(ch[0]=='A'){
            x=x%mo;
            mark++;x=(x+rem)%mo;
            while(q[t]<=x&&t>0)t--;
            q[++t]=x;num[t]=mark;
        }
        if(ch[0]=='Q'){
            rem=q[lower_bound(num+1,num+t+1,mark-x+1)-num];
            printf("%d\n",rem);
        }
    }
}
