#include "../lib_files/Simple_window.h"
#include "../lib_files/Graph.h"

int main()
{
using namespace Graph_lib;

try {
	Simple_window win {Point{100,100},600,400,"Canvas"};
	
	win.wait_for_button();
	
	Rectangle rect {Point{100,100},80,40};
	
	rect.set_color(Color::blue);
	win.attach(rect);
	win.set_label("Canvas 1");
	win.wait_for_button();
	
	Polygon poly;
	
	poly.add(Point{200,100});
	poly.add(Point{280,100});
	poly.add(Point{280,140});
	poly.add(Point{200,140});
	
	poly.set_color(Color::red);
	win.attach(poly);
	win.set_label("Canvas 2");
	win.wait_for_button();
}
catch(exception& e){
cerr << "Exception: " << e.what() << '\n';
}
catch(...){
cerr << "Valami hiba tortent" << '\n';
}
}
