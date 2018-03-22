#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define N 60005
#define MAX 60005*10-5
using namespace std;

int n,m,c[N],v[N][2];
struct tree{int l,r,lmx,rmx,mx,ans;}t[N*10];

void updata(int d,int l,int r)
{
    t[d].mx=max(t[l].mx,t[r].mx);
    t[d].ans=t[l].ans+t[r].ans;
    t[d].l=t[l].l;t[d].lmx=t[l].lmx;
    t[d].r=t[r].r;t[d].rmx=t[r].rmx;
    int mx=max(t[l].rmx,t[r].lmx);
    if (t[l].r==t[r].l) t[d].ans-=c[t[l].r];
    else if (mx>=max(c[t[l].r],c[t[r].l])) t[d].ans-=mx;
    else if (c[t[l].r]>c[t[r].l])
    {
        t[d].ans-=c[t[l].r];
        if (t[l].l==t[l].r) t[d].l=t[r].l,t[d].lmx=max(t[l].mx,t[r].lmx);
    }
    else
    {
        t[d].ans-=c[t[r].l];
        if (t[r].l==t[r].r) t[d].r=t[l].r,t[d].rmx=max(t[r].mx,t[l].rmx);
    }
}

void build(int d,int l,int r)
{
    if (l+1==r)
    {
        t[d].mx=max(v[l][0],v[l][1]);
        if (t[d].mx>=max(c[l],c[r]))
        {
            t[d].l=l;t[d].r=r;t[d].lmx=t[d].rmx=0;
			t[d].ans=v[l][0]+v[l][1]+c[l]+c[r]-t[d].mx;
        }
        else if (c[l]>c[r])
        {
            t[d].l=t[d].r=r;t[d].lmx=t[d].mx;
			t[d].rmx=0;t[d].ans=v[l][0]+v[l][1]+c[r];
        }
        else
        {
            t[d].l=t[d].r=l;t[d].rmx=t[d].mx;
			t[d].lmx=0;t[d].ans=v[l][0]+v[l][1]+c[l];
        }
        return;
    }
    int mid=(l+r)/2;
    build(d*2,l,mid);build(d*2+1,mid,r);
    updata(d,d*2,d*2+1);
}

void ins(int d,int l,int r,int x,int y)
{
    if (x>y) return;
    if (l+1==r)
    {
        t[d].mx=max(v[l][0],v[l][1]);
        if (t[d].mx>=max(c[l],c[r]))
        {
            t[d].l=l;t[d].r=r;t[d].lmx=t[d].rmx=0;
			t[d].ans=v[l][0]+v[l][1]+c[l]+c[r]-t[d].mx;
        }
        else if (c[l]>c[r])
        {
            t[d].l=t[d].r=r;t[d].lmx=t[d].mx;
			t[d].rmx=0;t[d].ans=v[l][0]+v[l][1]+c[r];
        }
        else
        {
            t[d].l=t[d].r=l;t[d].rmx=t[d].mx;
			t[d].lmx=0;t[d].ans=v[l][0]+v[l][1]+c[l];
        }
        return;
    }
    int mid=(l+r)/2;
    ins(d*2,l,mid,x,min(y,mid));
    ins(d*2+1,mid,r,max(x,mid),y);
    updata(d,d*2,d*2+1);
}

tree query(int d,int l,int r,int x,int y)
{
    if (l==x&&r==y) return t[d];
    int mid=(l+r)/2;
    if (y<=mid) return query(d*2,l,mid,x,y);
    else if (x>=mid) return query(d*2+1,mid,r,x,y);
    else
    {
        tree u=query(d*2,l,mid,x,mid),v=query(d*2+1,mid,r,mid,y);
        t[MAX-2]=u;t[MAX-1]=v;
        updata(MAX,MAX-2,MAX-1);
        return t[MAX];
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<n;i++) scanf("%d",&v[i][0]);
    for (int i=1;i<n;i++) scanf("%d",&v[i][1]);
    for (int i=1;i<=n;i++) scanf("%d",&c[i]);
    build(1,1,n);
    for (int i=1;i<=m;i++)
    {
        char op[2];
        scanf("%s",op);
        if (op[0]=='Q')
        {
            int l,r;
            scanf("%d%d",&l,&r);
            if (l==r) printf("%d\n",c[l]);
            else
            {
                tree u=query(1,1,n,l,r);
                printf("%d\n",u.ans);
            }
        }
        else
        {
            int x1,y1,x2,y2,w;
            scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&w);
            if (x1>x2) swap(x1,x2);
            if (y1>y2) swap(y1,y2);
            if (x1==x2) v[y1][x1-1]=w;
            else c[y2]=w;
            ins(1,1,n,y1,y2);
        }
    }
    return 0;
}
