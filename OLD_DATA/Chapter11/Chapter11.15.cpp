// 17/03/2026
// Chapter11.15.cpp
// Exercises

//
// [17] Define a class 'Star'.
//		One parameter should be the number of points.
//		Draw a few stars with differing numbers of points, differing line colors, and differing fill colors.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#define PI 3.14159265359

/*------------------------------------------------------------------*\
| Class Definition                                                   |
\*------------------------------------------------------------------*/
struct Star : Polygon
{
	Star(const Point &center, const int &num_of_points, const int &radius, const double &rotation_in_d = 0.);

	void draw_specifics(Painter &painter) const override;
};

/*------------------------------------------------------------------*\
| Member Functions                                                   |
\*------------------------------------------------------------------*/
Star::Star(const Point &center, const int &num_of_points, const int &radius, const double &rotation_in_d)
{
	const double interior_angle = 2. * PI / double(num_of_points);

	for (auto [i, x_coord, y_coord] = tuple{ 0, 0, 0 }; i < num_of_points; ++i)	// First vertex will always be at 12 o'clock
	{
		// Draw outer points of the Star
		x_coord = (int)round((double)center.x + (double)radius * sin((double)i * interior_angle + rotation_in_d * PI / 180.));
		y_coord = (int)round((double)center.y - (double)radius * cos((double)i * interior_angle + rotation_in_d * PI / 180.));

		Polygon::add({ x_coord, y_coord });

		// Draw inner points of the Star (using a fraction of radius and an angle inbetween outer points)
		x_coord = (int)round((double)center.x + ((double)radius / 4.) * sin(((double)i + .5) * interior_angle + rotation_in_d * PI / 180.));
		y_coord = (int)round((double)center.y - ((double)radius / 4.) * cos(((double)i + .5) * interior_angle + rotation_in_d * PI / 180.));

		Polygon::add({ x_coord, y_coord });
	}
}

void Star::draw_specifics(Painter &painter) const
{
	// This checks that num_of_points > 2
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
		Simple_window win{ {50, 50}, 1080, 720, "Star Class" };

		// Stars //
		constexpr int max_points = 16;
		constexpr int max_radius = 75;
		constexpr int num_of_stars = 32;

		Vector_ref<Star> stars;

		srand(time(0));
		for (auto [center, points, radius, i, rotation] = tuple<Point, int, int, int, double>{ {0, 0}, 0, 0, 0, 0. }; i < num_of_stars; ++i)
		{
			center.x = rand() % (win.x_max() - 99) + 50;
			center.y = rand() % (win.y_max() - 99) + 50;
			points = rand() % max_points + 3;
			radius = rand() % max_radius + 15;
			rotation = double(rand() % 36000) / 100.;

			stars.push_back(make_unique<Star>(center, points, radius, rotation));

			stars[stars.size() - 1].set_color(rand() % 256);
			stars[stars.size() - 1].set_fill_color(rand() % 256);

			win.attach(stars[stars.size() - 1]);
		}

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
