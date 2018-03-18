#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define maxn 50010
const double pi=acos(-1);
using namespace std;
int n,deg,p;
double r;
struct node{
	double x,y;
	node(double x=0,double y=0){}
	node operator - (const node w)const{
		node res;
		res.x=x-w.x;res.y=y-w.y;
		return res;
	}
}a[maxn],c;
node rotate(node t,int tmp){
	double rt=1.0*tmp/180*pi;
	node res;
	res.x=t.x*cos(rt)-t.y*sin(rt);
    res.y=t.x*sin(rt)+t.y*cos(rt);
    return res;
}
double sqr(double x){return x*x;}
double dis(node a,node b){
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}
bool incircle(node a){
	return dis(a,c)<=r;
}
node getcentre(node A,node B,node C){
	double a1=B.x-A.x,b1=B.y-A.y,c1=(a1*a1+b1*b1)/2;
	double a2=C.x-A.x,b2=C.y-A.y,c2=(a2*a2+b2*b2)/2;
	double d=a1*b2-b1*a2;node res;
	res.x=A.x+(c1*b2-c2*b1)/d;
    res.y=A.y+(c2*a1-c1*a2)/d;
    return res;
}
void getcircle(){
	random_shuffle(a+1,a+n+1);
	c=a[1];r=0;
	for(int i=1;i<=n;i++){
		if(!incircle(a[i])){
			c=a[i];r=0;
			for(int j=1;j<i;j++){
				if(!incircle(a[j])){
					c.x=(a[i].x+a[j].x)/2.0;
					c.y=(a[i].y+a[j].y)/2.0;
					r=dis(c,a[i]);
					for(int k=1;k<j;k++){
						if(!incircle(a[k])){
							c=getcentre(a[i],a[j],a[k]);
							r=dis(c,a[i]);
						}
					}
				}
			}
		}
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf%lf",&a[i].x,&a[i].y);
	scanf("%d%d",&deg,&p);
	for(int i=1;i<=n;i++){
		a[i]=rotate(a[i],-deg);a[i].x/=p;
	}
	getcircle();
	printf("%.3lf",r);
}
