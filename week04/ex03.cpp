#define _USE_MATH_DEFINES
#include "Simple_window.h"
#include "Graph.h"
#include <cmath>

typedef double Fct(double);

double one(double x) { return 1; }
double slope(double x) { return x / 2; }
double square(double x) { return x * x; }
double sloping_cos(double x) { return cos(x) + slope(x); }
double sum_sin_cos(double x) { return sin(x) + cos(x); }
double sum_sin_cos_sq(double x) { return sin(x) * sin(x) + cos(x) * cos(x); }

template <class T> class myFct : Shape {
public:
myFct(Fct* f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25, T precision = 1.0);
~myFct() {}

void set_f(Fct* p) { f = p; }
void set_r1(double r) { r1 = r; }
void set_r2(double r) { r2 = r; }
void set_orig(Point o) { orig = o; }
void set_count(int c) { count = c; }
void set_xscale(double x) { xscale = x; }
void set_yscale(double y) { yscale = y; }
void set_precision(T p) { precision = p; }

double get_r1() { return r1; }
double get_r2() { return r2; }
Point get_orig() { return orig; }
int get_count() { return count; }
double get_xscale() { return xscale; }
double get_yscale() { return yscale; }
T get_precision() { return precision; }

void calc();
void reset(Fct* f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25, T precision = 1.0);

private:
Fct* f;
double r1;
double r2;
Point orig;
int count;
double xscale;
double yscale;
T precision;
};

template <class T> myFct<T>::myFct(Fct* f, double r1, double r2, Point orig, int count, double xscale, double yscale, T precision)
:f(f), r1(r1), r2(r2), orig(orig), count(count), xscale(xscale), yscale(yscale), precision(precision)
{
calc();
}

template <class T> void myFct<T>::calc()
{
if (r2 – r1 <= 0) error("bad graphing range");
if (count <= 0) error("non-positive graphing count");
double dist = (r2 – r1) / count;
double r = r1;
for (int i = 0; i < count; ++i) {
cout << f(r) << endl;
int x = orig.x + int(int(r * xscale) / precision) * precision;
int y = orig.y – int(int(f(r) * yscale) / precision) * precision;
add(Point(x, y));
r += dist;
}
}

template <class T> void myFct<T>::reset(Fct* f, double r1, double r2, Point orig, int count, double xscale, double yscale, T precision)
{
set_f(f);
set_r1(r1);
set_r2(r2);
set_orig(orig);
set_count(count);
set_xscale(xscale);
set_yscale(yscale);
set_precision(precision);
calc();
}

int main()
try
{
int min = 0;
int max = 5;
Point origin(0, 0);
int count = 5;
double xscale, yscale = 25;

myFct<double> MF(one, min, max, origin, count, xscale, yscale, 2.0);
cout << "—" << endl;
MF.reset(slope, min, max, origin, count, xscale, yscale, 3.0);

keep_window_open();
}
catch (exception& e) {
cerr << "error: " << e.what() << ‘\n’;
keep_window_open();
return 1;
}

catch (…) {
cerr << "Unknown exception!\n";
keep_window_open();
return 2;
}
