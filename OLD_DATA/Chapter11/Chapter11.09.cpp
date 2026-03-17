// 14/03/2026
// Chapter11.09.cpp
// Exercises

//
// [10] Draw a circle.
//		Move a mark around the circle (let it move a bit each time you hit the "Next" button).
//
//		Sources:
//			https://math.stackexchange.com/questions/260096/find-the-coordinates-of-a-point-on-a-circle
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#define PI 3.14159265359

/*------------------------------------------------------------------*\
| Utility Function                                                   |
\*------------------------------------------------------------------*/
Point find_next_point(const Circle &circ, const double &theta)
{
	return { int((double)circ.center().x + (double)circ.radius() * sin(theta)), int((double)circ.center().y - (double)circ.radius() * cos(theta)) };
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
		Simple_window win{ {50, 50}, 540, 360, "Moving Around a Circle" };

		// Circle //
		Circle circ{ {win.x_max() / 2, win.y_max() / 2}, 150 };
		circ.set_fill_color(Color::dark_cyan);

		// Attachments //
		win.attach(circ);

		// Moving around Circle //
		for (double rad = PI / 4; rad < 2 * PI; rad += PI / 4)	// Move in 1/8 steps
		{
			Mark point_on_circ{ find_next_point(circ, rad), 'X' };
			point_on_circ.set_color(Color::red);

			win.attach(point_on_circ);
			win.wait_for_button();
		}
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
