/*
7
-1 4
-1 2
-1 2
-2 2
-2 2
-2 -2
-2 -2
2 -2
2 -2
2 2
2 2
1 2
1 2
1 4
*/
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;


int type[180][410],crsx,crsy,li,lj;
float posx,posy,spdx,spdy,acc,pangle,tspd,fov;
float dtype[410];
string screen;

HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);

int rnd(int a, int b)
{
    return rand()%b+a;
}

void display2(int color)

{
    SetConsoleTextAttribute(handle, color);
    cout<<screen;
    screen.clear();
}

void display()
{
    screen.clear();
   int clr=8;
    for (int a=0; a<=li-1;a++)
    {
        for (int b=0; b<=lj+1;b++)
        {


    if (type[a][b]==1)


       screen+="#";
       if (type[a][b]==2)screen+="[";

    if (type[a][b]==3)screen+="]";

        else if (type[a][b]==0)screen+=" ";

        }
    screen+="\n";

    }
    for (int a=li; a>=0;a--)
    {
        for (int b=0; b<=lj+1;b++)
        {


    if (type[a][b]==1)


       screen+="#";

    if (type[a][b]==2)screen+="[";

       if (type[a][b]==3)screen+="]";
    if (type[a][b]==0)screen+=".";

        }
    screen+="\n";

    }
    display2(clr);
}
float mi (float x, float y) {return (x<=y)?x:y;}
float ma (float x, float y) {return (x>=y)?x:y;}
float sgn(float x)
{
    if (x>0)return 1;
    if (x<0)return -1;
    if (x==0)return 0;

}

struct strucwalls{
float xa;
float xb;
float ya;
float yb;
};
void intrs (float t, float a, float b, float c, float i,float j, float k, float &rx, float&ry, int &ex ,float&distt)
{
    if ((j-k)*cos(t)-sin(t)*(b-c)==0||(b-c)*sin(t)-cos(t)*(j-k)==0)
    {
        ex=0;rx=0;ry=0;
    }
    else
    {
        rx=((i*cos(t)-a*sin(t))*(b-c)-(b*k-j*c)*cos(t))/((j-k)*cos(t)-sin(t)*(b-c));
        ry=((a*sin(t)-i*cos(t))*(j-k)-(j*c-b*k)*sin(t))/((b-c)*sin(t)-cos(t)*(j-k));

        if ((rx-a)*sgn(cos(t))>=0&&(ry-i)*sgn(sin(t))>=0&&mi(b,c)<=rx&&rx<=ma(b,c)&&mi(j,k)<=ry&&ry<=ma(j,k))ex=1,distt=sqrt((rx-a)*(rx-a)+(ry-i)*(ry-i));
        else ex=0,distt=10000;
    }

}

float mod (float x)
{
    return (x>=0)?x:-x;
}

void cllr()
{
    for (int i=1;i<=li+1;i++)
        for (int j=1;j<=lj+1;j++)
        type[i][j]=0;
    for  (int j=1;j<=lj+1;j++)
        dtype[j]=-1;
}
int main()
{
    srand (time(NULL));
    li=20;
    lj=160;
    int simspd =0;
    float dcolt=0.1;
    int linewalls=1;
    posx=0;
    posy=0;
    pangle=0;
    fov=M_PI/2;
    acc=0.03;
    tspd=0.02;
    int nrpereti;
    strucwalls wall[100];
   // display();
 //  float a,b,c,i,j,k,t,rx,ry,distt;
//   int ex;
//   cin>> posx>>b>>c>>posy>>j>>k;
//   a=posx;
 //  i=posy;
 //  t=-M_PI;
 /*  for (int ite=1;ite<=lj;ite++)
   {
       intrs(t,a,b,c,i,j,k,rx,ry,ex,distt);
       t+=2*M_PI/lj;
       if (ex==1)
       {
       if (distt*cos(t)<=1)for (int ith=1;ith<=li;ith++) type [li-ith+1][ite]=1;
       else for (int ith=1;ith<=li/(distt*cos(t));ith++) type [li-ith+1][ite]=1;
       }
   }
   //intrs(t,a,b,c,i,j,k,rx,ry,ex,distt);
   display();*/
// cout<<M_PI<<" "<<rx<<" "<<ry<<" "<<distt;


    cin>>nrpereti;
    for (int npi=1;npi<=nrpereti;npi++)

        cin>>wall[npi].xa>>wall[npi].ya>>wall[npi].xb>>wall[npi].yb;

    COORD zerozero={0,0};
    CONSOLE_CURSOR_INFO crsvis;
    crsvis.bVisible = 0,crsvis.dwSize = 1;
    SetConsoleCursorInfo(handle, &crsvis);

    while (true)
    {

         SetConsoleCursorPosition( handle, zerozero );
        SetConsoleCursorInfo(handle, &crsvis);

        if( GetAsyncKeyState(VK_UP))
        {
            posx+=acc*cos(pangle);
            posy+=acc*sin(pangle);

        }
        if( GetAsyncKeyState(VK_DOWN))
        {
            posx-=acc*cos(pangle);
            posy-=acc*sin(pangle);

        }
        if( GetAsyncKeyState(VK_LEFT))
        {
            posy+=acc*cos(pangle);
            posx-=acc*sin(pangle);

        }
        if( GetAsyncKeyState(VK_RIGHT))
       {
            posy-=acc*cos(pangle);
            posx+=acc*sin(pangle);
       }
       if( GetAsyncKeyState(0x41))
       {
          pangle+=tspd;
       }
       if( GetAsyncKeyState(0x44))
       {
          pangle-=tspd;
       }
       if( GetAsyncKeyState(0x50))
       {
          fov+=tspd;
       }
       if( GetAsyncKeyState(0x4F))
       {
          fov-=tspd;
       }
       if( GetAsyncKeyState(0x49))
       {
          fov=M_PI/2;
       }
        if( GetAsyncKeyState(0x4C))
       {
          linewalls=0;
       }
        if( GetAsyncKeyState(0x4B))
       {
          linewalls=1;
       }


       cllr();


for (int npi=1;npi<=nrpereti;npi++)
{
       float a,b,c,i,j,k,t,rx,ry,distt,tpangle;
       float colid=-1, colidt;
   int ex;
   b=wall[npi].xa;
   c=wall[npi].xb;
   j=wall[npi].ya;
   k=wall[npi].yb;
   a=posx;
   i=posy;
   t=pangle;
   t-=fov/2;

        a=posx;
        i=posy;

          // t=-M_PI;
        for (int ite=1;ite<=lj;ite++)
        {
       intrs(t,a,b,c,i,j,k,rx,ry,ex,distt);
       t+=fov/lj;

       if (ex==1&&(distt<=dtype[ite]||dtype[ite]<0))
       {
           dtype[ite]=distt;
           if (linewalls==1)tpangle=t-pangle;
           else tpangle=0;



       if (distt*mod(cos(tpangle))<=1)
       {
           for (int ith=1;ith<=li;ith++)
           {
               type [li-ith+1][lj-ite+1]=1;
               if (b-dcolt<=rx&&rx<=b+dcolt&&j-dcolt<=ry&&ry<=j+dcolt) type [li-ith+1][lj-ite+1]=2;
                if (c-dcolt<=rx&&rx<=c+dcolt&&k-dcolt<=ry&&ry<=k+dcolt) type [li-ith+1][lj-ite+1]=3;
           }
       }
       else
       {
           for (int ith=1;ith<=li/(distt*mod(cos(tpangle)));ith++)
           {
               type [li-ith+1][lj-ite+1]=1;
               if (ma(b,c)-dcolt<=rx&&rx<=ma(b,c)+dcolt&&ma(j,k)-dcolt<=ry&&ry<=ma(j,k)+dcolt) type [li-ith+1][lj-ite+1]=2;
                if (mi(b,c)-dcolt<=rx&&rx<=mi(b,c)+dcolt&&mi(j,k)-dcolt<=ry&&ry<=mi(j,k)+dcolt) type [li-ith+1][lj-ite+1]=3;
           }
       }
       }
        }




}

//wall[1].xa+=0.001;
        display();

       Sleep(1);
    }




}
