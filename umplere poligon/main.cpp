#include <iostream>

using namespace std;
int matr[100][100];
int mi (int x, int y)
{
    if (x<=y)return x;
    else return y;
}
int ma (int x, int y)
{
    if (x>=y)return x;
    else return y;
}

bool cup (int x, int y, int z)
{
    return (x<=ma(y,z)&&x>=mi(y,z));
}
bool cupe (int x, int y, int z)
{
    return (x<ma(y,z)&&x>mi(y,z));
}
bool inters (int i, int j, int a, int b, int c, int d)
{
    if (b>=d)
    return ((b-d)*j<(a-c)*i-a*d+c*b);
    else return ((b-d)*j>(a-c)*i-a*d+c*b);
}

bool apart (int i, int j, int a, int b, int c, int d)
{
    return ((b-d)*j-(a-c)*i+a*d-c*b==0);
}
int main()
{
    int a[100],b[100],n,arie=0;
    cin>>n;
    for (int i=1;i<=n;i++)
    cin>>a[i]>>b[i];
    a[n+1]=a[1];
    b[n+1]=b[1];
    a[0]=a[n];
    b[0]=b[n];
    for (int i=0;i<=90;i++)
    {
        for (int j=0;j<=90;j++)
        {
            int tr=0;
            for (int k=1;k<=n;k++)
            {
            if (apart(i,j,a[k],b[k],a[k+1],b[k+1])&&cup(i,b[k],b[k+1])&&cup(j,a[k],a[k+1]))tr=1,k=n+1;
            if (k<=n)
                {
                if(inters(i,j,a[k],b[k],a[k+1],b[k+1]) &&cup(i,b[k],b[k+1]))tr++;
                if (i==b[k]&&j<a[k]&&cupe(b[k],b[k-1],b[k+1]))tr++;
                }
            }
           if (tr%2==1)matr[i][j]=1,arie++;
        }
    }

    for (int i=20;i>=0;i--)
    {
        for (int j=0;j<=20;j++)
        cout<<matr[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    cout<<arie;

}
//&&j<b[k]&&cup(a[k],a[k-1],a[k+1])
//&&i<=ma(a,c)&&i>=mi(a,c)&&i<=ma(a,c)&&j>=mi(b,d)&&j<=ma(b,d)
//sig((b-d)*j-(a-c)*i+a*d-c*b)!=sig((b-d)*j-(a-c)*(i+1)+a*d-c*b)
