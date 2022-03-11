#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


using namespace std;

struct table
{
    int p[100];
}m,t;

int Rnd(int low, int high)
{
        return rand() % high + low;
}



int checkwin(table mt)
{
    int r=-1;

    int dp1=1;
    int dp2=1;
    int ds1=1;
    int ds2=1;
    int msp=1;

    for (int i=1;i<=3;i++)
    {
        int l1=1;
        int l2=1;
        int c1=1;
        int c2=1;
    for (int j=1;j<=3;j++)
    {
        if (mt.p[(i-1)*3+j]==0)msp=0;
        if (mt.p[(i-1)*3+j]!=-1)l1=0;
        if (mt.p[(i-1)*3+j]!=1)l2=0;
        if (mt.p[(j-1)*3+i]!=-1)c1=0;
        if (mt.p[(j-1)*3+i]!=1)c2=0;
        if (i==j&&mt.p[(i-1)*3+j]!=-1)dp1=0;
        if (i==j&&mt.p[(i-1)*3+j]!=1)dp2=0;
        if (i==3+1-j&&mt.p[(i-1)*3+j]!=-1)ds1=0;
        if (i==3+1-j&&mt.p[(i-1)*3+j]!=1)ds2=0;
    }
    if (l1==1||c1==1)return -1;
    if (l2==1||c2==1)return 1;

    }
    if (ds1==1||dp1==1)return -1;
    if (ds2==1||dp2==1)return 1;
    if (msp==0)return 2;
    return 0;
}

int act (table mx,int c,int pc, int ww)
{
    mx.p[pc]=c;
  //  for (int i=1;i<=3;i++){for (int j=1;j<=3;j++)if (mx.p[(i-1)*3+j]==0)cout <<"_"; else if (mx.p[(i-1)*3+j]==1)cout << "O";else cout<<"X";cout<<endl;}
    int chk=checkwin(mx);
    if (chk==c&&ww==0)return 1;
    if (chk==c&&ww==1)return pc;
    if (chk==-c)return -1;
    if (chk==0)return 0;
    int r=0,rt=c;
    if (chk==2)
    for (int i=1;i<=9;i++)
    {
        if (mx.p[i]==0)
        {
            int ri=-act(mx,-c,i,0);
            if (ri<rt||r==0)r=i,rt=ri;
            //if (ri==rt)if(Rnd(1,2)==1)r=i,rt=ri;
        }
    }
    if (ww==0)
    return rt;
    else return r;
}



int main()
{
    srand(time(NULL));

    int k=0,x;
    cin>>k;
    while (checkwin(m)==2)
    {
        k++;
        if (k%2==1)
        {cin>>x;
        m.p[x]=-1;
        }
        else
        {
            int r=0,rt=-1;
            for (int i=1;i<=9;i++)
            {
                if (m.p[i]==0)
                {
                    int ri=act(m,1,i,0);
                    if (ri==1&&act(m,1,i,1)==i)r=i,i=10;
                   else if (ri>rt||r==0)r=i,rt=ri;
                }
            }
            cout<<rt<<" "<<act(m,1,r,1)<<endl;
            m.p[r]=1;
        }


        for (int i=1;i<=3;i++)
        {

        for (int j=1;j<=3;j++)

            if (m.p[(i-1)*3+j]==0)cout <<"_";
            else if (m.p[(i-1)*3+j]==1)cout << "O";
                else cout<<"X";

            cout<<endl;
        }

        cout<<endl;
    }
}
