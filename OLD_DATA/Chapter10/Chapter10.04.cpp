// 05/03/2026
// Chapter10.04.cpp
// Exercises

//
// [8] Draw the Olympic five rings. If you can't remember the colors, look them up.
//

#include "PPP/Graph.h";
#include "PPP/Simple_window.h";

using namespace Graph_lib;

int main()
{
	Application app;
	Simple_window win{ Point{20, 20}, 600, 400, "Olympic Rings" };

	Circle blue_ring{ Point{125, 100}, 50 };
	blue_ring.set_style(Line_style(Line_style::solid, 6));
	blue_ring.set_color(Color::blue);

	Circle yellow_ring{ Point{185, 150}, 50 };
	yellow_ring.set_style(Line_style(Line_style::solid, 6));
	yellow_ring.set_color(Color::yellow);

	Circle black_ring{ Point{245, 100}, 50 };
	black_ring.set_style(Line_style(Line_style::solid, 6));

	Circle green_ring{ Point{305, 150}, 50 };
	green_ring.set_style(Line_style(Line_style::solid, 6));
	green_ring.set_color(Color::green);

	Circle red_ring{ Point{365, 100}, 50 };
	red_ring.set_style(Line_style(Line_style::solid, 6));
	red_ring.set_color(Color::red);

	win.attach(blue_ring);
	win.attach(yellow_ring);
	win.attach(black_ring);
	win.attach(green_ring);
	win.attach(red_ring);
	win.wait_for_button();
	return 0;
}
