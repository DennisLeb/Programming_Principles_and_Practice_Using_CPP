// 10/03/2026
// Chapter11.03.cpp
// Exercises

//
// [3] Define the functions from exercise 2 for a 'Circle' and an 'Ellipse'.
//     Place the connection points on or outside the shape but not outside the bounding rectangle.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/**********************************/
/******** HELPER FUNCTIONS ********/
/**********************************/
// Circle //
Point n(const Circle &c) { return { c.center().x, c.center().y - c.radius() }; }

Point s(const Circle &c) { return { c.center().x, c.center().y + c.radius() }; }

Point e(const Circle &c) { return { c.center().x + c.radius(), c.center().y }; }

Point w(const Circle &c) { return { c.center().x - c.radius(), c.center().y }; }

Point center(const Circle &c) { return c.center(); }

Point ne(const Circle &c) { return { c.center().x + c.radius(), c.center().y - c.radius() }; }

Point se(const Circle &c) { return { c.center().x + c.radius(), c.center().y + c.radius() }; }

Point sw(const Circle &c) { return { c.center().x - c.radius(), c.center().y + c.radius() }; }

Point nw(const Circle &c) { return { c.center().x - c.radius(), c.center().y - c.radius() }; }

// Ellipse //
Point n(const Ellipse &el) { return { el.center().x, el.center().y - el.minor()}; }

Point s(const Ellipse &el) { return { el.center().x, el.center().y + el.minor() }; }

Point e(const Ellipse &el) { return { el.center().x + el.major(), el.center().y }; }

Point w(const Ellipse &el) { return { el.center().x - el.major(), el.center().y }; }

Point center(const Ellipse &el) { return el.center(); }

Point ne(const Ellipse &el) { return { el.center().x + el.major(), el.center().y - el.minor() }; }

Point se(const Ellipse &el) { return { el.center().x + el.major(), el.center().y + el.minor() }; }

Point sw(const Ellipse &el) { return { el.center().x - el.major(), el.center().y + el.minor() }; }

Point nw(const Ellipse &el) { return { el.center().x - el.major(), el.center().y - el.minor() }; }

/**********************/
/******** MAIN ********/
/**********************/
int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 1080, 720, "Circle/Ellipse connection points" };

		// Circle //
		Circle c{ {win.x_max() / 6, win.y_max() / 2}, win.x_max() / 8 };
		c.set_fill_color(Color::dark_cyan);

		// Ellipse //
		Ellipse el{ {win.x_max() * 2 / 3, win.y_max() / 2}, win.x_max() / 4, win.y_max() / 6 };
		el.set_fill_color(Color::dark_red);

		// Connection Points - Circle //
		Mark c_north{ n(c), 'N' };
		c_north.set_color(Color::white);

		Mark c_south{ s(c), 'S' };
		c_south.set_color(Color::white);

		Mark c_east{ e(c), 'E' };
		c_east.set_color(Color::white);

		Mark c_west{ w(c), 'W' };
		c_west.set_color(Color::white);

		Mark c_cntr{ center(c), 'C' };
		c_cntr.set_color(Color::white);

		Mark c_north_east{ ne(c), 'n' };
		c_north_east.set_color(Color::white);

		Mark c_south_east{ se(c), 's' };
		c_south_east.set_color(Color::white);

		Mark c_south_west{ sw(c), 's'};
		c_south_west.set_color(Color::white);

		Mark c_north_west{ nw(c), 'n'};
		c_north_west.set_color(Color::white);

		// Connection Points - Ellipse //
		Mark el_north{ n(el), 'N' };
		el_north.set_color(Color::white);

		Mark el_south{ s(el), 'S' };
		el_south.set_color(Color::white);

		Mark el_east{ e(el), 'E' };
		el_east.set_color(Color::white);

		Mark el_west{ w(el), 'W' };
		el_west.set_color(Color::white);

		Mark el_cntr{ center(el), 'C' };
		el_cntr.set_color(Color::white);

		Mark el_north_east{ ne(el), 'n'};
		el_north_east.set_color(Color::white);

		Mark el_south_east{ se(el), 's'};
		el_south_east.set_color(Color::white);

		Mark el_south_west{ sw(el), 's'};
		el_south_west.set_color(Color::white);

		Mark el_north_west{ nw(el), 'n'};
		el_north_west.set_color(Color::white);

		// Attachments //
		win.attach(c);
		win.attach(el);

		win.attach(c_north);
		win.attach(c_south);
		win.attach(c_east);
		win.attach(c_west);
		win.attach(c_cntr);
		win.attach(c_north_east);
		win.attach(c_south_east);
		win.attach(c_south_west);
		win.attach(c_north_west);

		win.attach(el_north);
		win.attach(el_south);
		win.attach(el_east);
		win.attach(el_west);
		win.attach(el_cntr);
		win.attach(el_north_east);
		win.attach(el_south_east);
		win.attach(el_south_west);
		win.attach(el_north_west);

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
