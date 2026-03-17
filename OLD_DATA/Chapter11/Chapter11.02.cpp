// 10/03/2026
// Chapter11.02.cpp
// Exercises

//
// [2] Define functions 'n()', 's()', 'e()', 'w()', 'center()', 'ne()', 'se()', 'sw()', and 'nw()'.
//     Each takes a 'Rectangle' argument and returns a 'Point'. These functions define "connection points" on and in the rectangle.
//     For example, 'nw(r)' is the northwest (top left) corner of a 'Rectangle' called 'r'.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/**********************************/
/******** HELPER FUNCTIONS ********/
/**********************************/
Point n(const Rectangle &r) { return { r.point(0).x + r.width() / 2, r.point(0).y }; }

Point s(const Rectangle &r) { return { r.point(0).x + r.width() / 2, r.point(0).y + r.height() }; }

Point e(const Rectangle &r) { return { r.point(0).x + r.width(), r.point(0).y + r.height() / 2 }; }

Point w(const Rectangle &r) { return { r.point(0).x, r.point(0).y + r.height() / 2 }; }

Point center(const Rectangle &r) { return { r.point(0).x + r.width() / 2, r.point(0).y + r.height() / 2 }; }

Point ne(const Rectangle &r) { return { r.point(0).x + r.width(), r.point(0).y }; }

Point se(const Rectangle &r) { return { r.point(0).x + r.width(), r.point(0).y + r.height() }; }

Point sw(const Rectangle &r) { return { r.point(0).x, r.point(0).y + r.height() }; }

Point nw(const Rectangle &r) { return { r.point(0).x, r.point(0).y }; }

/**********************/
/******** MAIN ********/
/**********************/
int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 540, 360, "Rectangle connection points" };

		// Rectangle //
		Rectangle r{ {win.x_max() / 6, win.y_max() / 8}, win.x_max() * 2 / 3, win.y_max() * 3 / 4 };
		r.set_fill_color(Color::dark_cyan);
		
		// Connection Points //
		Mark north{ n(r), 'N' };
		north.set_color(Color::white);
		
		Mark south{ s(r), 'S' };
		south.set_color(Color::white);
		
		Mark east{ e(r), 'E' };
		east.set_color(Color::white);
		
		Mark west{ w(r), 'W' };
		west.set_color(Color::white);
		
		Mark cntr{ center(r), 'C' };
		cntr.set_color(Color::white);
		
		Text north_east{ ne(r), "NE" };
		north_east.set_color(Color::white);
		
		Text south_east{ se(r), "SE" };
		south_east.set_color(Color::white);
		
		Text south_west{ sw(r), "SW" };
		south_west.set_color(Color::white);
		
		Text north_west{ nw(r), "NW" };
		north_west.set_color(Color::white);

		// Attachments //
		win.attach(r);
		win.attach(north);
		win.attach(south);
		win.attach(east);
		win.attach(west);
		win.attach(cntr);
		win.attach(north_east);
		win.attach(south_east);
		win.attach(south_west);
		win.attach(north_west);

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
