
///numpad1 sand
///numpad2 water
///numpad0 wall
///rightctrl delete

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;


int type[90][210],crsx,crsy,li,lj;
float posx,posy,spdx,spdy,acc;

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
    for (int a=0; a<=li+1;a++)
    {
        for (int b=0; b<=lj+1;b++)
        {

    if (b==crsx&&a==crsy)
    {
        if (7!=clr)display2(clr),clr=7;
        screen+="O";
    }
   else if (type[a][b]==-1)
   {
       if (8!=clr)display2(clr),clr=8;
       screen+="#";
   }
   else if (type[a][b]>=15)
   {
       if (9!=clr)display2(clr),clr=9;
       screen+="*";

   }
   else if (type[a][b]>=10)
   {
       if (1!=clr)display2(clr),clr=1;
       screen+="*";

   }
   else if (type[a][b]>=5)
   {
       if (14!=clr)display2(clr),clr=14;
       screen+="*";

   }
    else if (type[a][b]>=1)
    {
        if (6!=clr)display2(clr),clr=6;
    screen+="*";

       //screen+=wb[a][b]+('0'-0);
    }


        else if (type[a][b]==0)screen+=" ";

        }
    screen+="\n";

    }
    display2(clr);
}


void walls ()
{
for (int i=0; i<=li+1;i++)
    {
        for (int j=0; j<=lj+1;j++)
        {
            if (type[i][j]>=1) type[i][j]--;
            if (type[i][j]==10)type[i][j]=0;
            if (i==li+1||j==0||j==lj+1||i==0) type[i][j]=-1;
        }
    }
}

int mod (int x)
{
    return (x>=0)?x:-x;
}
int sgn(int x)
{
    return (x>=0)?1:-1;
}
int main()
{
    srand (time(NULL));
    li=9*3;
    lj=21*4;
    int simspd =0;
    crsx=1;
    crsy=1;
    posx=lj/2;
    posy=li/2;
    acc=0.01;
    float coef=0.005;
    float grav=0.005;
    walls();

    COORD zerozero={0,0};
    CONSOLE_CURSOR_INFO crsvis;
    crsvis.bVisible = 0,crsvis.dwSize = 1;
    SetConsoleCursorInfo(handle, &crsvis);

    while (true)
    {
        SetConsoleCursorPosition( handle, zerozero );
        SetConsoleCursorInfo(handle, &crsvis);
        if( GetAsyncKeyState(VK_LEFT))
        {
            spdx-=acc;
            if (spdx<=0) type[crsy][crsx+1]=10;
            else type[crsy][crsx+1]=20;
        }
        if( GetAsyncKeyState(VK_RIGHT))
        {
            spdx+=acc;
            if (spdx>=0) type[crsy][crsx-1]=10;
            else type[crsy][crsx-1]=20;
        }
        if( GetAsyncKeyState(VK_UP))
        {
            spdy-=acc;
            if (spdy<=0) type[crsy+1][crsx]=10;
            else type[crsy+1][crsx]=20;
        }
      //  if( GetAsyncKeyState(VK_DOWN))
       // {
        //    spdy+=acc;
        //    if (spdy>=0) type[crsy-1][crsx]=10;
      //      else type[crsy-1][crsx]=20;
      //  }
        if (posx<=1)posx=lj-acc;
        if (posx>=lj)posx=1+acc;
        if (posy<=1)posy=1+acc,spdy=0;
        if (posy*3>=li*4)posy=li*4/3-acc,spdy=0;
        crsx=int(posx+0.5);
        crsy=int(posy*3/4+0.5);
        posx+=spdx;
        spdy+=grav;
        posy+=spdy;
        if (crsy==li) spdx+=(spdx>0)?-coef:coef;
      //  if (pow((li/2-posy),2)+pow((lj/2-posx),2)>=100)spdx*=-1,spdy*=-1;
        walls ();
        display();
        cout<<spdx<<"\t\t\n"<<spdy<<"\t\t";
        Sleep(simspd);
    }




}
