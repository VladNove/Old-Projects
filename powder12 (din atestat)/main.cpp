
///numpad1 sand
///numpad2 water
///numpad0 wall
///rightctrl delete

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using namespace std;


int type[90][210],crsx,crsy,i,j,up[90][210],li,lj,wba[2000],wqa[2000],wbb[2000],wqb[2000],wb[90][210],wen,wk,wk2,wk3,a,b;

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
    int clr=0;
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
   else if (type[a][b]==1)
   {
       if (6!=clr)display2(clr),clr=6;
       screen+="*";
   }
    else if (type[a][b]==2)
    {
        if (9!=clr)display2(clr),clr=9;
    screen+="~";
      // screen+=wb[a][b]+('0'-0);
    }


        else if (type[a][b]==0)screen+=" ";

        }
    screen+="\n";
    }

    display2(clr);
}


void gravity()
{for (int a=1; a<=li;a++) //update
    {
        for (int b=1; b<=lj;b++)
        {
            if (type[a][b]==1) // sand
            {
                if (type[a+1][b]%2==0||type[a+1][b-1]%2==0||type[a+1][b+1]%2==0)up[a][b]=1;
            }

            if (type[a][b]==2) // water
            {
                if (type[a+1][b]==0||type[a+1][b-1]==0||type[a+1][b+1]==0||type[a][b-1]==0||type[a][b+1]==0)up[a][b]=2;
            }
        }
    }


    for (int a=1; a<=li;a++) //replace
    {
        for (int b=1; b<=lj;b++)
        {
            if (up[a][b]==1) // sand
            {
                if (type[a+1][b]%2==0)swap(type[a+1][b],type[a][b]);
                    else if (type[a+1][b-1]%2==0||type[a+1][b+1]%2==0)
                {
                    if (rnd(0,2)==1&&type[a+1][b-1]%2==0||type[a+1][b+1]%2!=0)swap(type[a+1][b-1],type[a][b]);
                        else swap(type[a+1][b+1],type[a][b]);
                }
            }

            if (up[a][b]==2) // water
            {
                if (type[a+1][b]==0)swap(type[a+1][b],type[a][b]);

                else if (type[a+1][b-1]==0||type[a+1][b+1]==0)
                {
                    if (rnd(0,2)==1&&type[a+1][b-1]==0||type[a+1][b+1]!=0)swap(type[a+1][b-1],type[a][b]);
                        else swap(type[a+1][b+1],type[a][b]);
                }

                else if (type[a][b-1]==0||type[a][b+1]==0)
                {
                    if (rnd(0,2)==1&&type[a][b-1]==0||type[a][b+1]!=0)swap(type[a][b-1],type[a][b]);
                        else swap(type[a][b+1],type[a][b]);
                }

            }
            up[a][b]=0;
        }
    }


    wen=1; //water b
    for (a=1; a<=li;a++)
        for (b=1; b<=lj;b++)
            wb[a][b]=0;

        int wk=1;
        int wk2=1;
        int wk3=1;

    while (wk2==1)
    {
            wk2=0;
            wk=1;
        while (wk==1)
        {
                wk=0;
        for (int a1=1; a1<=li;a1++)
            for (int b1=1; b1<=lj;b1++)
            {
                if (type[a1][b1]==2)
                    {
                if (wb[a1][b1]==0 && wk3==1)wb[a1][b1]=wen,wk3=0;
                if (wb[a1][b1]==wen)
                {
                    for (i=-1;i<=1;i++)
                        for (j=-1;j<=1;j++)
                        {
                        if (type[a1+i][b1+j]==2 && wb[a1+i][b1+j]!=wen) wb[a1+i][b1+j]=wen,wk=1;
                        }
                }
                if (wb[a1][b1]==0)wk2=1;
                    }

            }
        }
        wen++;
        wk3=1;
    }

     for (i=1;i<=wen;i++)wba[i]=0,wqa[i]=0,wbb[i]=0,wqb[i]=0;  //wequal

     int kwqb=0;
     int difw1;
     int difw2;
    for (int a=1; a<=li;a++)
        for (int b=1; b<=lj;b++)
        {
            difw1=0;
            difw2=0;
            if (type[a][b]==2 && wba[wb[a][b]]==0)wba[wb[a][b]]=a,wbb[wb[a][b]]=b;
            if (type[a][b]==2&&(type[a-1][b-1]==0||type[a-1][b]==0||type[a-1][b+1]==0))
            {
                if (wbb[wb[a][b]]-b>0)difw1=wbb[wb[a][b]]-b;
                else difw1=b-wbb[wb[a][b]];

                if (wbb[wb[a][b]]-wqb[wb[a][b]]>0)difw2=wbb[wb[a][b]]-wqb[wb[a][b]];
                else difw2=wqb[wb[a][b]]-wbb[wb[a][b]];

             if (a-1>wba[wb[a][b]]&&(kwqb==0||difw1<difw2))wqa[wb[a][b]]=a,wqb[wb[a][b]]=b,kwqb=1;

            }
        }

    for (i=1;i<=wen;i++)
    {
        if (wqa[i]!=0)
            for (j=-1;j<=1;j++)
                if (type[wqa[i]-1][wqb[i]+j]==0)
                {
                    swap(type[wqa[i]-1][wqb[i]+j],type[wba[i]][wbb[i]]);
                    wba[i]=0;wqa[i]=0;wbb[i]=0;wqb[i]=0;
                    swap(wb[wqa[i]-1][wqb[i]+j],wb[wba[i]][wbb[i]]);
                    j=1;
                }
    }






}

void walls ()
{
for (i=0; i<=li+1;i++)
    {
        for (j=0; j<=lj+1;j++)
        {
            if (i==li+1||j==0||j==lj+1||i==0) type[i][j]=-1;
        }
    }
}

int main()
{
    srand (time(NULL));
    li=9*3;
    lj=21*4;
    int simspd =50;
    crsx=1;
    crsy=1;
    walls();

    COORD zerozero={0,0};
    CONSOLE_CURSOR_INFO crsvis;
    crsvis.bVisible = 0,crsvis.dwSize = 1;
    SetConsoleCursorInfo(handle, &crsvis);

    while (true)
    {
        SetConsoleCursorPosition( handle, zerozero );

        if( GetAsyncKeyState(VK_LEFT))
        {
            if (crsx==1)crsx=lj;
            else crsx--;
        }
        if( GetAsyncKeyState(VK_RIGHT))
        {
            if (crsx==lj)crsx=1;
            else crsx++;
        }
        if( GetAsyncKeyState(VK_UP))
        {
            if (crsy==1)crsy=li;
            else crsy--;
        }
        if( GetAsyncKeyState(VK_DOWN))
        {
            if (crsy==li)crsy=1;
            else crsy++;
        }
        if( GetAsyncKeyState(VK_NUMPAD1))
        {
            type[crsy][crsx]=1;
        }
        if( GetAsyncKeyState(VK_NUMPAD2))
        {
            type[crsy][crsx]=2;
        }
        if( GetAsyncKeyState(VK_RCONTROL))
        {
            type[crsy][crsx]=0;
        }
        if( GetAsyncKeyState(VK_NUMPAD0))
        {
            type[crsy][crsx]=-1;
        }

        if( GetAsyncKeyState(VK_MULTIPLY))
        {
            for (int a=1; a<=li;a++)
        for (int b=1; b<=lj;b++)
        {
            type[a][b]=0;
        }
        }

        if( GetAsyncKeyState(VK_SUBTRACT))
        {
            for (int a=0; a<=li+1;a++)for (int b=0; b<=lj+1;b++)
                if (b==0||b==lj+1||a==0)
                    type[a][b]=0;
        }

        if( GetAsyncKeyState(VK_ADD))
        {
            walls();
        }

            for (int a=0; a<=li+1;a++)for (int b=0; b<=lj+1;b++)
                if (type[a][b]!=-1&&(a==li+1||b==0||b==lj+1||a==0))
                    type[a][b]=0;

        gravity();
        display();
        Sleep(simspd);
    }




}
