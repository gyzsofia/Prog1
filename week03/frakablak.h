#ifndef FRAKABLAK_H
#define FRAKABLAK_H

#include <QMainWindow>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include "frakszal.h"

class FrakSzal;

class FrakAblak : public QMainWindow
{
    Q_OBJECT

public:
    FrakAblak(double a = -2.0, double b = .7, double c = -1.35,
              double d = 1.35, int szelesseg = 600,
              int iteraciosHatar = 255, QWidget *parent = 0);
    ~FrakAblak();
    void vissza(int magassag , int * sor, int meret) ;
    void vissza(void) ;
    // A komplex sk vizsglt tartomnya [a,b]x[c,d].
    double a, b, c, d;
    // A komplex sk vizsglt tartomnyra fesztett
    // hl szlessge s magassga.
    int szelesseg, magassag;
    // Max. hny lpsig vizsgljuk a z_{n+1} = z_n * z_n + c itercit?
    // (tk. most a nagytsi pontossg)
    int iteraciosHatar;

protected:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void keyPressEvent(QKeyEvent*);

private:
    QImage* fraktal;
    FrakSzal* mandelbrot;
    bool szamitasFut;
    // A nagytand kijellt terletet bal fels sarka.
    int x, y;
    // A nagytand kijellt terlet szlessge s magassga.
    int mx, my;
    int kepszam;
};

#endif // FRAKABLAK_H

