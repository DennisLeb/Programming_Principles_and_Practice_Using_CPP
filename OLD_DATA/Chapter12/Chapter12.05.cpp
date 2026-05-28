// 16/04/2026
// Chapter12.05.cpp
// Exercises

//
// [8] Define a class 'Octagon' to be a regular octagon.
//     Write a test that exercises all of its functions (as defined by you or inherited from 'Shape').
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#define PI 3.14159265359

/*----------------------------------------*\
| Class Definitions                        |
\*----------------------------------------*/
struct Regular_octagon : Polygon
{
	Regular_octagon(const Point &cntr, const int &dist_to_cntr, const double &rotation_in_d);
	void draw_specifics(Painter &painter) const override;

	// overwrite some of 'Shape's functions (can technically still be accessed)
	void add(Point) { error("undefined operation for regular octagons"); }
	void set_point(int, Point) { error("undefined operation for regular octagons"); }
};

/*------------------------------------------------------------------*\
| Member Functions                                                   |
\*------------------------------------------------------------------*/
Regular_octagon::Regular_octagon(const Point &cntr, const int &dist_to_cntr, const double &rotation_in_d = 0.)
{
	constexpr double interior_angle = 2. * PI / 8.;	// 2 * PI / sides

	for (auto [i, x_coord, y_coord] = tuple{ 0, 0., 0. }; i < 8; ++i)	// First vertex will always be at 3 o'clock
	{
		x_coord = double(cntr.x) + double(dist_to_cntr) * cos(double(i) * interior_angle + rotation_in_d * PI / 180.);
		y_coord = double(cntr.y) - double(dist_to_cntr) * sin(double(i) * interior_angle + rotation_in_d * PI / 180.);

		Polygon::add({ int(round(x_coord)), int(round(y_coord)) });
	}
}

void Regular_octagon::draw_specifics(Painter &painter) const
{
	Polygon::draw_specifics(painter);
}

/*----------------------------------------*\
| Main                                     |
\*----------------------------------------*/
int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 1080, 720, "Striped Rectangle" };

		// Octagons //
		Regular_octagon oct_1{ {100, 100}, 75 };
		oct_1.set_color(Color::white);
		oct_1.set_fill_color(Color::dark_cyan);
		oct_1.move(100, 100);

		Regular_octagon oct_2{ {600, 250}, 225, 32.2 };
		oct_2.set_color(Color::white);
		oct_2.set_fill_color(Color::red);
		
		Regular_octagon oct_3{ {700, 500}, 150, 107.8 };
		oct_3.set_color(Color::white);
		oct_3.set_fill_color(Color::yellow);

		win.attach(oct_1);
		win.attach(oct_2);
		win.attach(oct_3);

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
