#include <iostream>

using namespace std; 
 
void novel(int* x){
  (*x)++;
}

int main(){ 
  int n=100;
  int kihuzott_feher=0,kihuzott_fekete=0;
  for(int i=0;i<n;i++){
    int szam=rand()%3;
    if(szam==0){
      novel(&kihuzott_feher);
    }else{
      novel(&kihuzott_fekete);
    }
  }
  cout<<"kihuzott feketek szama: "<<kihuzott_fekete<<endl;
  cout<<"         feherek szama: "<<kihuzott_feher <<endl;

    

 return 0;
}