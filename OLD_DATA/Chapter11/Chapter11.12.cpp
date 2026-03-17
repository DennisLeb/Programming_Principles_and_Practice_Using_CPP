// 17/03/2026
// Chapter11.12.cpp
// Exercises

//
// [13] "Tile" a window with small right triangles.
// 

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#include "Chapter11.12.h"

int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 1080, 720, "Right Triangle Tiles" };

		// Triangles //
		Vector_ref<Right_triangle> triangles;

		constexpr int side_a_length = 120;		
		constexpr int side_b_length = 60;

		constexpr int tri_per_row = 18;
		constexpr int rows = 12;

		for (auto [i, tri_origin] = tuple<int, Point>{ 0, {0, 0} }; i < rows; ++i)
		{
			for (int j = 0; j < tri_per_row; j += 2)
			{
				triangles.push_back(make_unique<Right_triangle>(tri_origin, side_a_length, side_b_length));
				triangles.push_back(make_unique<Right_triangle>(Point{ tri_origin.x + side_a_length, tri_origin.y + side_b_length }, side_a_length, side_b_length, 180.));

				triangles[triangles.size() - 1].set_color(Color::white);
				triangles[triangles.size() - 2].set_color(Color::white);

				triangles[triangles.size() - 1].set_fill_color(Color::dark_cyan);
				triangles[triangles.size() - 2].set_fill_color(Color::dark_cyan);

				win.attach(triangles[triangles.size() - 1]);
				win.attach(triangles[triangles.size() - 2]);

				tri_origin.x += side_a_length;
			}
			tri_origin.x = 0;
			tri_origin.y += side_b_length;
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
