#include <cstring>
#include <iostream>
using namespace std;


class Allat { // absztrakt osztaly(van benne legalabb egy tiszta virtualis fuggveny)
    // nem tudunk peldanyositani belole
protected:
    char* faj;
    float tomeg;

public:
    Allat(char* faj, float tomeg)
    {
        this->faj = new char[strlen(faj) + 1];
        strcpy(this->faj, faj);
        this->tomeg = tomeg;
        cout << "Allat osztaly konstruktora \n";
    };
    ~Allat()
    {
        delete[] faj;
        cout << "Allat osztaly destruktora \n";
    }
    virtual void taplalkozik() = 0;
    virtual void kiir()
    {
        cout << faj << endl;
        cout << tomeg << endl;
    };
    // tiszta virtualis fuggveny = csak deklaraljuk de nem definialjuk
};

class Madar : public Allat {
protected:
    float szarny_tav;

public:
    Madar(char* szoveg, float tomeg, float szarny_tav)
        : Allat(szoveg, tomeg)
    {
        this->szarny_tav = szarny_tav;
    }

    void taplalkozik()
    {
        cout << "A madarak magvakat esznek. Taplalkozik.";
    }

    void kiir()
    {
        Allat::kiir();
        cout << szarny_tav << endl;
    }
};

class Kutya : public Allat {
protected:
    bool hazi;

public:
    Kutya(char* szoveg, int tomeg, bool hazi)
        : Allat(szoveg, tomeg)
    {
        this->hazi = hazi;
    }
    ~Kutya()
    {
        cout << "Kutya osztaly destruktora\n";
    }
    void taplalkozik()
    {
        cout << "A kutya ragja a csontot." << endl;
    }

    void kiir()
    {
        Allat::kiir();
        if (!hazi)
            cout << "nem";
        cout << "hazi" << endl;
    }
};

main()
{
    char f2[] = "sas";
    // Madar madiar(f2, 30, 10);
    // madiar.kiir();

    char f3[] = "Bison";
    Kutya misi(f3, 45, 2);
    misi.kiir();
    misi.taplalkozik();

    // Allat* allatok[] = { new Madar(f2, 30, 10), new Kutya(f3, 45, 2) };
    // allatok[0]->kiir();
    // delete allatok[0];
    return 0;
}