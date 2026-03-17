// 17/03/2026
// Chapter11.13.cpp
// Exercises

//
// [14] Do the previous exercise, but with hexagons.
// 
// [15] Do the previous exercise, but using hexagons of a few different colors.
// 

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#include "Chapter11.13.h"

int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 1080, 720, "Hexagon Tiles" };

		// Hexagons //
		constexpr int hex_size = 30;
		constexpr int x_start_pos = hex_size;
		const int y_start_pos = (int)round(sqrt(3) * (double)hex_size / 2.);

		Vector_ref<Regular_hexagon> hexes;

		srand(time(0));
		for (auto [i, hex_center] = tuple<int, Point>{ 0, {x_start_pos, y_start_pos} }; i < 14; ++i)
		{
			for (int j = 0; j < 24; ++j)
			{
				hexes.push_back(make_unique<Regular_hexagon>(hex_center, hex_size));
				
				hexes[hexes.size() - 1].set_color(Color::white);
				hexes[hexes.size() - 1].set_fill_color(rand() % 256);

				hex_center.x += hex_size * 2 - hexes[hexes.size() - 1].get_diag_x();
				hex_center.y = j % 2 ? hex_center.y - hexes[hexes.size() - 1].get_diag_y() : hex_center.y + hexes[hexes.size() - 1].get_diag_y();

				win.attach(hexes[hexes.size() - 1]);
			}

			hex_center.x = x_start_pos;
			hex_center.y += 2 * hexes[hexes.size() - 1].get_diag_y(); 
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
