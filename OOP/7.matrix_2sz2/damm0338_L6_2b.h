// Domokos Ábel
// 411

#include <iostream>
using namespace std;

class Intervallum {
    int kezdopont;
    int vegpont;

public:
    Intervallum();
    Intervallum(int, int);
    Intervallum operator--(int); // utotag
    Intervallum& operator--(); // elotag
    void kiir();
};

Intervallum::Intervallum()
{
    kezdopont = -10;
    vegpont = 10;
}

Intervallum::Intervallum(int a, int b)
{
    if (a > b)
        throw " Hiba";
    kezdopont = a;
    vegpont = b;
}

void Intervallum::kiir()
{
    cout << "[" << kezdopont << "," << vegpont << "]" << endl;
}

Intervallum Intervallum::operator--(int k)
{ // utotag
    Intervallum uj(kezdopont++, vegpont--);
    return uj;
}

Intervallum& Intervallum::operator--()
{ // elotag
    kezdopont++;
    vegpont--;
    return *this;
}