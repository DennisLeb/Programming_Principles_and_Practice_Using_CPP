// 05/03/2026
// Chapter10.03.cpp
// Exercises

//
// [7] Draw a two-dimensional house seen from the front, the way a child would:
//     with a door, two windows, and a roof with a chimney.
//     Feel free to add details; maybe have "smoke" come out of the chimney.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;

int main()
{
	Application app;
	Simple_window win{ Point{20, 20}, 600, 400, "2D House" };

	// Intended values: [150, 150, 300, 200]
	constexpr int foundation_pos_x = 150;
	constexpr int foundation_pos_y = 150;
	constexpr int foundation_width = 300;
	constexpr int foundation_height = 200;

	Rectangle foundation{ Point{foundation_pos_x, foundation_pos_y}, foundation_width, foundation_height };
	foundation.set_fill_color(Color::dark_cyan);

	Rectangle door{ Point{foundation_pos_x + foundation_width / 3, foundation_pos_y + foundation_height * 2 / 3}, foundation_width / 5, foundation_height / 3 };
	door.set_fill_color(Color::dark_yellow);

	Rectangle window_1{ Point{foundation_pos_x + foundation_width / 10, foundation_pos_y + foundation_height / 2}, foundation_width / 6, foundation_height / 4 };
	window_1.set_fill_color(Color::cyan);

	Rectangle window_2{ Point{foundation_pos_x + foundation_width * 2 / 3, foundation_pos_y + foundation_height / 2}, foundation_width / 6, foundation_height / 4 };
	window_2.set_fill_color(Color::cyan);

	Rectangle chimney{ Point{foundation_pos_x + foundation_width / 4, foundation_pos_y - foundation_height / 2}, foundation_width / 10, foundation_height / 2 };
	chimney.set_fill_color(Color::red);

	Polygon roof
	{ 
		Point{foundation_pos_x - foundation_pos_x / 2, foundation_pos_y + foundation_pos_y / 5},
		Point{foundation_pos_x + foundation_width + foundation_pos_x / 2, foundation_pos_y + foundation_pos_y / 5},
		Point{foundation_pos_x + foundation_width / 2, foundation_pos_y - foundation_height / 2}
	};
	roof.set_fill_color(Color::dark_red);

	Ellipse smoke_1{ Point{foundation_pos_x + 25 + foundation_width / 5, foundation_pos_y - foundation_height * 2 / 3}, 35, 25 };
	smoke_1.set_fill_color(Color::white);

	Ellipse smoke_2{ Point{foundation_pos_x + foundation_width / 5, foundation_pos_y - foundation_height * 2 / 3}, 25, 35 };
	smoke_2.set_fill_color(Color::white);

	Circle smoke_3{ Point{foundation_pos_x - 25 + foundation_width / 5, foundation_pos_y - foundation_height * 2 / 3}, 25 };
	smoke_3.set_fill_color(Color::white);

	win.attach(foundation);
	win.attach(door);
	win.attach(window_1);
	win.attach(window_2);
	win.attach(chimney);
	win.attach(roof);
	win.attach(smoke_1);
	win.attach(smoke_2);
	win.attach(smoke_3);
	win.wait_for_button();
}
