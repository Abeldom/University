// Domokos Ábel
// 411

#include "damm0338_L9_1b.h"

int main()
{
    Alakzat* a[] = { new Kor(3), new Haromszog, new Derekszogu_haromszog(3, 4, 5) };

    cout << a[0]->kerulet() << ", " << a[0]->terulet() << endl;
    cout << a[1]->kerulet() << ", " << a[1]->terulet() << endl;
    cout << a[2]->kerulet() << ", " << a[2]->terulet() << endl;

    delete a[0];
    delete a[1];
    delete a[2];

    return 0;
}