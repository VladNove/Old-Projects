#include <iostream>

using namespace std;

int t[100][100][100],tn;

int main()
{
    cin>>tn;
    t[1][1][1]=1;

    for (int kn=1;kn<=tn;kn++)
    {
        for (int x=1;x<=kn+1;x++)
            for (int y=1;y<=kn+1;y++)
                for (int z=1;z<=kn+1;z++)
                {
                    if (((x-1)+(y-1)+(z-1))==kn&&t[x][y][z]==0)
                        t[x][y][z]=t[x-1][y][z]+t[x][y-1][z]+t[x][y][z-1];
                }
    }



    for (int x=1;x<=tn+1;x++)
    {
            for (int y=1;y<=tn+1;y++)
            {
                for (int z=1;z<=tn+1;z++)
                    cout <<  t[x][y][z] << " ";
                cout<<"\n";
            }
            cout<<"\n";
    }

    cout<<endl<<endl;

    for (int x=1;x<=tn+1;x++)
    {
            for (int y=1;y<=tn+1;y++)
            {
                for (int z=1;z<=tn+1;z++)
                    {
                        if (((x-1)+(y-1)+(z-1))==tn)
                        {
                            if (t[x][y][z]>1) cout << t[x][y][z] ;
                            if (z-1>0) {cout << "a";if (z-1>1) cout << "^" << z-1;} ;
                            if (y-1>0) {cout << "b";if (y-1>1) cout << "^" << y-1;} ;
                            if (x-1>0) {cout << "c";if (x-1>1) cout << "^" << x-1;} ;
                            if (x!=tn+1) cout<<" + ";
                        }
                    }
            }

    }
}
