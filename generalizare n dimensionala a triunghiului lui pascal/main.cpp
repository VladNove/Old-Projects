#include <iostream>

using namespace std;

int t[100000000],tn,dim,vd[100];

void sv(int n, int i)
{
    if (i<=dim+1)
    {
    if (vd[i]<n+1)vd[i]++;
    else vd[i]=1, sv (n,i+1);
    }
}

int pow(int x, int p) {
  if (p == 0) return 1;
  if (p == 1) return x;
  return x * pow(x, p-1);
}

int red()
{
    int poi=0;
    for (int i=1;i<=dim;i++)poi+=vd[i]*pow(tn+2,i-1);
    return t[poi];
}
int redprec()
{
    int rez=0;
    for (int i=1;i<=dim;i++)
    {
        vd[i]--;
        rez+=red();
        vd[i]++;
    }
    return rez;
}

void wri (int x)
{
    int poi=0;
    for (int i=1;i<=dim;i++)poi+=vd[i]*pow(tn+2,i-1);
    t[poi]=x;
}

int main()
{
    cin>>dim >> tn;
    //tn++;
    for (int i=1;i<=dim;i++)vd[i]=1;
    wri(1);


    for (int kn=1;kn<=tn;kn++)
    {
        for (int i=1;i<=dim+1;i++)vd[i]=1;

        while (vd[dim+1]==1)
        {
            sv(tn,1);
            int suma=0;
            for (int i=1;i<=dim;i++)suma+=vd[i];
            if (suma==kn+dim&&red()==0)wri(redprec());
        }
    }




 for (int i=1;i<=dim+1;i++)vd[i]=1;

 //cout<<endl<<endl;

 //while (vd[dim+1]==1) sv(tn,1), cout <<red();

 cout<<endl<<endl;


    for (int i=1;i<=dim+1;i++)vd[i]=1;
    while (vd[dim+1]==1)
        {
            sv(tn,1);
            int suma=0;
            for (int i=1;i<=dim;i++)suma+=vd[i];
            if (suma==tn+dim)
            {
                if (red()>1)cout<< red();
                for (int i=1;i<=dim;i++)
                {
                if (vd[i]-1>0)
                    {
                        cout << char('a'-1+i);
                        if (vd[i]-1>1)cout<<"^"<<vd[i]-1;
                    }
                }
               if(vd[dim]!=0) cout << " ";
            }
        }

 cout<<endl<<endl;



}
