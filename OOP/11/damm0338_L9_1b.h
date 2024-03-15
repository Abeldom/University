#include <iostream>
#include <math.h>
#define PI 3.1415926535
using namespace std;

class Alakzat {

public:
    Alakzat() {};
    virtual double terulet() = 0;
    virtual double kerulet() = 0;
    virtual void nagyit() = 0;
};

class Kor : public Alakzat {
    double radius;

public:
    Kor(double radius = 0)
    {
        this->radius = radius;
    }
    double terulet()
    {
        return PI * radius * radius;
    }
    double kerulet()
    {
        return 2 * PI * radius;
    }
    void nagyit()
    {
        radius *= 2;
    }
};

class Haromszog : public Alakzat {
    double side1, side2, side3;

public:
    Haromszog(double side1 = 0, double side2 = 0, double side3 = 0)
    {
        this->side1 = side1;
        this->side2 = side2;
        this->side3 = side3;
    }
    double terulet()
    {
        double p = (side1 + side2 + side3) / 2;
        return sqrt(p * (p - side1) * (p - side2) * (p - side3));
    }
    double kerulet()
    {
        return side1 + side2 + side3;
    }
    void nagyit()
    {
        side1 *= 2;
        side2 *= 2;
        side3 *= 2;
    }
};

class Derekszogu_haromszog : public Haromszog {

public:
    Derekszogu_haromszog(double side1 = 0, double side2 = 0, double side3 = 0)
        : Haromszog(side1, side2, side3)
    {
        if (side1 > side2) {
            swap(side1, side2);
        };

        if (side2 > side3) {
            swap(side2, side3);
        };
        if (side1 * side1 + side2 * side2 != side3 * side3) {
            throw "Nem derekszogu";
        }
    }
};