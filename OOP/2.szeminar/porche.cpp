#include <iostream>
using namespace std;
namespace tomb_nevter {
int tomb[100];
int hossz;
void inicializal(int* t, int h);
void ketszerez();
void kiir();
} // namespace tomb_nevter

void tomb_nevter::inicializal(int* t, int h)
{
    hossz = h;
    for (int i = 0; i < hossz; i++) {
        tomb[i] = t[i];
    }
}

void tomb_nevter::ketszerez()
{
    for (int i = 0; i < hossz; i++) {
        tomb[i] *= 2;
    }
}

void tomb_nevter::kiir()
{
    for (int i = 0; i < hossz; i++) {
        cout << tomb[i] << " ";
    }
    cout << endl;
}

int main()
{
    int ukrosz[] = { 1, 222, 11, 5442 };
    tomb_nevter::inicializal(ukrosz, 4);
    tomb_nevter::ketszerez();
    tomb_nevter::kiir();
    return 0;
}