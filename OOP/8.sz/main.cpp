#include <iostream>
using namespace std;

class Tomeg {
    int g;
    int mg;

public:
    Tomeg(); // 0g 1 mg
    Tomeg(int, int); // ellenorzes ne legyenek negativak
    explicit Tomeg(int);
    operator int();

    void kiir();
    Tomeg operator+(const Tomeg& t);
    Tomeg& operator+=(const Tomeg& t);
    Tomeg operator++(int);
    Tomeg& operator++();
    Tomeg operator+(int);
    // int operator+(int);
    // Tomeg operator<<();
};

Tomeg::operator int()
{
    return 1000 * g + mg;
}

Tomeg::Tomeg()
{
    g = 0;
    mg = 1;
}

Tomeg::Tomeg(int _mg)
{
    mg = _mg % 1000;
    g += mg / 1000;
}

Tomeg::Tomeg(int gramm, int mili_gramm)
{
    if (gramm < 0 || mili_gramm < 0) {
        throw "Bad input.";
    } else {
        g = gramm + mili_gramm / 1000;
        mg = mili_gramm % 1000;
    }
}

void Tomeg::kiir()
{
    cout << g << "g " << mg << "mg \n";
}

Tomeg Tomeg::operator+(const Tomeg& t)
{
    Tomeg test(g + t.g, mg + t.mg);
    return test;
}

Tomeg& Tomeg::operator+=(const Tomeg& t)
{
    return *this = *this + t;
}

Tomeg Tomeg::operator++(int k)//post++
{
    Tomeg masolat(g, mg);
    *this = *this + masolat;
    return masolat;
}

Tomeg& Tomeg::operator++()//++pre
{
    Tomeg test(1, 1);
    *this = *this + test;
    return *this;
}

Tomeg Tomeg::operator+(int adalek)
{
    Tomeg test(adalek / 1000, adalek % 1000);
    return *this + test;
}

// int Tomeg::operator+(int adalek)
// {
//     return g*1000+mg+adalek;
// }

int main()
{
    try {
        Tomeg laptop(1, 1100);
        laptop.kiir();

        Tomeg bohoc(80, 2400);
        bohoc.kiir();

        Tomeg legy(0, 1001);
        // legy.kiir();

        (legy + 999).kiir();
        (legy + 1001).kiir();
        cout << legy + 999;

    } catch (const char* hibauzenet) {
        cout << hibauzenet << endl;
    }
    return 0;
}