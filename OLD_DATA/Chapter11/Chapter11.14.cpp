// 17/03/2026
// Chapter11.14.cpp
// Exercises

//
// [16] Define a class 'Poly' that represents a polygon but checks that its points really do make a polygon in its constructor.
//		Hint: You'll have to supply the points to the constructor.
// 

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/*------------------------------------------------------------------*\
| Class Definition                                                   |
\*------------------------------------------------------------------*/
struct Poly : Polygon
{
	Poly(std::initializer_list<Point> p_list = {});

	void draw_specifics(Painter &painter) const override;
};

/*------------------------------------------------------------------*\
| Member Functions                                                   |
\*------------------------------------------------------------------*/
Poly::Poly(std::initializer_list<Point> p_list)
{
	for (Point p : p_list)
		Polygon::add(p);
}

void Poly::draw_specifics(Painter &painter) const
{
	Polygon::draw_specifics(painter);
}

/*------------------------------------------------------------------*\
| Main                                                               |
\*------------------------------------------------------------------*/
int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 1080, 720, "Poly class" };

		// Polys //
		Poly poly_1{ {75, 75}, {125, 75}, {100, 100} };
		poly_1.set_color(Color::white);
		poly_1.set_fill_color(Color::dark_cyan);

		Poly poly_2{ {75, 250}, {200, 250}, {250, 400}, {75, 300} };
		poly_2.set_color(Color::white);
		poly_2.set_fill_color(Color::dark_cyan);

		// Attachments //
		win.attach(poly_1);
		win.attach(poly_2);

		win.wait_for_button();
		return 0;
	}
	catch (exception &e)
	{
		cerr << "error: " << e.what() << endl;
		return 1;
	}
	catch (...)
	{
		cerr << "unknown error" << endl;
		return 2;
	}
}
