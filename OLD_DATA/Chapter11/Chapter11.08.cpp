// 11/03/2026
// Chapter11.08.cpp
// Exercises

//
// [9] Draw a 300-by-200-pixel ellipse.
//     Draw a 400-pixel-long x axis and a 300-pixel-long y axis through the center of the ellipse.
//     Mark the foci. Mark a point on the ellipse that is not on one of the axes.
//     Draw the two lines from the foci to the point.
//
//     Sources:
//         https://www.geeksforgeeks.org/dsa/check-if-a-point-is-inside-outside-or-on-the-ellipse/
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/*------------------------------------------------------------------*\
| Utility Function                                                   |
\*------------------------------------------------------------------*/
Point find_point_on_ellipse(const Point &origin, const int &major_axis, const int &minor_axis)
{
	for (auto [d, y_coord] = tuple{ 0., 1 }; y_coord < origin.y + minor_axis; y_coord += 5 /* 5 is arbitrary. This produces a point that isn't on either axis. */)
		for (int x_coord = 1; x_coord < origin.x + major_axis; ++x_coord)
		{
			// Equals 1 if coords are on the ellipse
			d = (pow((x_coord - origin.x), 2) / pow(major_axis, 2)) + (pow((y_coord - origin.y), 2) / pow(minor_axis, 2));

			if (d == 1)
				return { x_coord, y_coord };
		}
	error("this shouldn't happen");

} // This is horrific, but I just need a point on the ellipse man..

/*------------------------------------------------------------------*\
| Main                                                               |
\*------------------------------------------------------------------*/
int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 540, 360, "Ellipse Exercise" };

		// Ellipse //
		const int major = 300 / 2, minor = 200 / 2;

		Ellipse el{ {win.x_max() / 2, win.y_max() / 2}, major, minor };
		el.set_color(Color::white);

		// Axes //
		Axis x_axis{ Axis::x, {win.x_max() / 2 - 200, win.y_max() / 2}, 400, 8, "X" };
		x_axis.set_color(Color::white);
		
		Axis y_axis{ Axis::y, {win.x_max() / 2, win.y_max() / 2 + 150}, 300, 6, "Y" };
		y_axis.set_color(Color::white);

		// Marks //
		Mark focal_1{ {el.focus1()}, '*' };
		focal_1.set_color(Color::red);

		Mark focal_2{ {el.focus2()}, '*' };
		focal_2.set_color(Color::red);

		Mark point{ find_point_on_ellipse({win.x_max() / 2, win.y_max() / 2} , major, minor), '*'};
		point.set_color(Color::cyan);

		// Lines //
		Line focal_1_to_point{ el.focus1(), point.point(0) };
		focal_1_to_point.set_color(Color::red);

		Line focal_2_to_point{ el.focus2(), point.point(0) };
		focal_2_to_point.set_color(Color::red);

		// Attachments //
		win.attach(x_axis);
		win.attach(y_axis);
		win.attach(el);
		win.attach(focal_1);
		win.attach(focal_2);
		win.attach(point);
		win.attach(focal_1_to_point);
		win.attach(focal_2_to_point);

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
