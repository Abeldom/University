#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
 
using namespace std;
 
void kiiratas(char latok[][50],int x,int y){
    cout<<" ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    for(int i=0;i<y;i++){
        if(i>10){
           cout<<" "<<i;
        }else{
              cout<<"  "<<i;
            }
        }
 
    cout<<endl;
 
    for(int i=0;i<x;i++){
        if (i>=10){
            cout<<i;
        }else{
            cout<<" "<<i;
        }
 
        for(int j=0;j<y;j++){
                if(latok[i][j]=='*'){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                    cout<<" "<<latok[i][j]<<" ";
                }else{
                    if(latok[i][j]>=48 && latok[i][j]<57){
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                    }else{
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    }
                    cout<<" "<<latok[i][j]<<" ";
                }
        }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout<<i;
        cout<<endl;
 
    }
 
    cout<<" ";
    for(int i=0;i<y;i++){
        if(i>10){
           cout<<" "<<i;
        }else{
              cout<<"  "<<i;
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout<<endl;
    cout<<endl;
}
 
 
 
//egy bomba korul hany bomba van
int vizsg1(char avan[][50],int m,int k,int x,int y,int & nb){
            int ex=m-1;//ex=ettol,ax=addig
            int ax=m+1;
            int ey=k-1;
            int ay=k+1;
            if(ex<0){
                ex=0;
            }
            if(ax>x-1){
                ax=x-1;
            }
            if(ey<0){
                ey=0;
            }
            if(ay>y-1){
                ay=y-1;
            }
            int f=0;
            for(int i=ex;i<=ax;i++){
                   for(int j=ey;j<=ay;j++){
                        if(avan[i][j]=='*'){
                           f++;
                        }
                        else{
                           nb++;
                        }
                        }
            }
 
        return f-1;
}
 
//a helyzet koruli- helyzetek koruli bombak szamanak a vizsgalata
int vizsg2(char avan[][50],int m,int k,int x,int  y,int &nb){
            int ex=m-1;//ex=ettol,ax=addig
            int ax=m+1;
            int ey=k-1;
            int ay=k+1;
            if(ex<0){
                ex=0;
            }
            if(ax>x-1){
                ax=x-1;
            }
            if(ey<0){
                ey=0;
            }
            if(ay>y-1){
                ay=y-1;
            }
 
            for(int i=ex;i<=ax;i++){
                for(int j=ey;j<=ay;j++){
                        int h=vizsg1(avan,i,j,x,y,nb);
                        if(avan[i][j]=='*' ){
                            if(h>7||nb==0){
                              return 8;
                            }
                        }else if(avan[i][j]=='0'){
                            if(h+1>7){
                              return 8;
                            }
                        }
                        nb=0;
                }
            }
 
  return 0;
}
 
 
 
int rekurziv(char latok[][50],char avan[][50],int m,int k,int x,int y){
     int ex=m-1;//ex=ettol,ax=addig
     int ax=m+1;
     int ey=k-1;
     int ay=k+1;
     int szaml=0;
     if(ex<0){
         ex=0;
     }
     if(ax>x-1){
         ax=x-1;
     }
     if(ey<0){
         ey=0;
     }
     if(ay>y-1){
         ay=y-1;
     }
    for(int i=ex;i<=ax;i++){
            for(int j=ey;j<=ay;j++){
                if(i==m && j==k){
               }else if(avan[i][j]=='0'&&latok[i][j]!='0'){
                   latok[i][j]='0';
                   szaml=szaml+1+rekurziv(latok,avan,i,j,x,y);
               }else if(latok[i][j]!=avan[i][j]){
                latok[i][j]=avan[i][j];
                szaml++;
               }
            }
    }
    return szaml;
}
 
 
int main()
{
    //adatok bekerese
    int n;
    cout << "Jatekmod:easy   (n=1)" << endl ;
    cout << "         medium (n=2)" << endl ;
    cout << "         hard   (n=3)" << endl ;
    cout << "n=" ;
    cin >> n;
 
 
 
    int x,y;
    cout<< "Palya merete(x*y)(x-sor,y-oszlop):"<<endl;
    cout<< "  x=";
    cin>>x;
    cout<< "  y=";
    cin>>y;
 
 
 
    int bsz;
    if(n==1){
        bsz=x*y*20/100;
    }else if(n==2){
        bsz=x*y*30/100;
    }else{
        bsz=x*y*40/100;
    }
 
 
 
    char latok[x][50];//amit en latok a kepernyon
    char avan[x][50];//ahogy van
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            latok[i][j]='?';
            avan[i][j]=48;
        }
    }
 
 
 
 
    system("cls");//torli a kepernyot
    cout<<bsz<<"bomba"<<endl;
    kiiratas(latok,x,y);
    cout<<endl;
 
 
 
    //bombak elhelyezese
 
    srand(time(NULL));
    int r;
    int bomb[bsz][2];
    int k;
    int m;
    for(int i=0;i<bsz;i++){
        r=rand()%(x*y)+1;
        if(r%y==0){
            k=y-1;
            m=r/y-1;
        }else{
            m=r/y;
            k=r%y-1;
        }
        if(avan[m][k]=='*'){
            i--;
        }else{
          avan[m][k]='*';
          bomb[i][0]=m;
          bomb[i][1]=k;
        }
    }
 
//bombak ujravizsgalasa
bool logic=true;
int nb=0;
    for(int i=0;i<bsz;i++){
            if(logic){
            m=bomb[i][0];
            k=bomb[i][1];
            }
            nb=0;
                if (vizsg1(avan,m,k,x,y,nb)>7||vizsg2(avan,m,k,x,y,nb)>7){
 
                    logic=false;
                    avan[m][k]=48;
                    do{
                    r=rand()%(x*y)+1;
                      if(r%y==0){
                         k=y-1;
                         m=r/y-1;
                      }else{
                         k=r%y-1;
                         m=r/y;
                      }
                    }while(avan[m][k]=='*');
                    avan[m][k]='*';
                    i--;
 
               }else{
                   logic=true;
                     bomb[i][0]=m;
                     bomb[i][1]=k;
 
               }
    }
 
    //avan--a bomba koruli helyeknek erteket adok
    int ex,ax,ey,ay;
    for(int i=0;i<bsz;i++){
         m=bomb[i][0];
         k=bomb[i][1];
 
            ex=m-1;//ex=ettol,ax=addig
            ax=m+1;
            ey=k-1;
            ay=k+1;
            if(ex<0){
                ex=0;
            }
            if(ax>x-1){
                ax=x-1;
            }
            if(ey<0){
                ey=0;
            }
            if(ay>y-1){
                ay=y-1;
            }
 
             for(int i=ex;i<=ax;i++){
                for(int j=ey;j<=ay;j++){
                        if(avan[i][j]!='*'){
                            avan[i][j]=avan[i][j]+1;
                        }
                }
             }
    }
/*
    kiiratas(avan,x,y);
*/
 
    int sor,oszlop,szaml=0,kell=(x*y)-bsz;
    int S=x*y;
    do{
        cout<<"sor:";
        cin>>sor;
        cout<<"oszlop:";
        cin>>oszlop;
        system("cls");
        if(avan[sor][oszlop]=='*'){
            for(int i=0;i<bsz;i++){
            int ind1=bomb[i][0];
            int ind2=bomb[i][1];
            latok[ind1][ind2]='*';
            }
        }else{
            if(avan[sor][oszlop]=='0'){
               szaml=szaml+rekurziv(latok,avan,sor,oszlop,x,y);
 
           }else{
               latok[sor][oszlop]=avan[sor][oszlop];
               szaml++;
           }
           kiiratas(latok,x,y);
           if(szaml!=kell){
                cout<<bsz<<" bomba van osszesen a(z) "<<S<<" helybol"<<endl;
           cout<<kell-szaml<<" helyet kell meg kiutni,te eddig "<<szaml<<" helyet utottel ki"<<endl;
           cout<<endl;
           }
        }
    }while(avan[sor][oszlop]!='*' && szaml!=kell);
 
    if(avan[sor][oszlop]=='*'){
            kiiratas(latok,x,y);
            cout<<"oopsz,rosszul szamoltad ki/vagy rosszul tippeltel!"<<endl;
    }else{
    cout<<"Nyertel"<<endl;
    }
 
    return 0;
}