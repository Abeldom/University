// Domokos Ábel
// 411

#include "damm0338_L7_1b.h"

int main()
{
    Ido a(2, 1, 59);
    a.kiir();

    a += 1; // előbb 1-ről Ido-re konvertál
    a.kiir();

    a -= 1; // előbb 1-ről Ido-re konvertál
    a.kiir();
    cout << endl;
    /////////
    Ido b(9605);
    b.kiir(); // 2 óra 40 perc 5 másodperc

    try {
        a -= b; // összeadja a két időt
        a.kiir();
    } catch (const char* uzenet) {
        cout << uzenet;
    }
    return 0;
}