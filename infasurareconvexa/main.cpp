#include <iostream>

using namespace std;
struct punct
{
    int x;
    int y;
}p[100];
int det (punct a, punct b)
{
    return a.x*b.y-a.y*b.x;
}
punct trans (punct a, punct b)
{
    punct r;
    r.x=a.x-b.x;
    r.y=a.y-b.y;
    return r;
}
int lunp (punct a)
{
    return a.x*a.x+a.y*a.y;
}
int n, c[100],pm,k=1,d;
int main()
{
    cin>>n;
    for (int i =1; i<=n;i++)
        {
            cin>>p[i].x>>p[i].y;
            if (p[i].x<p[c[1]].x||p[c[1]].x==0)c[1]=i;
        }
    do
    {
        pm=0;
        for (int i =1; i<=n;i++)
        {

            if (i!=c[k])
            {
                    d= det(trans(p[i],p[c[k]]),trans(p[pm],p[c[k]]));
                if (pm==0||d<0)pm=i;
                else if (d==0&&lunp(trans(p[i],p[c[k]]))<lunp(trans(p[pm],p[c[k]])))pm=i;
            }
        }

        k++;
        c[k]=pm;
    }
    while (c[k]!=c[1]);

    for (int i =1; i<=k;i++)cout<<c[i];
}
