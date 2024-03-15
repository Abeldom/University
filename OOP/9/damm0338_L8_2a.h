// Domokos Abel
// 411

#include <iostream>
using namespace std;

// 1111111111
class Tomeg_g
{
    int kg, dkg, g;
    double maradek;

  public:
    Tomeg_g(int kg = 0, int dkg = 0, int g = 0, double marad = 0.0);
    // Tomeg_g(Tomeg_d ebbol);
    void kiir_g();
};

// 2222222222
class Tomeg_d
{
    int font, uncia, dram;

  public:
    Tomeg_d(int font = 0, int uncia = 0, int dram = 0);
    int ossz_dram();
    void kiir_d();
    operator Tomeg_g();
};

//-------------------------------------------------------------------
//                GRAMM         GRAMM            GRAMM
//-------------------------------------------------------------------

Tomeg_g::Tomeg_g(int kg, int dkg, int g, double marad)
{
    int ossz_gramm = kg * 1000 + dkg * 10 + g + marad;

    this->kg = ossz_gramm / 1000;
    ossz_gramm %= 1000;
    this->dkg = ossz_gramm / 10;
    ossz_gramm %= 10;
    this->g = ossz_gramm;

    this->maradek = marad;
}

/* Tomeg_g::Tomeg_g(Tomeg_d test)
{
    maradek = 1.77 * test.ossz_dram();
    int ossz_gramm = (int)maradek;
    maradek -= ossz_gramm;
    Tomeg_g ujtest(0, 0, ossz_gramm, 0);
    // int a=test.;

    kg = ujtest.kg;
    dkg = ujtest.dkg;
    g = ujtest.g;
}
*/

void Tomeg_g::kiir_g()
{
    if (kg)
        cout << kg << "kg ";
    if (dkg)
        cout << dkg << "dkg ";
    if (g + maradek)
        cout << (g + maradek) << "g";
    cout << endl;
}

//-------------------------------------------------------------------
//              DRAM              DRAM            DRAM
//-------------------------------------------------------------------

Tomeg_d::Tomeg_d(int font, int uncia, int dram)
{
    int ossz_dram = font * 16 * 16 + uncia * 16 + dram;
    this->font = ossz_dram / 256;
    ossz_dram %= 256;
    this->uncia = ossz_dram / 16;
    ossz_dram %= 16;
    this->dram = ossz_dram;
}

Tomeg_d::operator Tomeg_g()
{
    double marad = 1.77 * ossz_dram();
    int g = static_cast<int>(marad);
    marad -= g;
    int kg = g / 1000;
    g %= 1000;
    int dkg = g / 10;
    g %= 10;
    return Tomeg_g(kg, dkg, g, marad);
}

int Tomeg_d::ossz_dram()
{
    return font * 256 + uncia * 16 + dram;
}

void Tomeg_d::kiir_d()
{
    if (font)
        cout << font << "ft ";
    if (uncia)
        cout << uncia << "unc ";
    if (dram)
        cout << dram << "dram";
    cout << endl;
}