// Domokos Ábel
// 411

#include <iostream>
using namespace std;

class Ido {
    int hour, minute, second;

public:
    Ido(int hour1, int minute1, int second1);
    Ido(int seconds);

    Ido& operator+=(const Ido& i);
    Ido& operator-=(const Ido& i);
    void kiir();
};

Ido::Ido(int h, int m, int s)
{
    if (h < 0 || m < 0 || s < 0) {
        throw "Invalid input.";
    }
    hour = h + m / 60 + s / 3600;
    minute = (m + s / 60) % 60;
    second = s % 60;
}

Ido::Ido(int s)
{
    if (s < 0) {
        throw "Invalid input.";
    }
    hour = s / 3600;
    minute = (s / 60) % 60;
    second = s % 60;
}

Ido& Ido::operator+=(const Ido& time)
{
    Ido new_time(hour + time.hour, minute + time.minute, second + time.second);
    *this = new_time;
    return *this;
}

Ido& Ido::operator-=(const Ido& time)
{
    int t1 = hour * 3600 + minute * 60 + second;
    int t2 = time.hour * 3600 + time.minute * 60 + time.second;
    if (t1 - t2 < 0) {
        throw "Invalid operation.";
    }
    Ido new_time(t1 - t2);
    *this = new_time;
    return *this;
}

void Ido::kiir()
{
    cout << hour << "h " << minute << "m " << second << "s " << endl;
}
