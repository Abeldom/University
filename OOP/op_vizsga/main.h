#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

class GrayscalePoint {
  int szin;

 public:
  GrayscalePoint();
  GrayscalePoint(int);
  GrayscalePoint& operator+=(int);
  GrayscalePoint& operator-=(int);

  void kiir() const;
  int get_szin() { return szin; }
};

class ColorPoint {
  GrayscalePoint R;
  GrayscalePoint G;
  GrayscalePoint B;

 public:
  ColorPoint();
  ColorPoint(GrayscalePoint&, GrayscalePoint&, GrayscalePoint&);

  ColorPoint operator++(int);  // post++
  ColorPoint& operator++();    //++pre
  ColorPoint& operator+=(int);

  GrayscalePoint getAsGray();
  void kiir();
};

#endif