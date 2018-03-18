#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define maxn 100010
using namespace std;
struct node{double x,y;}b[maxn],cir;
double R;
double sqr(double x){return x*x;}
double dis(node x,node y){
	return sqrt(sqr(x.x-y.x)+sqr(x.y-y.y));
}
bool incircle(node x){
	if(dis(cir,x)<=R)return 1;
	return 0;
}
node solve(double a,double b,double c,double d,double e,double f){
	double y=(f*a-c*d)/(b*d-e*a);
	double x=(f*b-c*e)/(a*e-b*d);
	return (node){x,y};
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lf%lf",&b[i].x,&b[i].y);
	random_shuffle(b+1,b+n+1);
	R=0;
	for(int i=1;i<=n;i++)
		if(!incircle(b[i])){
			cir.x=b[i].x;cir.y=b[i].y;R=0;
			for(int j=1;j<i;j++)
				if(!incircle(b[j])){
					cir.x=(b[i].x+b[j].x)/2.0;
					cir.y=(b[i].y+b[j].y)/2.0;
					R=dis(cir,b[i]);
					for(int k=1;k<j;k++)
						if(!incircle(b[k])){
							cir=solve(b[i].x-b[j].x,b[i].y-b[j].y,(sqr(b[j].x)+sqr(b[j].y)-sqr(b[i].x)-sqr(b[i].y))/2,b[i].x-b[k].x,b[i].y-b[k].y,(sqr(b[k].x)+sqr(b[k].y)-sqr(b[i].x)-sqr(b[i].y))/2);
							R=dis(b[i],cir);
						}
				}
		}
//	printf("%.10lf\n%.10lf %.10lf",R,cir.x,cir.y);
	printf("%.3lf",R);
	return 0;
}
