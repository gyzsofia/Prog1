#include "std_lib_facilities.h"

int fac_recursive(int n) { return n > 1 ? n * fac_recursive(n – 1) : 1; } // factorial n!

int fac_iterative(int n)
{
int r = 1;
while (n > 1) {
r *= n;
–n;
}
return r;
}

int main()
try
{
for (int i = 0; i < 21; i++) {
cout << fac_recursive(i) << endl;
}

for (int i = 0; i < 21; i++) {
cout << fac_iterative(i) << endl;
}

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
