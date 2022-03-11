
#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


//ifstream shipf ("ship.txt");

HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);

int playerPosX,playerPosY,movcldX,movcldY,pmovspdX,pmovspdY,playerHp;
int scrnplayerposx, scrnplayerposy;
int shipH,shipW,ship[100][100],shipposx,shipposy;
int endposx,endposy;
int location;
int minimap[100][100],miniH,miniW;
int mainmap[1500][1500],mainH,mainW;
int up[1500][1500];
int screenmap[1000][1000];
int hitmap[1500][1500];
int fireCold,firecld;
int range;
int enemymap[1500][1500],enemyPosx,enemyPosy,enemyHp,emovcldX,emovcldY,efirecld,escrnplayerposx, escrnplayerposy;

string screen;
int scrnH, scrnW;



void init()
{
    srand (time(NULL));
  //  shipf>>shipH>>shipW;
   // for (int i=1; i<=shipH;i++)
    //    for (int j=1;j<=shipW;j++)
       // shipf>>ship[i][j];
     //   playerPosX=8;playerPosY=5;
    miniW=10;
    miniH=10;
    scrnH=30;
    scrnW=60;
    pmovspdY=4;
    pmovspdX=3;
    fireCold=24;
    range=12;
    location=1;
    system("cls");
}

int rnd(int rnda, int rndb){return rand()%rndb+rnda;}




void display()
{
    CONSOLE_CURSOR_INFO crsvis;
    crsvis.bVisible = 0,crsvis.dwSize = 1;
    SetConsoleCursorInfo(handle, &crsvis);
    SetConsoleCursorPosition( handle, {0,0} );
    screen.clear();
}

void display2(int color)
{
    SetConsoleTextAttribute(handle, color);
    cout<<screen;
    screen.clear();
}

int clr;

atchr(int atvec, int atval, string atchar, int atcolor)
{
    if (atvec==atval)
            {
            if (atcolor!=clr)display2(clr),clr=atcolor;
            screen+=atchar;
            }
}

void render()
{
    scrnplayerposx=scrnW;
    scrnplayerposy=scrnH;
    int a, b,x, y;
    for (a=0; a<=scrnH*2+2;a++)
        for (b=0; b<=scrnW*2-2;b++)
        {
            int x=playerPosX+b-scrnW;
            int y=playerPosY+a-scrnH;
            int hitm=hitmap[playerPosY+a-scrnH][playerPosX+b-scrnW];
            if (enemymap[y][x]==1)screenmap[a][b]=3;
            else if (hitm>6)screenmap[a][b]=2;
            else if (hitm>0)screenmap[a][b]=-2;
           else screenmap[a][b]=mainmap[playerPosY+a-scrnH][playerPosX+b-scrnW];
        }
}


void displayland()
{
    render();

    int a, b;
    for (a=0; a<=scrnH*2+2;a++)
    {
        for (b=0; b<=scrnW*2-2;b++)
        {
            if (scrnplayerposy==a&&scrnplayerposx==b&&playerHp>0)
                atchr(0,0,"O",15);
            else
            {

                atchr(screenmap[a][b],0," ",5);//air
                atchr(screenmap[a][b],1,"#",5);//wall
                atchr(screenmap[a][b],2,"*",14);//fire
                atchr(screenmap[a][b],-2,"*",6);//fire2
                atchr(screenmap[a][b],3,"S",2);//fire2

            }


        }
    screen+="\n";
    }

    display2(clr);
}


void genminimap()
{
    int a,b,i,j,a1,b1;
    //border
    for (int i=1;i<=miniH;i++)
        for (int j=1;j<=miniW;j++)
    {
        if (i==1||j==1||i==miniH||j==miniW)minimap[i][j]=1;
    }

    int vlblpathx[10];
    int vlblpathy[10];
    int vlblpathn;


   shipposx=rnd(4,miniH-4);
   shipposy=rnd(4,miniW-4);
   minimap[shipposy][shipposx]=-1;

   int k1=0;
   int kcount=0;

   endposx=shipposx;
   endposy=shipposy;

   i=endposy;
    j=endposx;

   while (k1!=1) //generate initial path
   {

        if (minimap[i][j]==-1)
        {

            vlblpathn=0;
            for (a1=-1;a1<=1;a1++)
            for (b1=-1;b1<=1;b1++)
                if (a1*b1==0&&a1!=b1)
                if (minimap[i+a1][j+b1]==0)
                {
                    for ( a=-1;a<=1;a++)
                    for ( b=-1;b<=1;b++)
                    if (a!=0||b!=0)
                    {
                    if (minimap[i+a+a1][j+b+b1]==-1)kcount++;
                    }
                    if (kcount==1||kcount==0||kcount==2)
                    {
                    vlblpathy[vlblpathn]=a1;
                    vlblpathx[vlblpathn]=b1;
                    vlblpathn++;
                    }
                    kcount=0;
                }

            if (vlblpathn>0)
            {
               vlblpathn=rnd(0,vlblpathn);
               endposx=j+vlblpathx[vlblpathn];
               endposy=i+vlblpathy[vlblpathn];
               minimap[endposy][endposx]=-1;
            i=endposy;
            j=endposx;
            }
            else k1++;
        }
   }

   if (endposy==shipposy && abs(endposx-shipposx)==1)
    {
        minimap[endposy][endposx]=0;
        endposx+=endposx-shipposx;
        minimap[endposy][endposx]=-1;
    }
   else if (endposx==shipposx && abs(endposy-shipposy)==1)
   {
       minimap[endposy][endposx]=0;
       endposy+=endposy-shipposy;
       minimap[endposy][endposx]=-1;
   }

   int k2=0;
   int k3=0;
   for (int i1=1;i1<=miniH;i1++)
        for (int j1=1;j1<=miniW;j1++)
        {
    k1=0;
    if (k3==(miniH+miniW)/10)j1=miniW,i1=miniH;
    if (k2!=0)k3++,
    k2=0;
    i=i1;
    j=j1;
    kcount=0;
   while (k1==0) //generate etc paths
   {
       k1=1;
        if (minimap[i][j]==-1)
        {

            vlblpathn=0;
            for (a1=-1;a1<=1;a1++)
            for (b1=-1;b1<=1;b1++)
                if (a1*b1==0&&a1!=b1)
                if (minimap[i+a1][j+b1]==0)
                {
                    for ( a=-1;a<=1;a++)
                    for ( b=-1;b<=1;b++)
                    if (a!=0||b!=0)
                    {
                    if (minimap[i+a+a1][j+b+b1]==-1)kcount++;
                    }
                    if (kcount==1||kcount==0||kcount==2)
                    {
                    vlblpathy[vlblpathn]=a1;
                    vlblpathx[vlblpathn]=b1;
                    vlblpathn++;
                    }
                    kcount=0;
                }

            if (vlblpathn>0)
            {
                k1=0;
               vlblpathn=rnd(0,vlblpathn);
               minimap[i+vlblpathy[vlblpathn]][j+vlblpathx[vlblpathn]]=-1;
            i=i+vlblpathy[vlblpathn];
            j=j+vlblpathx[vlblpathn];
            k2++;
            }
        }
    }
        }


   for (int i=2;i<=miniH-1;i++)
        for (int j=2;j<=miniW-1;j++)
    {

        if  (minimap[i][j]==0)
        {
            kcount=0;
        for ( a=-1;a<=1;a++)
                    for ( b=-1;b<=1;b++)
                    if (a*b==0&&a!=b)
                    {
                    if (minimap[i+a][j+b]==-1)kcount++;
                    }
                    if (kcount ==1)minimap[i][j]=2;
        }
    }

    for (int i=2;i<=miniH-1;i++)
        for (int j=2;j<=miniW-1;j++)
    {

        if  (minimap[i][j]==2)
        {
            kcount=0;
        for ( a=-1;a<=1;a++)
                    for ( b=-1;b<=1;b++)
                    if (a!=0||b!=0)
                    {
                    if (minimap[i+a][j+b]!=-1)kcount++;
                    }
                    if (kcount ==8)minimap[i][j]=1;
        }
    }

    for (int i=2;i<=miniH-1;i++)
        for (int j=2;j<=miniW-1;j++)
    {

        if  (minimap[i][j]==0)
        {
            minimap[i][j]=1;
        }
    }

    minimap[shipposy][shipposx]=0;
    minimap[endposy][endposx]=0;

     ///minimap test
   for (int i=1;i<=miniH;i++){for (int j=1;j<=miniW;j++){if (i==shipposy&&j==shipposx)cout<<"@";else if (i==endposy&&j==endposx)cout<<"$";else if(minimap[i][j]==-1)cout<<" ";else cout<<minimap[i][j];}cout<<endl;};

   }

void genmainmap()
{
    int msideH=15;
    int msideW=20;
    mainH=miniH*msideH;
    mainW=miniW*msideW;
    int i,j,a,b,k1,kcount;


    for (i=1;i<=mainH;i++)
        for (j=1;j<=mainW;j++)
    {
        if (minimap[i/msideH+1][j/msideW+1]!=1)
        mainmap[i][j]=1;
    }


    k1=0;
    while (k1!=5)
    {
     for (i=1;i<=mainH;i++)
        for (j=1;j<=mainW;j++)
    {
        kcount=0;
        if (mainmap[i][j]==1)
        for ( a=-1;a<=1;a++)
        for ( b=-1;b<=1;b++)
        {
            if (mainmap[i+a][j+b]==0)kcount++;
        }

        if (kcount==5||kcount==4)up[i][j]=1;
    }

    for (i=1;i<=mainH;i++)
            for (j=1;j<=mainW;j++)
            if (up[i][j]==1)mainmap[i][j]=0,up[i][j]=0;


            k1++;
    }

    k1=0;
    while (k1!=5)
    {
     for (i=1;i<=mainH;i++)
        for (j=1;j<=mainW;j++)
    {
        kcount=0;
        if (mainmap[i][j]==0)
        for ( a=-1;a<=1;a++)
        for ( b=-1;b<=1;b++)
        {
            if (mainmap[i+a][j+b]==1)kcount++;
        }

        if (kcount==5||kcount==4)up[i][j]=1;
    }

    for (i=1;i<=mainH;i++)
            for (j=1;j<=mainW;j++)
            if (up[i][j]==1)mainmap[i][j]=1,up[i][j]=0;


            k1++;
    }

    for (i=1;i<=mainH;i++)
       for (j=1;j<=mainW;j++)
            if (mainmap[i][j]==0)mainmap[i][j]=1;
            else mainmap[i][j]=0;

    playerPosX=(shipposx-1)*msideW+msideW/2;
    playerPosY=(shipposy-1)*msideH+msideH/2;
     enemyPosx=(endposx-1)*msideW+msideW/2;
    enemyPosy=(endposy-1)*msideH+msideH/2;

///main map test
   for (i=1;i<=mainH;i++){for (j=1;j<=mainW;j++){if (i==playerPosY&&j==playerPosX)cout<<"o"; else if (mainmap[i][j]==1) cout<< mainmap[i][j]; else cout<<" ";}cout<<endl;}cin>>location;
}



void hitscan(int firedirX,int firedirY)
{
    int i,j,k,a,b,rangecount;
    if (firedirX==0&&firedirY==0)
    {
        for (i=1; i<=mainH;i++)
        for (j=1; j<=mainW;j++)
       if (hitmap[i][j]>0) hitmap[i][j]--;
    }
    else
        {
    if (mainmap[playerPosY+firedirY*2][playerPosX+firedirX*2]==0)
    {
    i=playerPosY+firedirY*2;
    j=playerPosX+firedirX*2;
    k=0;
    rangecount=0;
    while (k!=3&&rangecount<=range*range&&(k!=1||rangecount<=range)&&(k!=2||rangecount<=range*2))
    {
        rangecount++;
        if (k==0)hitmap[i][j]=10;
        else hitmap[i][j]=10;
        i+=firedirY;
        j+=firedirX;
        if (mainmap[i][j]==0);

        else k++;

        if (k==1&&rangecount<=range)
        {

            if(firedirY*firedirX!=0)
            for (a=-1;a<=1;a+=2)
            for (b=-1;b<=1;b+=2)
            {
            if (mainmap[i+a][j+b]==0&&hitmap[i+a][j+b]==0)firedirY=a,firedirX=b;
            }
            else
            for (a=-1;a<=1;a++)
            for (b=-1;b<=1;b++)
            {
            if ((a==0||b==0)&&mainmap[i+a][j+b]==0&&hitmap[i+a][j+b]==0)firedirY=a,firedirX=b;
            }


            k++;
        }
    }
    }

    }
}


void enemyspawn()
{
    enemyHp=3;
    playerHp=3;

}
void enemyai()
{
    int i,j;
    for (i=1;i<=mainH;i++)
        for (j=1;j<=mainW;j++)
        enemymap[i][j]=0;
    if (enemyHp>=0) enemymap[enemyPosy][enemyPosx]=1;
    if (hitmap [enemyPosy][enemyPosx]==10)enemyHp--;
    if (playerHp>=0) enemymap[playerPosY][playerPosX]=1;
    if (hitmap [playerPosY][playerPosX]==10)playerHp--;
}


int main()
{
    cin>>location;
    init();
    genminimap();
    genmainmap();
    enemyspawn();
    while (true)
    {

        if (movcldX>=pmovspdX)
        {
        if( GetAsyncKeyState(0x41))
        {
            if (mainmap[playerPosY][playerPosX-1]<=0)playerPosX--,movcldX=0;
        }
        if( GetAsyncKeyState(0x44))
        {
            if (mainmap[playerPosY][playerPosX+1]<=0)playerPosX++,movcldX=0;
        }

        }

        if (movcldY>=pmovspdY)
        {
        if( GetAsyncKeyState(0x57))
        {
            if (mainmap[playerPosY-1][playerPosX]<=0)playerPosY--,movcldY=0;
        }
        if( GetAsyncKeyState(0x53))
        {
            if (mainmap[playerPosY+1][playerPosX]<=0)playerPosY++,movcldY=0;
        }

        }

        int firedirX=0;
        int firedirY=0;

        if( GetAsyncKeyState(VK_LEFT))
        {
            firedirX+=-1;
        }
        if( GetAsyncKeyState(VK_RIGHT))
        {
            firedirX+=1;
        }
        if( GetAsyncKeyState(VK_UP))
        {
            firedirY+=-1;
        }
        if( GetAsyncKeyState(VK_DOWN))
        {
            firedirY+=1;
        }

        if (firecld>=fireCold&&(firedirY!=0||firedirX!=0))hitscan(firedirX,firedirY),firecld=0;

    enemyai();
    displayland();
    hitscan(0,0);
    if (movcldX<pmovspdX)movcldX++;
    if (movcldY<pmovspdY)movcldY++;
    if (firecld<fireCold)firecld++;
    Sleep(5);
    cout<<enemyPosx<<" "<<enemyPosy<<" "<<enemyHp<<endl;
    cout<<playerPosX<<" "<<playerPosY<<" "<<playerHp;
    display();
    }
}
