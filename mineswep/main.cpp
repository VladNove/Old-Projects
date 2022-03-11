#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>


using namespace std;
int m[30][30],posx,posy,up, vis[30][30], running, mark[30][30],p,q,dim,bmb,f;

void display()
{
    system("cls");
    cout <<endl;
    for (int i=1;i<=dim;i++)
    {
        for (int j=1;j<=dim;j++)
        {
            cout<<"    ";
            if (mark[i][j]==1)cout << "X";
            else
            {
            if (vis[i][j]==1)
            {
                if (m[i][j]!=0)
                    cout<< m[i][j];
                else cout << " ";

            }
            else if (vis[i][j]==2) cout<< "O";
            else cout<< "#";
            }
        }
        cout<<endl;
        if (posy==i)
        {
            cout << "    ";
            for (int k=1;k<=posx-1;k++) cout<<"     ";
                cout<<"*"<<endl<<endl;
        }
        else cout<<endl<<endl;
    }
}

int gamover()
{
                for (int i=1;i<=dim;i++)
                {
                    for (int j=1;j<=dim;j++)
                    {
                        if (vis[i][j]==-1)vis [i][j]=2;
                        else vis[i][j]=1;
                    }
                }
                display();
                running--;
                cout << "GAME OVER";
                while (true) if (GetAsyncKeyState(VK_RETURN)) return 0;

}

void chain()
{
    for (int i=1;i<=dim;i++)
        for (int j=1;j<=dim;j++)
        {
                for (p=-1;p<=1;p++)
                for (q=-1;q<=1;q++)
                if (p*q!=0||p+q!=0)
                if (vis[i+p][j+q]==1&&m[i+p][j+q]==0)vis[i][j]=1;
        }
    for (int i=dim;i>=1;i--)
        for (int j=dim;j>=1;j--)
        {
                for (p=-1;p<=1;p++)
                for (q=-1;q<=1;q++)
                if (p*q!=0||p+q!=0)
                if (vis[i+p][j+q]==1&&m[i+p][j+q]==0)vis[i][j]=1;
        }
    for (int i=1;i<=dim;i++)
        for (int j=1;j<=dim;j++)
        {
                for (p=-1;p<=1;p++)
                for (q=-1;q<=1;q++)
                if (p*q!=0||p+q!=0)
                if (vis[i+p][j+q]==1&&m[i+p][j+q]==0)vis[i][j]=1;
        }
}

void dclick()
{
    int t=0;
    for (p=-1;p<=1;p++)
    for (q=-1;q<=1;q++)
    if (p*q!=0||p+q!=0)
    if (mark[posy+p][posx+q]==1)t++;

    if (m[posy][posx]==t)
    for (p=-1;p<=1;p++)
    for (q=-1;q<=1;q++)
    if (p*q!=0||p+q!=0)
    if (mark[posy+p][posx+q]!=1)
    {
    if (vis[posy+p][posx+q]==-1)gamover();
    else vis[posy+p][posx+q]=1;
    }

    chain();

}

int checkwin()
{
    int r=0;
    for (int i=1;i<=dim;i++)
        for (int j=1;j<=dim;j++)
            if (vis[i][j]==-1)
                if (mark[i][j]!=1)
                    r++;

    if (r==0)
    {

        display();
        running++;
        cout << "WIN";
        while (true) if (GetAsyncKeyState(VK_RETURN)) return 0;
    }
    r=0;
    for (int i=1;i<=dim;i++)
        for (int j=1;j<=dim;j++)
            if (vis[i][j]!=0)r++;
    if (r==0)
    {

        display();
        running++;
        cout << "WIN";
        while (true) if (GetAsyncKeyState(VK_RETURN)) return 0;
    }
}

int main()
{
    cout<<"dimensiune: ";
    cin>>dim;
    cout<<endl<<"nr mine: ";
    cin>>bmb;
    srand(time(NULL));
    for (int i=1;i<=bmb;i++)
    {
        p=rand()%dim+1;
        q=rand()%dim+1;
        if (vis[p][q]==-1)i--;
        vis[p][q]=-1;
    }
    posy=1;
    posx=1;
    up++;

    for (int i=1;i<=dim;i++)
        for (int j=1;j<=dim;j++)
            {
                for (p=-1;p<=1;p++)
                for (q=-1;q<=1;q++)
                if (p*q!=0||p+q!=0)
                if (vis[i+p][j+q]==-1)m[i][j]++;
            }

    while(running==0)
    {
        if(GetAsyncKeyState(VK_UP))
        {
            while (GetAsyncKeyState(VK_UP));
            if (posy>1) posy--;
            up++;
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            while (GetAsyncKeyState(VK_DOWN));
            if (posy<dim) posy++;
            up++;
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            while (GetAsyncKeyState(VK_LEFT));
            if (posx>1) posx--;
            up++;
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            while (GetAsyncKeyState(VK_RIGHT));
            if (posx<dim) posx++;
            up++;
        }
        if(GetAsyncKeyState(VK_CONTROL))
        {
            while (GetAsyncKeyState(VK_CONTROL));
            if (vis[posy][posx]!=1 && mark[posy][posx]==0) mark[posy][posx]=1, checkwin();
            else mark[posy][posx]=0;

            up++;
        }

        if(GetAsyncKeyState(VK_RETURN))
        {
            while (GetAsyncKeyState(VK_RETURN));
            if (mark[posy][posx]!=1&&f!=0)
            {
            if (vis[posy][posx]!=-1)
            {
                if (vis[posy][posx]==1)dclick();
                 vis[posy][posx]=1;
                 if (m[posy][posx]==0)chain();
            }

            if (vis[posy][posx]==-1)gamover();
            }
            f=1;
            up++;
        }
        if (up!=0)
        {
            up=0;
            display();
        }
    }
}
