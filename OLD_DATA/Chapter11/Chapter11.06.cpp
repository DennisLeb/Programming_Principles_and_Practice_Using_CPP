// 11/03/2026
// Chapter11.06.cpp
// Exercises

//
// [6] Define a class 'Regular_hexagon' (a regular hexagon is a six-sided polygon with all sides of equal length).
//     Use the center and the distance from the center to a corner point as constructor arguments.
//
// [7] Tile a part of a window with 'Regular_hexagon's (use at least eight hexagons).
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#define PI 3.14159265359

/*------------------------------------------------------------------*\
| Class Definition                                                   |
\*------------------------------------------------------------------*/
struct Regular_hexagon : Closed_polyline
{
	Regular_hexagon(const Point &cntr, const int &dist_to_cntr);
	void draw_specifics(Painter &painter) const override;

	int get_diag_y() const { return diag_y; }
	int get_diag_x() const { return diag_x; }

private:
	int diag_y;
	int diag_x;
};

/*------------------------------------------------------------------*\
| Member Functions                                                   |
\*------------------------------------------------------------------*/
Regular_hexagon::Regular_hexagon(const Point &cntr, const int &dist_to_cntr)
{
	diag_y = sqrt(3) * dist_to_cntr / 2;
	diag_x = dist_to_cntr - diag_y * tan(30 * PI / 180);	// Convert 30° to radians

	Closed_polyline::add({ cntr.x - diag_x, cntr.y + diag_y });	// A
	Closed_polyline::add({ cntr.x + diag_x, cntr.y + diag_y });	// B
	Closed_polyline::add({ cntr.x + dist_to_cntr, cntr.y });	// C
	Closed_polyline::add({ cntr.x + diag_x, cntr.y - diag_y });	// D
	Closed_polyline::add({ cntr.x - diag_x, cntr.y - diag_y });	// E
	Closed_polyline::add({ cntr.x - dist_to_cntr, cntr.y });	// F
}

void Regular_hexagon::draw_specifics(Painter &painter) const
{
	Closed_polyline::draw_specifics(painter);
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
		Simple_window win{ {50, 50}, 1080, 720, "Regular Hexagon" };

		// Hexagons //
		constexpr int hex_size = 25;
		constexpr int x_start_pos = 25, y_start_pos = 25;

		int x_pos = x_start_pos, y_pos = y_start_pos;

		Vector_ref<Regular_hexagon> hexes;
		for (int i = 1; i <= 384; ++i)
		{
			hexes.push_back(make_unique<Regular_hexagon>(Point{ x_pos, y_pos }, hex_size));
			hexes[hexes.size() - 1].set_fill_color(randint(255));

			if (i % 24)
			{
				x_pos += hex_size * 2 - hexes[hexes.size() - 1].get_diag_x();
				y_pos = i % 2 ? y_pos + hexes[hexes.size() - 1].get_diag_y() : y_pos - hexes[hexes.size() - 1].get_diag_y();
			}
			else
			{
				x_pos = x_start_pos;
				y_pos += hexes[hexes.size() - 1].get_diag_y();
			}
		}

		// Attachments //
		for (int i = 0; i < hexes.size(); ++i)
			win.attach(hexes[i]);

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
