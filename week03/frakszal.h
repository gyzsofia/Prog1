#ifndef FRAKSZAL_H
#define FRAKSZAL_H

#include <QThread>
#include <cmath>
#include <complex>
#include "frakablak.h"

class FrakAblak;

class FrakSzal : public QThread
{
    Q_OBJECT

public:
    FrakSzal(double a, double b, double c, double d,
             int szelesseg, int magassag, int iteraciosHatar, FrakAblak *frakAblak);
    ~FrakSzal();
    void run();

protected:
    // A komplex sk vizsglt tartomnya [a,b]x[c,d].
    double a, b, c, d;
    // A komplex sk vizsglt tartomnyra fesztett
    // hl szlessge s magassga.
    int szelesseg, magassag;
    // Max. hny lpsig vizsgljuk a z_{n+1} = z_n * z_n + c itercit?
    // (tk. most a nagytsi pontossg)
    int iteraciosHatar;
    // Kinek szmolok?
    FrakAblak* frakAblak;
    // Soronknt kldm is neki vissza a kiszmoltakat.
    int* egySor;

};

#endif // FRAKSZAL_H

