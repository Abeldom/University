#include <cstring>
#include <iostream>
using namespace std;

class Szemely
{
  protected:
    int eletkor;
    char nev[20];

  public:
    Szemely();
    Szemely(int, const char *);
    void taplalkozik();
    void alszik();
    void kiir();
};

class Diak : public virtual Szemely
{
  protected:
    double atlag;

  public:
    Diak();
    Diak(int eletkor, const char *nev, double atlag);
    void tanul();
    void kiir();
};

class Kulfoldi : public virtual Szemely
{
  protected:
    char orszag[20];

  public:
    Kulfoldi(int, const char *nev, const char *orszag);
    void utazik();
    void kiir();
};

class Erasmusos : public Kulfoldi, public Diak
{
  protected:
    int kulfold_honapok;

  public:
    Erasmusos(int eletkor, const char *nev, const char *orszag, double atlag, int honapok);
    void kiir();
};

Szemely::Szemely()
{
    eletkor = 0;
    strcpy(nev, "");
}

Szemely::Szemely(int eletkor, const char *nev)
{
    this->eletkor = eletkor;
    strcpy(this->nev, nev);
    cout << "szemely konstruktor\n";
}

void Szemely::taplalkozik()
{
    cout << "a szemely taplalkozik." << endl;
}

void Szemely::alszik()
{
    cout << "a szemely alszik" << endl;
}

void Szemely::kiir()
{
    cout << "Nev:" << nev << endl;
    cout << "Eletkor:" << eletkor << endl;
}

Diak::Diak()
{
    atlag = 0;
}

Diak::Diak(int e, const char *nev, double atlag) : Szemely(e, nev)
{
    cout << "diak osztalykonstruktora." << endl;
    this->atlag = atlag;
}

void Diak::tanul()
{
    cout << "A diak tanul" << endl;
}

void Diak::kiir()
{
    cout << "Nev:" << nev << endl;
    cout << "Eletkor:" << eletkor << endl;
    cout << "Atlag:" << atlag << endl;
}

Kulfoldi::Kulfoldi(int eletkor, const char *nev, const char *orszag) : Szemely(eletkor, nev)
{
    cout << "kulfoldi konstruktor." << endl;
    strcpy(this->orszag, orszag);
}

void Kulfoldi::utazik()
{
    cout << "A kulfoldi utazik." << endl;
}

void Kulfoldi::kiir()
{
    cout << "Nev:" << nev << endl;
    cout << "Eletkor:" << eletkor << endl;
    cout << "Orszag:" << orszag << endl;
}

Erasmusos::Erasmusos(int eletkor, const char *nev, const char *orszag, double atlag, int kulfold_honapok)
    : Szemely(eletkor, nev), Diak(eletkor, nev, atlag), Kulfoldi(eletkor, nev, orszag)
{
    cout << "Erasmusos konstruktor." << endl;
    this->kulfold_honapok = kulfold_honapok;
}

void Erasmusos::kiir()
{
    cout << "Nev:" << Diak::nev << endl;
    cout << "Eletkor:" << Diak::eletkor << endl;
    cout << "Atlag:" << atlag << endl;
    cout << "Orszag:" << orszag << endl;
    cout << "Kulfoldi honapok:" << kulfold_honapok << endl;
}

int main()
{
    Szemely ember1(19, "Dani");
    ember1.alszik();
    ember1.taplalkozik();

    Diak x(19, "Misi", 8.50);
    x.kiir();
    x.tanul();

    Kulfoldi k(19, "Dani", "Erdely");
    k.kiir();
    k.utazik();

    cout << endl;
    Erasmusos e(19, "Dani", "Erdely", 8.9, 4);
    e.kiir();

    return 0;
}