#include <iostream>
#include <windows.h>
#include <stdlib.h>


///COPYRIGHT VLAD NOVETSCHI

using namespace std;
HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);

int v[100][100],up,ner[100][100],mt[100][100],sle[100][100];
int rdc[100][100],nrrad;
int nrcarb,nrhidr;
struct nrpozrad
{
    int n, p[20];
};

nrpozrad til[100];

struct coord
{
    int x, y;
};

int mnr,tmp1,tmp2,tmrad;
coord crs,cner;

int debug1,debug2;


///43 4f 50 59 52 49 47 48 54 0a 4d 41 44 45 20 42 59 20 56 4c 41 44 20 4e 4f 56 45 54 53 43 48 49

coord dir (int a)
{
    coord ret;
    ret.y=0;
    ret.x=0;
    if (a==1)ret.y=-1;
    if (a==2)ret.x=1;
    if (a==3)ret.y=1;
    if (a==4)ret.x=-1;
    return ret;
}

string nomen[100]={
"met","et","prop","but","pent","hex","hept","oct",
"non","dec","undec","dodec","tridec","tetradec","pentadec"
    };

    string multi[100]={
"","di","tri","tetra","penta","hexa","hepta","octa",
"nona","deca","undeca","dodeca","trideca","tetradeca","pentadeca"
    };

void display ()
{

    system("cls");
    SetConsoleCursorPosition( handle, {0,0} );
    string screen;
    int i, j;
    for (i=1;i<=21;i++)
    {
        for (j=1;j<=21;j++)
        {
            if (j==21||i==21)screen+="#";
            else
            {

            if (v[i][j]==-1)screen +="C";
            else if (v[i][j]==1)screen +="-";
            else if (v[i][j]==2)screen +="=";
            else if (v[i][j]==3)screen +="~";
            else screen +=" ";
            }
            screen+=" ";
        }
        screen+="\n";
    }
    screen+="\n";


    for (int i=16;i>=1;i--)
    {
        if (til[i].n>0)
        {
            for (j=1;j<=til[i].n;j++)
            {
                screen+=til[i].p[j]+'0';
                if (j!=til[i].n)screen+=",";
            }
            screen+=" ";
            screen+=multi[til[i].n-1];
            screen+=nomen[i-1]+"il";
            screen+=" - ";
        }
    }
    if (mnr>=1)screen+=nomen[mnr-1]+"an\n";
   // for (i=1;i<=20;i++){for (j=1;j<=20;j++)screen+=rdc[i][j]+'0';screen+="\n";}
    cout<<screen<<endl;
    cout<<"C"<<nrcarb<<"H"<<nrhidr;
    SetConsoleCursorPosition( handle, {(crs.x-1)*2,(crs.y-1)} );
}

int sleg (int a, int b)
{
    int ret=0;
    for (int x=1;x<=4;x++)
    {
        if (v[a+dir(x).y][b+dir(x).x]!=0)
            ret++;
    }
    return ret;
}

void resmt()
{
    for (int x=1;x<=20;x++)
        for (int y=1;y<=20;y++)
        mt [x][y]=0;
}

void fil(int a, int b, int c)
{
    if (v[a][b]==-1)c++,mt[a][b]=c;
    if (c>tmp1)tmp1=c;
    if (v[a][b]>=1)mt[a][b]=c;
    for (int x=1;x<=4;x++)
    {
        if (v[a+dir(x).y][b+dir(x).x]!=0)
            {
                if(mt[a+dir(x).y][b+dir(x).x]==0)fil(a+dir(x).y,b+dir(x).x,c);
            }
    }

}

void ers (int a, int b)
{

    for (int x=1;x<=4;x++)
    if  (v[a+dir(x).y][b+dir(x).x]>=1&&mt[a+dir(x).y][b+dir(x).x]!=-1)
        mt[a+dir(x).y][b+dir(x).x]=-1,
        ers (a+dir(x).y,b+dir(x).x);
    //cout<<"x";
}

void rfil (int a, int b,int c)
{
    if (v[a][b]==-1)c++,rdc[a][b]=c;
    if (c>tmrad)tmrad=c;
    if (v[a][b]>=1)rdc[a][b]=c;
     for (int x=1;x<=4;x++)
    {
        if (v[a+dir(x).y][b+dir(x).x]!=0)
            {
                if(rdc[a+dir(x).y][b+dir(x).x]==-1)rfil(a+dir(x).y,b+dir(x).x,c);
                if(ner[a+dir(x).y][b+dir(x).x]>0)tmp2=ner[a+dir(x).y][b+dir(x).x];
            }
    }
}

void den ()
{
    tmp1=0;
    mnr=0;
    nrcarb=0;
    int i,j,k,ok,l;
    for (i=1;i<=20;i++)
        for (j=1;j<=20;j++)
        if (v[i][j]==-1)sle[i][j]=sleg(i,j),nrcarb++;
    nrhidr=2*nrcarb+2;

    for (i=1;i<=20;i++)
        for (j=1;j<=20;j++)
        if (sle[i][j]==1||(sle[i][j]==0&&v[i][j]==-1))
    {
        resmt();
        fil(i,j,0);
        if (tmp1>mnr)cner.y=i,cner.x=j,mnr=tmp1;
    }
     resmt();
    fil (cner.y,cner.x,0);

    for (k=mnr;k>=1;k--)
    {
        ok=0;
        for (i=1;i<=20;i++)
        for (j=1;j<=20;j++)
        {
            if (mt[i][j]==k&&v[i][j]==-1)
            {
            for (l=1;l<=4;l++)
                if(mt[i+dir(l).y][j+dir(l).x]>=k||k==mnr&&ok==0)ok=1,mt[i][j]=mnr+1;
            }
        }

        for (i=1;i<=20;i++)
        for (j=1;j<=20;j++)
        {
            if (mt[i][j]==k&&v[i][j]==-1)
            {
                mt[i][j]=-1;
                ers(i,j);
            }
            if (mt[i][j]==mnr+1) mt[i][j]=k;
        }

    }


    int invo=0,inva=0;
    for (i=1;i<=20;i++)
        for (j=1;j<=20;j++)
            if (mt[i][j]>=1&&sle[i][j]>=3)invo+=mt[i][j]*(sle[i][j]-2);
    for (i=1;i<=20;i++)
        for (j=1;j<=20;j++)
            if (mt[i][j]>=1&&sle[i][j]>=3)inva+=(mnr+1-mt[i][j])*(sle[i][j]-2);

            debug1=invo;
            debug2=inva;
    for (i=1;i<=20;i++)
        for (j=1;j<=20;j++)
        {

             if (inva<invo&&mt[i][j]>0)ner[i][j]=mnr+1-mt[i][j];
             else ner[i][j]=mt[i][j];
             if (mt[i][j]<0)rdc[i][j]=-1;
             else rdc[i][j]=0;
        }


    for (i=1;i<=20;i++)
    {
        til[i].n=0;
    }

        ok=0;
        for (i=1;i<=20;i++)
        for (j=1;j<=20;j++)
        {
            if (rdc[i][j]==-1)
            {
                tmrad=0;
                rfil(i,j,0);
                til[tmrad].n++;
                til[tmrad].p[til[tmrad].n]=tmp2;
            }
        }

    for (k=1;k<=16;k++)
    {
        for (i=1;i<=til[k].n-1;i++)
            for (j=i+1;j<=til[k].n;j++)
                if (til[k].p[i]>til[k].p[j])swap(til[k].p[i],til[k].p[j]);
    }



}

int main()
{
    crs.x=1;
    crs.y=1;

    while(true)
    {
          if(GetAsyncKeyState(VK_UP))
        {
            while (GetAsyncKeyState(VK_UP));
            if (crs.y>1)crs.y--;
            up++;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            while (GetAsyncKeyState(VK_DOWN));
            if (crs.y<20) crs.y++;
            up++;
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            while (GetAsyncKeyState(VK_LEFT));
            if (crs.x>1) crs.x--;
            up++;
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            while (GetAsyncKeyState(VK_RIGHT));
            if (crs.x<20) crs.x++;
            up++;
        }

        if(GetAsyncKeyState(VK_RIGHT))
        {
            while (GetAsyncKeyState(VK_RIGHT));
            if (crs.x<20) crs.x++;
            up++;
        }

        if(GetAsyncKeyState(0x43))
        {
            while (GetAsyncKeyState(0x43));
            v[crs.y][crs.x]=-1;
            up++;den();
        }

        if(GetAsyncKeyState(0x45))
        {
            while (GetAsyncKeyState(0x45));
            v[crs.y][crs.x]=0;
            up++;den();
        }
         if(GetAsyncKeyState(0x31))
        {
            while (GetAsyncKeyState(0x31));
            v[crs.y][crs.x]=1;
            up++;den();
        }
        if(GetAsyncKeyState(0x31))
        {
            while (GetAsyncKeyState(0x31));
            v[crs.y][crs.x]=1;
            up++;den();
        }
        if(GetAsyncKeyState(0x32))
        {
            while (GetAsyncKeyState(0x32));
            v[crs.y][crs.x]=2;
            up++;den();
        }
        if(GetAsyncKeyState(0x33))
        {
            while (GetAsyncKeyState(0x33));
            v[crs.y][crs.x]=3;
            up++;den();
        }

        if (up!=0)up=0, display();
    }
}
