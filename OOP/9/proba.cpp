#include <iostream>
using namespace std;

class hossz_m {
    int mm;
    int cm;
    int dm;
    int m;
    double marad; // maradék, a konverzió után
public:
    hossz_m(int mm_1 = 0, int cm_1 = 0,
        int dm_1 = 0, int m_1 = 0, double marad1 = 0.0);
    void kiir();
    // hossz_m(hossz_inch h);
};

hossz_m::hossz_m(int mm_1, int cm_1,
    int dm_1, int m_1, double marad1)
{
    mm = mm_1;
    cm = cm_1;
    dm = dm_1;
    m = m_1;
    marad = marad1;
}

class hossz_inch {
    int line;
    int inch;
    int foot;
    int yard;

public:
    hossz_inch(int l = 0, int i = 0, int f = 0, int y = 0);
    int line_hossz();
    void kiir();
    operator hossz_m();
};

hossz_inch::hossz_inch(int l, int i, int f, int y)
{
    line = l;
    inch = i;
    foot = f;
    yard = y;
}

hossz_inch::operator hossz_m()
{
    double marad1 = 2.54 * line_hossz();
    int mm1 = static_cast<int>(marad1);
    marad1 -= mm1;
    int m1 = mm1 / 1000;
    mm1 %= 1000;
    int dm1 = mm1 / 100;
    mm1 %= 100;
    int cm1 = mm1 / 10;
    mm1 %= 10;
    return hossz_m(mm1, cm1, dm1, m1, marad1);
}

int hossz_inch::line_hossz()
{
    return line + 10 * inch + 120 * foot + 360 * yard;
}

void hossz_m::kiir()
{
    if (m)
        cout << m << " m ";
    if (dm)
        cout << dm << " dm ";
    if (cm)
        cout << cm << " cm ";
    if (mm + marad)
        cout << mm + marad << " mm ";
    cout << endl;
}

void hossz_inch::kiir()
{
    if (line)
        cout << line << " line ";
    if (inch)
        cout << inch << " inch ";
    if (foot)
        cout << foot << " foot ";
    if (yard)
        cout << yard << " yard";
    cout << endl;
}

int main()
{ // ugyanaz
    hossz_inch y(6, 3, 2, 5);
    y.kiir();
    cout << y.line_hossz() << " line\n";
    cout << 2.54 * y.line_hossz() << " mm\n";
    hossz_m x;
    x = y;
    x.kiir();
}