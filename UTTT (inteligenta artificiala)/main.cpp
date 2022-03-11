#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;


int crsx=2, crsy=2, crsxd=2, crsyd=2,
actxd=0,
actyd=0,
turn=-1,
running, up
;

long long dis=1;


int Rnd(int low, int high)
{
        return rand() % high + low;
}

struct board{
int t[4][4];
int v;
}b[4][4];

struct cordw
{
    int xd;
    int yd;
    int x;
    int y;
    int w;
};



void display()
{
    system("cls");
    cout <<endl;
    if (turn==1) cout<<"X";
            else cout<<"O";
               cout<<endl;

    for (int i=1;i<=3;i++) ///yd
    {
        for (int j=1;j<=3;j++) ///y
        {
            for (int k=1;k<=3;k++) ///xd
            {
                if (b[k][i].v==0)
                {
                    for (int l=1;l<=3;l++) ///x
                    {
                    if (b[k][i].t[l][j]==1) cout<<"X";
                    else if (b[k][i].t[l][j]==-1) cout<<"O";
                    else cout<<"_";
                   // if (b[k][i].v==0)
                        cout<<" ";
                    //else cout<<b[k][i].v;
                    }
                }
                else if (b[k][i].v==1)
                {
                    if (j!=2)cout<<"*   * ";
                    if (j==2)cout<<"  *   ";
                }
                else if (b[k][i].v==-1)
                {
                    if (j!=2)cout<<"* * * ";
                    if (j==2)cout<<"*   * ";
                }
                cout<<"   ";
            }
            cout<<endl;
            if (crsyd==i&&crsy==j)
            {
                for (int ki=1;ki<=crsxd-1;ki++) cout<<"         ";
                for (int li=1;li<=crsx-1;li++) cout<<"  ";
                    cout<<"^";

            }

            cout<<endl;

        }
        if (i==actyd)
            {
                for (int ki=1;ki<=actxd-1;ki++) cout<<"         ";
                    cout<<"'''''";

            }
        cout<<endl;
        cout<<endl;
    }


}


void crsu (int a, int b)
{
    crsx+=a;
    crsy+=b;
    if (crsx>3)crsx=1,crsxd++;
    if (crsy>3)crsy=1,crsyd++;
    if (crsx<1)crsx=3,crsxd--;
    if (crsy<1)crsy=3,crsyd--;
    if (crsxd>3)crsxd=3,crsx=3;
    if (crsyd>3)crsyd=3,crsy=3;
    if (crsxd<1)crsxd=1,crsx=1;
    if (crsyd<1)crsyd=1,crsy=1;
}

bool chksp(board alph[4][4], int uxd, int uyd)
{
    for (int ux=1;ux<=3;ux++)
        for (int uy=1;uy<=3;uy++)
            if (alph[uxd][uyd].t[ux][uy]==0)return true;
    return false;
}

void chkmi(board alph[4][4], int uxd, int uyd)
{
    for (int ux=1;ux<=3;ux++)
        for (int uy=1;uy<=3;uy++)
    {
    int alphch=alph[uxd][uyd].t[ux][uy];
   // cout<<alphch;
    //int alphr;
        if (alphch!=0&&(ux==2||uy==2))
        {
        if (alph[uxd][uyd].t[ux-1][uy]==alphch&&alphch==alph[uxd][uyd].t[ux+1][uy])     alph[uxd][uyd].v=alphch;
        else if (alph[uxd][uyd].t[ux-1][uy-1]==alphch&&alphch==alph[uxd][uyd].t[ux+1][uy+1]) alph[uxd][uyd].v=alphch;
        else if (alph[uxd][uyd].t[ux+1][uy-1]==alphch&&alphch==alph[uxd][uyd].t[ux-1][uy+1]) alph[uxd][uyd].v=alphch;
        else if (alph[uxd][uyd].t[ux][uy-1]==alphch&&alphch==alph[uxd][uyd].t[ux][uy+1])     alph[uxd][uyd].v=alphch;
        else {ux-=3;uy-=3;}
              uy+=3;ux+=3;
        }
    }
}


int chkwi(board alph[4][4])
{
    for (int uxd=1;uxd<=3;uxd++)
        for (int uyd=1;uyd<=3;uyd++)
            chkmi(alph, uxd, uyd);
    for (int uxd=1;uxd<=3;uxd++)
        for (int uyd=1;uyd<=3;uyd++)
    {
        int alphch=alph[uxd][uyd].v;
        // cout<<alphch;
        //int alphr;
        if (alphch!=0&&(uxd==2||uyd==2))
        {
        if (alph[uxd-1][uyd].v==alphch&&alphch==alph[uxd+1][uyd].v)     return alphch;
        if (alph[uxd-1][uyd-1].v==alphch&&alphch==alph[uxd+1][uyd+1].v) return alphch;
        if (alph[uxd+1][uyd-1].v==alphch&&alphch==alph[uxd-1][uyd+1].v) return alphch;
        if (alph[uxd][uyd-1].v==alphch&&alphch==alph[uxd][uyd+1].v)     return alphch;
        }

    }



    return 0;

}

void clearr(board alph[4][4])
{
    for (int i=1;i<=3;i++)
        for (int j=1;j<=3;j++)
            alph[i][j].v=0;
   // int fixx=chkwi(alph);
}


cordw ai (board si[4][4],int side, int &acxd, int &acyd,int depth)
{

    cordw retur;
    retur.xd=0;
    retur.x=0;
    retur.yd=0;
    retur.y=0;
    retur.w=0;

   // si[acxd][acyd].t[ix][jy]=side;

    int txd=acxd,tyd=acyd;

    cordw cmpare,cmpmax;
    int eqp=0;

    if (depth<=5||(depth<=81&&Rnd(1,depth)==1&&dis<=531441)||(dis<=59049&&depth<=18))
    {




        for (int iacyd=1;iacyd<=3;iacyd++)
        for (int iacxd=1;iacxd<=3;iacxd++)
        for (int i=1;i<=3;i++)
        for (int j=1;j<=3;j++)
        {
            if (si[iacxd][iacyd].t[i][j]==0&&((iacxd==acxd&&iacyd==acyd)||acxd*acyd==0)&&si[iacxd][iacyd].v==0)
            {


                si[iacxd][iacyd].t[i][j]=side;


                chkwi(si);

                if (si[i][j].v==0&&chksp(si,i,j))
                    {
                    acxd=i;
                    acyd=j;
                    }
                    else acxd=0,acyd=0;

                if (chkwi(si)==side||si[iacxd][iacyd].v!=0) /// checkwin
                {


                    retur.x=i;
                    retur.y=j;
                    retur.xd=iacxd;
                    retur.yd=iacyd;
                    if (chkwi(si)==side)retur.w=side*(10/(depth+1)+1)*100;
                    else retur.w=side*(10/(depth+1)+1);

                    if (depth>0)
                    {
                        clearr(si);
                        acxd=txd;acyd=tyd;
                        si[iacxd][iacyd].t[i][j]=0;
                        chkwi(si);
                    }
                    crsxd=acxd;
                    crsyd=acyd;


                    return retur;
                }

                cmpare=ai(si,-side,acxd,acyd,depth+1);

                if (eqp==0||(cmpare.w>cmpmax.w&&side==1)||(cmpare.w<cmpmax.w&&side==-1))
                {
                    eqp=2;
                    cmpmax.w=cmpare.w;
                    cmpmax.x=i;
                    cmpmax.y=j;
                    cmpmax.xd=iacxd;
                    cmpmax.yd=iacyd;


                }
                else if (cmpare.w==cmpmax.w)
                {
                    if (Rnd(1,eqp)==1)
                    {
                    eqp++;
                    cmpmax.w=cmpare.w;
                    cmpmax.x=i;
                    cmpmax.y=j;
                    cmpmax.xd=iacxd;
                    cmpmax.yd=iacyd;
                    }
                }


                clearr(si);
                acxd=txd;acyd=tyd;
                si[iacxd][iacyd].t[i][j]=0;
                chkwi(si);


            }
        }


    }


    retur=cmpmax;
    if (depth==0)
    {

         si[retur.xd][retur.yd].t[retur.x][retur.y]=side;


                chkwi(si);

                if (si[retur.x][retur.y].v==0&&chksp(si,retur.x,retur.y))
                    {
                    acxd=retur.x;
                    acyd=retur.y;
                    crsxd=acxd;
                    crsyd=acyd;
                    }
                    else acxd=0,acyd=0;

       // turn=side*-1;
    }
  /// if (dis>=531441)display();
    dis++;
    return retur;
}

int main()
{
  //  b[1][1].t[1][1]=0;
 srand(time(NULL));



display();

    while(running==0)
    {
        if(GetAsyncKeyState(VK_UP))
        {
            while (GetAsyncKeyState(VK_UP));
            crsu (0, -1);
            up++;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            while (GetAsyncKeyState(VK_DOWN));
            crsu (0, 1);
            up++;
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            while (GetAsyncKeyState(VK_LEFT));
            crsu (-1, 0);
            up++;
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            while (GetAsyncKeyState(VK_RIGHT));
            crsu (1, 0);
            up++;
        }
        if(GetAsyncKeyState(VK_CONTROL))
        {
            while (GetAsyncKeyState(VK_CONTROL));

            if (b[crsxd][crsyd].v==0&&b[crsxd][crsyd].t[crsx][crsy]==0&&(crsxd==actxd&&crsyd==actyd||actyd*actxd==0))
            {
                b[crsxd][crsyd].t[crsx][crsy]=turn;


               // chkmi(b, crsxd, crsyd);
                if (chkwi(b)!=0)running++;


                if (b[crsx][crsy].v==0&&chksp(b,crsx,crsy))
                {
                    actxd=crsx;
                    actyd=crsy;
                    crsxd=actxd;
                    crsyd=actyd;
                    crsx=2; crsy=2;
                }
                else actxd=0,actyd=0;

                //chkmi(b, crsxd, crsyd, crsx, crsy);
               // ai (b,turn,actxd,actyd,0);

           /// ai (b,turn,actxd,actyd,0);
           ///    dis=1;

                turn=1;

                if (chkwi(b)!=0)running++;

               ai (b,turn,actxd,actyd,0);
               dis=1;

                if (chkwi(b)!=0)running++;

                turn=-1;


            }

            up++;
        }


        if (up!=0)
        {
            up=0;
            display();

        }
    }
     display();
     cout<<endl;
      if (chkwi(b)==1) cout<<"Winner is X";
            else cout<<"Winner is O";
           //  cout<<chkwi(b);
     cin>>running;
}
