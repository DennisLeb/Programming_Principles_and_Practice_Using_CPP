// 11/03/2026
// Chapter11.07.cpp
// Exercises

//
// [8] Define a class 'Regular_polygon'.
//     Use the center, the number of sides (>2), and the distance from the center to a corner point as constructor arguments.
//
//     Sources:
//         https://www.mathsisfun.com/geometry/regular-polygons.html
//         https://math.stackexchange.com/questions/117164/calculate-coordinates-of-a-regular-polygon
//         https://stackoverflow.com/questions/3436453/calculate-coordinates-of-a-regular-polygons-vertices
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#define PI 3.14159265359

/*------------------------------------------------------------------*\
| Class Definition                                                   |
\*------------------------------------------------------------------*/
struct Regular_polygon : Polygon
{
	Regular_polygon(const Point &cntr, const int &dist_to_cntr, const int &sides);
	void draw_specifics(Painter &painter) const override;
};

/*------------------------------------------------------------------*\
| Member Functions                                                   |
\*------------------------------------------------------------------*/
Regular_polygon::Regular_polygon(const Point &cntr, const int &dist_to_cntr, const int &sides)
{
	const double interior_angle = 2. * PI / double(sides);

	if (sides % 2)
		for (auto [i, x_coord, y_coord] = tuple{ 0, 0., 0. }; i < sides; ++i)	// First vertex will always be at 12 o'clock
		{
			x_coord = double(cntr.x) + double(dist_to_cntr) * sin(double(i) * interior_angle);
			y_coord = double(cntr.y) - double(dist_to_cntr) * cos(double(i) * interior_angle);

			Polygon::add({ int(round(x_coord)), int(round(y_coord)) });	// Rounding precisely makes all the difference here
		}

	else
		for (auto [i, x_coord, y_coord] = tuple{ 0, 0., 0. }; i < sides; ++i)	// First vertex will always be at 3 o'clock
		{
			x_coord = double(cntr.x) + double(dist_to_cntr) * cos(double(i) * interior_angle);
			y_coord = double(cntr.y) - double(dist_to_cntr) * sin(double(i) * interior_angle);
		
			Polygon::add({ int(round(x_coord)), int(round(y_coord)) });
		}
}

void Regular_polygon::draw_specifics(Painter &painter) const
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
		Simple_window win{ {50, 50}, 1080, 720, "Regular Polygon" };

		// Polygons //
		Regular_polygon circle{ {win.x_max() / 2, win.y_max() / 2}, 300, 84 };
		circle.set_fill_color(Color::dark_cyan);

		Regular_polygon triangle{ {75, 75}, 40, 3 };
		triangle.set_fill_color(Color::dark_red);

		Regular_polygon square{ {780, 560}, 80, 4 };
		square.set_fill_color(Color::dark_blue);

		Regular_polygon pentagon{ {680, 220}, 100, 5 };
		pentagon.set_fill_color(Color::magenta);

		Regular_polygon hexagon{ {320, 600}, 75, 6 };
		hexagon.set_fill_color(Color::white);

		Regular_polygon heptagon{ {600, 550}, 60, 7 };
		heptagon.set_fill_color(Color::dark_green);

		Regular_polygon octagon{ {200, 400}, 90, 8 };
		octagon.set_fill_color(Color::dark_yellow);

		// Attachments //
		win.attach(circle);
		win.attach(triangle);
		win.attach(square);
		win.attach(pentagon);
		win.attach(hexagon);
		win.attach(heptagon);
		win.attach(octagon);

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
