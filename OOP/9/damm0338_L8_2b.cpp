// Domokos Abel
// 411

#include "damm0338_L8_2b.h"

int main()
{

    komp p(1, 2), q(3, 3), r;

    r = p *= q;

    p.kiir();

    r.kiir();

    komp_kiir p1(1, 2), q1(3, 3);

    komp r1, r2;

    r1 = p1 * q1;

    r2 = p1 *= q1;

    p1.kiir();

    r1.kiir();

    r2.kiir();

    return 0;
}