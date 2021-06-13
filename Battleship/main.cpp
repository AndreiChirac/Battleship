#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;
char m[10][10],cp[10][10],ca[10][10],poz='Q';
int v[100],ls=-1,ld=-1;
int k,x,y,cnt=0,cnto=0,cntboom=0,okjucator=1,ok=1;
void afisare(char m[10][10])
{
    cout<<" ";
    for(int i=0; i<10; i++)
        cout<<" "<< i;
    cout<<endl;
    for(int i=0; i<10; i++)
    {
        cout<<i;
        for(int j=0; j<10; j++)
            cout<<" "<<m[i][j];
        cout<<endl;
    }
}

void afisarecp(char cp[10][10])
{
    cout<<" ";
    for(int i=0; i<10; i++)
        cout<<" "<< i;
    cout<<endl;
    for(int i=0; i<10; i++)
    {
        cout<<i;
        for(int j=0; j<10; j++)
            cout<<" "<<cp[i][j];
        cout<<endl;
    }
}

void afisareca(char ca[10][10])
{
    cout<<" ";
    for(int i=0; i<10; i++)
        cout<<" "<< i;
    cout<<endl;
    for(int i=0; i<10; i++)
    {
        cout<<i;
        for(int j=0; j<10; j++)
            cout<<" "<<ca[i][j];
        cout<<endl;
    }
}

void nave(int k ,char m[10][10])
{

    int a,b,c,d;
    cout<<"Coordonatele navei de dimensiune "<<k<<" sunt de __ la pana la __:";
    cin>>a>>b;
    cin>>c>>d;
    int ok=0;
    while(ok==0)
    {
        ok=1;
        while(c-a==k-1 && d!=b || d-b==k-1 && a!=c || d==b && c-a!=k-1 || a==c && d-b!=k-1 || a!=c && b!=d )
        {
            cout<<"IMPOSIBIL"<<endl;
            cin>>a>>b;
            cin>>c>>d;
        }
        for(int i=a; i<=c; i++)
        {
            for(int j=b; j<=d; j++)
                if(m[i][j]=='Z')
                {
                    ok=0;
                    j=d;
                    i=c;
                    cout<<"Navele se suprapun"<<endl;
                    cin>>a>>b;
                    cin>>c>>d;
                }
        }
    }


    for(int i=a; i<=c; i++)
    {
        for(int j=b; j<=d; j++)
            m[i][j]='Z';
    }
}
void init( char m[10][10])
{
    for(int i=0; i<10; i++)
        for(int j=0; j<10; j++)
            m[i][j]='~';
}
void initca( char ca[10][10])
{
    for(int i=0; i<10; i++)
        for(int j=0; j<10; j++)
            ca[i][j]='~';
}
void initcp( char cp[10][10])
{
    for(int i=0; i<10; i++)
        for(int j=0; j<10; j++)
            cp[i][j]='~';
}


void atac( char cp[10][10],char ca[10][10])
{
    //afisare(ca);
    cout<<"Coordonatele punctului in care vei lovi sunt _ _" ;
    int x,y;
    cin>>x>>y;
    if(cp[x][y]=='~')
    {
        cout<<"Mai incearca tura viitoare ! ";
        cout<<endl;
        cp[x][y]='O';
        ca[x][y]='O';
        afisare(ca);
        okjucator=0;

    }
    else if(cp[x][y]=='O')
    {
        cout<<"Aceasta pozitie a mai fost lovita !";
        cout<<endl;
        cout<<"Reintrodu coordonatele !";
        //cin>>x>>y;
     okjucator=1;
    }
    else if (cp[x][y]=='Z')
    {
        cout<<"Tocmai ai lovit o nava !";
        cout<<endl;
        cp[x][y]='X';
        ca[x][y]='X';
        cntboom++;
        afisare(ca);
        cout<<"Alege coordonatele urmatoarei tinte!";
        cout<<endl;
        //cin>>x>>y;
        okjucator=1;

    }
}
void strategie(char m[10][10])
{
    if(cnto<96)
    {
        if(ld==-1 || ls>ld)//ld=-1 -> inceput; ls>ld -> coada finalizata
        {
           Sleep(500);
           srand(time(0));
            x=rand()%10;
            y=rand()/10%10;
            ls=-1;
            ld=-1;
          //  cout<<x<<y;
            //cin>>x>>y;
        }
        else//mai am elemente in coada
        {
            ls++;
            x=v[ls]/10;
            y=v[ls]%10;
           /*  cout<<endl;
        for(int i=ls;i<=ld;i++)
            cout<<v[i]<" ";
        cout<<endl;
        cout<<x<<y<<endl;*/
        }//aici se incheie alegerea pozitiei de tragere
        if(m[x][y]=='Z'|| m[x][y]=='X')
        {
            if(m[x][y]=='Z')
            {
                m[x][y]='X';
                ld++;
                v[ld]=x*10+y;
                cnt++;
            }
            while(ok==1 && ls<=ld)//trebuie vazut cum revine la pozitia ramasa - rezolvat
            {
                if(x>0 && m[x-1][y]!='X' && m[x-1][y]!='O')
                {
                    if(m[x-1][y]=='Z')
                    {
                        m[x-1][y]='X';
                        ld++;
                        v[ld]=(x-1)*10+y;
                        cnt++;
                    }
                    else if(m[x-1][y]=='~')
                    {
                        m[x-1][y]='O';
                        cnto++;
                        ok=0;
                    }
                    poz='N';
                }
                if(ok!=0) //nu pot sa merg in nord sau am fost deja
                {
                    if(y<9 && m[x][y+1]!='X' && m[x][y+1]!='O')
                        if(m[x][y+1]=='Z')
                        {
                            m[x][y+1]='X';
                            ld++;
                            v[ld]=(x)*10+y+1;
                            cnt++;
                        }
                        else if (m[x][y+1]=='~')
                        {
                            m[x][y+1]='O';
                            cnto++;
                            ok=0;
                        }
                    poz='E';
                }
                if(ok==1)// nu pot sa mai merg nici in est sau am fost deja
                    if(x<9 && m[x+1][y]!='X' && m[x+1][y]!='O')
                    {
                        if(m[x+1][y]=='Z')
                        {
                            m[x+1][y]='X';
                            ld++;
                            v[ld]=(x+1)*10+y;
                            cnt++;
                        }
                        else if(m[x+1][y]=='~')
                        {
                            m[x+1][y]='O' ;
                            cnto++;
                            ok=0;
                        }
                    poz='S';
                    }
                if(ok==1) // nu pot sa mai merg nici in sud sau am fost deja
                    if(y>0 && m[x][y-1]!='X' && m[x][y-1]!='O')
                    {
                        if(m[x][y-1]=='Z')
                        {
                            m[x][y-1]='X';
                            ld++;
                            v[ld]=x*10+y-1;
                            cnt++;
                        }
                        else if(m[x][y-1]=='~')
                        {
                            m[x][y-1]='O';
                            cnto++;
                            ok=0;
                        }
                        poz='W';
                    }
                    if(ok==1)//am terminat vecinii lui[x][y] si ma mut in coada                 {
                    {
                        ls++;
                        x=v[ls]/10;
                        y=v[ls]%10;
                    }
            }
        }
        else if(m[x][y]=='~')
        {
            m[x][y]='O';
            cnto++;
            ok=0;
        }

       /* {
            ls=-1;
            ld=-1;
        }
*/
    }
    else
        cout<<"TABLA INCHEIATA";

}
void strategieasezare(char cp[10][10])
{
int ok=1,a,b,c,cnt3=1;
k=2;
srand(time(0));
while(k<=5)// Sa imi execute codul pana cand ramane vara nave
{
ok=1;
while(ok==1)//Am ales ok1 ca un semafor care sa mi urmareasca daca poztionarea e corect pusa si nu se interseteaza cu alta nava sau iese din tabla
{

a=rand()%10; // cordonata x de unde va incepe
b=rand()/10%10;// cordinata y de unde va incepe
c=rand()/100%10; // un numar in urma caruia sa stabilesc in ce directie ( N E S V) se va pozitiona nava

//Initial am luat cazurile colturilor particular pana mi am dat seama ca se poate rezolva totul intr- o singura bucata
/*if(a==0 && b==0)
    {
        if(c%2==0)
     {
      for(int i=0;i<k;i++)
       {
        if(m[a][b+i]=='Z')
         ok=0;
       }
      for(int i=0;i<k;i++)
      m[a][b+i]='Z';
     }
    else
      {for(int i=0;i<k;i++)
       {
        if(m[a+i][b]=='Z')
         ok=0;
       }
      for(int i=0;i<k;i++)
      m[a+i][b]='Z';
      }
    }
else if (a==0 && b==9)
       {
        if(c%2==0)
        {
         for(int i=0;i<k;i++)
          {if(m[a][b-i]=='Z')
           ok=0;
          }
           for(int i=0;i<k;i++)
           m[a][b-i]='Z';
        }
       else
        {
        for(int i=0;i<k;i++)
          {
            if(m[a+i][b]=='Z')
            ok=0;
          }
        for(int i=0;i<k;i++)
            m[a+i][b]='Z';
        }
       }
else if  (a==9 && b==0 )
        {
        if(c%2==0)
          {for(int i=0;i<k;i++)
           {
            if(m[a][b+i]=='Z')
              ok=0;

           }
           for(int i=0;i<k;i++)
            m[a][b+i]='Z';
          }
         else
            {
            for(int i=0;i<k;i++)
             {
                 if(m[a-i][b]=='Z')
                ok=0;
             }
            for(int i=0;i<k;i++)
             m[a-i][b]='Z';
            }
        }
else if   (a==9 && b==9)
           {
            if(c%2==0)
            {
            for(int i=0;i<k;i++)
              {
                if(m[a-i][b]=='Z')
               ok=0;
              }
             for(int i=0;i<k;i++)
              m[a-i][b]='Z';
            }
           else
            {
            for(int i=0;i<k;i++)
             {
            if(m[a][b-i]=='Z')
              ok=0;
             }
            for(int i=0;i<k;i++)
            m[a][b-i]='Z';
            }
           }
*/

   //Aici in urma selectiei lui c va incepe pozitionara
         if(c>=0 && c<3)//pentru valorile lui c aflate intre 0 si 3 va pozitiona nava pe directia NORD
          {
         if(a-k<0)//Se testeaza daca este posibila pozitionarea spre NORD raportata la nimensiunile navei
            ok=0;
         else//Daca trece de testul de depasire a tablei vom testa daca este posibila pozitionarea in ceea ce priveste suprapunerea navelor
            {
         for(int i=0;i<k;i++)
           {
            if(cp[a-i][b]=='Z' )
              ok=0;
           }
         if(ok==1)// Aici are loc pozitionarea efectiva
         {
             for(int i=0;i<k;i++)
              cp[a-i][b]='Z';
           }
          }
          }
       else if(c>=3 && c<5)//pentru valorile lui c aflate intre 3 si 5 va pozitiona nava pe directia Est
            {
          if(b+k>9)//Se testeaza daca este posibila pozitionarea spre Est raportata la nimensiunile navei
               ok=0;
          else//Daca trece de testul de depasire a tablei vom testa daca este posibila pozitionarea in ceea ce priveste suprapunerea navelor
            {
          for(int i=0;i<k;i++)
           {
            if(cp[a][b+i]=='Z')
              ok=0;
           }
           if(ok==1)//Aici are loc pozitionarea efectiva
           {
           for(int i=0;i<k;i++)
           cp[a][b+i]='Z';
                  }
           }
            }
         else if(c>=5 && c<8)//pentru valorile lui c aflate intre 5 si 8 va pozitiona nava pe directia Sud
             {
             if(a+k>9)//Se testeaza daca este posibila pozitionarea spre Sud raportata la nimensiunile navei
                    ok=0;
             else////Daca trece de testul de depasire a tablei vom testa daca este posibila pozitionarea in ceea ce priveste suprapunerea navelor
                {
        for(int i=0;i<k;i++)
           {
            if(cp[a+i][b]=='Z')
              ok=0;
           }
       if(ok==1)//Aici are loc pozitionare efectiva
       {
           for(int i=0;i<k;i++)
              cp[a+i][b]='Z';
       }

           }
             }
         else // Pentru valorile ramase navele se vor pozitiona spre Vest
            {
           if(b-k<0)//se testeaza posibilitatea de a pune nava fara sa nepaseasca marginea
                ok=0;
           else// se testeaza daca pe directia aleasa nu exista o nava cu care sa se intersecteze
            {
                for(int i=0;i<k;i++)
           {
            if(cp[a][b-i]=='Z')
              ok=0;
           }
           if(ok==1)//Are loc pozitionarea
            for(int i=0;i<k;i++)
              cp[a][b-i]='Z';
           }

           }


if(ok==1)//daca acest indice mi a ramas 1 inseamna ca am un caz favorabil asa ca pot pozitiona nava cu un indice mai mare
{
if(k!=3)// pentru ca trebuie sa fie doua nave de 3 am ales ca pentru orice k inafara de trei k-ul sa creasca
    {k++;
     ok=0;
    }
else
 {
  if(cnt3==2)//am ales cnt3 care sa imi inumere de cate ori au fost pozitionate nave de dimensiune 3
    {k++;
     ok=0;
    }
  else
 {
  cnt3++;
  k=3;
  ok=0;
  }
}

}

}
}
cout<<"Calculatorul si-a pozitionat navele !"<<endl;
}


int main()
{

    init(m);
    initcp(cp);
    initca(ca);
    strategieasezare(cp);
    afisare(m);
    for(int k=2; k<=5; k++)
    {
        nave(k,m);
         afisare(m);
        if(k==3)
        {
            nave(k,m);
            afisare(m);
        }
    }
    afisareca(ca);
    while( cntboom<17 && cnt<17 )
    {
        atac(cp,ca);
         if(okjucator==0)
         {
            while(ok!=0)
        {
        strategie(m);
        afisare(m);
        }
         ok=1;
         afisareca(ca);
         }
    }
  if(cntboom==17)
    cout<<"Ai invins calculatorul !";
  else if(cnt==17)
    cout<<"Toate navele tale au fost distruse !";
    return 0;

}
