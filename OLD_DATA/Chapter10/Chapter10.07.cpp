// 05/03/2026
// Chapter10.07.cpp
// Exercises

//
// [11] Draw a series of regular polygons, one inside the other.
//		The innermost should be an equilateral triangle, enclosed by a square, enclosed by a pentagon, etc..
//		For the mathematically adept only: let all the points of each 'N'-polygon touch sides of the '(N + 1)'-polygon.
//		Hint: the trigonemetric functions are found in <cmath> and module std.
//

#include "PPP/Graph.h";
#include "PPP/Simple_window.h";

using namespace Graph_lib;

int main()
{
	Application app;
	Simple_window win{ Point{20, 20}, 600, 400, "Enclosed polygons" };

	// 82p per side
	Polygon poly_tri
	{
		Point{259, 200},
		Point{341, 200},
		Point{300, 129}
	};
	poly_tri.set_fill_color(Color::blue);
	
	Polygon poly_square
	{
		Point{259, 200},
		Point{341, 200},
		Point{341, 129},
		Point{259, 129}
	};
	poly_square.set_fill_color(Color::red);
	
	Polygon poly_pent
	{
		Point{249, 200},
		Point{351, 200},
		Point{355, 135},
		Point{300, 110},
		Point{245, 135}
	};
	poly_pent.set_fill_color(Color::cyan);
	
	Polygon poly_hex
	{
		Point{240, 200},
		Point{300, 225},
		Point{360, 200},
		Point{360, 125},
		Point{300, 100},
		Point{240, 125}
	};
	poly_hex.set_fill_color(Color::white);

	win.attach(poly_hex);
	win.attach(poly_pent);
	win.attach(poly_square);
	win.attach(poly_tri);

	win.wait_for_button();
	return 0;
}
