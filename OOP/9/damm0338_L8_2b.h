// Domokos Abel
// 411

#include <iostream>
using namespace std;

class komp_kiir;

class komp {
protected:
    int valos;
    int imaginarius;

public:
    komp(int valos = 1, int imaginarius = 0);
    komp operator*(komp);
    virtual komp& operator*=(komp);
    // operator komp_kiir()
    // {
    //     return komp_kiir(valos, imaginarius);
    // }
    void kiir();
};

class komp_kiir : public komp {
public:
    komp_kiir(int a = 0, int b = 0);
    komp_kiir operator*(komp_kiir);
    // komp_kiir& operator*=(komp_kiir);
    // operator komp()
    // {
    //     return komp(valos, imaginarius);
    // }
};

komp::komp(int valos, int imaginarius)
{
    this->valos = valos;
    this->imaginarius = imaginarius;
}

komp komp::operator*(komp z)
{
    int uj_valos = valos * z.valos - imaginarius * z.imaginarius;
    int uj_imag = valos * z.imaginarius + imaginarius * z.valos;
    return komp(uj_valos, uj_imag);
}

komp& komp::operator*=(komp z)
{
    return *this = *this * z;
}

void komp::kiir()
{
    cout << valos;

    if (imaginarius > 0)
        cout << "+" << imaginarius << "i";
    else
        cout << imaginarius << "i";
    cout << endl;
}

komp_kiir::komp_kiir(int valos, int imaginarius)
    : komp(valos, imaginarius)
{
    this->valos = valos;
    this->imaginarius = imaginarius;
}

komp_kiir komp_kiir::operator*(komp_kiir z)
{
    int uj_valos = valos * z.valos - imaginarius * z.imaginarius;
    int uj_imag = valos * z.imaginarius + imaginarius * z.valos;
    komp_kiir ujz(uj_valos, uj_imag);

    cout << "(";
    cout << valos;
    if (imaginarius > 0)
        cout << "+" << imaginarius << "i";
    else
        cout << imaginarius << "i";

    cout << ") * (";

    cout << z.valos;
    if (z.imaginarius > 0)
        cout << "+" << z.imaginarius << "i";
    else
        cout << z.imaginarius << "i";

    cout << ") = ";

    ujz.kiir();

    return ujz;
}

// komp_kiir& komp_kiir::operator*=(komp_kiir z)
// {
//     return *this = *this * z;
// }