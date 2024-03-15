// Domokos Ábel
// 411

#include "damm0338_L9_1a.h"

int main()
{
    char* szoveg = new char[20];
    strcpy(szoveg, "Sorrend> ");
    J obj(szoveg, 15);
    obj.kiir();
    cout << szoveg;

    return 0;
}