#include<iostream>
#include<cstdio>
#include<cstring>
#define maxn 100010
using namespace std;
struct node{bool x[2],y[2],z[2];}tr[maxn*4];
char op[10];
int n,r1,r2,c1,c2;
int dx[3]={-1,0,1},dy[3]={0,1,0};
bool a[maxn][2][2];
void build(int l,int r,int k){
	if(l==r){
		tr[k].x[0]=1;
		tr[k].x[1]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,k<<1);
	build(mid+1,r,k<<1|1);
}
void update(node &k,node &l,node &r,int mid){
	k.x[0]=(l.x[0]&&a[mid][0][0]&&r.x[0])||(l.z[0]&&a[mid][1][0]&&r.z[1]);  //左上-右上 
    k.x[1]=(l.x[1]&&a[mid][1][0]&&r.x[1])||(l.z[1]&&a[mid][0][0]&&r.z[0]);  //左下-右下 
    k.y[0]=l.y[0]||(l.x[0]&&a[mid][0][0]&&r.y[0]&&a[mid][1][0]&&l.x[1]);  //左上-左下
    k.y[1]=r.y[1]||(r.x[0]&&a[mid][0][0]&&l.y[1]&&a[mid][1][0]&&r.x[1]);  //右上-右下
    k.z[0]=(l.x[0]&&a[mid][0][0]&&r.z[0])||(l.z[0]&&a[mid][1][0]&&r.x[1]);  //左上-右下 
    k.z[1]=(l.x[1]&&a[mid][1][0]&&r.z[1])||(l.z[1]&&a[mid][0][0]&&r.x[0]); 
}
void link(int k,int l,int r,int p){
	if(l==r){
		tr[k].y[0]=tr[k].y[1]=tr[k].z[0]=tr[k].z[1]=a[p][0][1];
		tr[k].x[0]=tr[k].x[1]=1;
		return;
	}
	int mid=(l+r)>>1;
	if(p<=mid)link(k<<1,l,mid,p);
	else link(k<<1|1,mid+1,r,p);
	update(tr[k],tr[k<<1],tr[k<<1|1],mid);
}
void change(bool w){
	int d;
	for(int i=0;i<3;i++)
		if(c1+dx[i]==c2&&r1+dy[i]==r2)d=i;
	if(d==0)a[c2][r2][0]=w,link(1,1,n,c2);
	else if(d==1)a[c1][0][1]=w,link(1,1,n,c1);
	else a[c1][r1][0]=w,link(1,1,n,c1);
}
void get(node &p,int k,int L,int R,int l,int r){
    if (L>=l&&R<=r) {p=tr[k];return;}
    int mid=(L+R)>>1;
    if (r<=mid) get(p,k<<1,L,mid,l,r);
    else if (l>mid) get(p,k<<1|1,mid+1,R,l,r);
    else{
        node t1,t2;
        get(t1,k<<1,L,mid,l,r);
        get(t2,k<<1|1,mid+1,R,l,r);
        update(p,t1,t2,mid);
    }
}
void ask(){
	if(c1>c2)swap(r1,r2),swap(c1,c2);
	node p1,p2,p3;
	get(p1,1,1,n,1,c1);
	get(p2,1,1,n,c1,c2);
	get(p3,1,1,n,c2,n);
	if(r1==r2){
		if(r1==0){
			if (p2.x[0]||(p1.y[1]&&p2.x[1]&&p3.y[0])||(p1.y[1]&&p2.z[1])||(p3.y[0]&&p2.z[0])) puts("Y");
            else puts("N");
		}
		else{
			if (p2.x[1]||(p2.x[0]&&p1.y[1]&&p3.y[0])||(p1.y[1]&&p2.z[0])||(p3.y[0]&&p2.z[1])) puts("Y");
            else puts("N");
		}
	}
	else{
		if(r1==0){
			if (p2.z[0]||(p1.y[1]&&p2.x[1])||(p2.x[0]&&p3.y[0])) puts("Y");
            else puts("N");
		}
		else {
			if (p2.z[1]||(p1.y[1]&&p2.x[0])||(p3.y[0]&&p2.x[1])) puts("Y");
            else puts("N");
		}
	}
}
int main(){
	scanf("%d",&n);
	build(1,n,1);
	while(1){
		scanf("%s",op);
		if(op[0]=='E')return 0;
		scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
		r1--;r2--;
		if(r1>r2)swap(c1,c2),swap(r1,r2);
		if(op[0]=='O')change(1);
		else if(op[0]=='C')change(0);
		else ask();
	}
	return 0;
}
