// 14/03/2026
// Chapter11.10.cpp
// Exercises

//
// [11] Draw the color matrix from §11.7.3, but without lines around each color.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/*------------------------------------------------------------------*\
| Main                                                               |
\*------------------------------------------------------------------*/
int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 600, 360, "Ellipse Exercise" };
		
		// Color Squares //
		Vector_ref<Rectangle> squares;

		constexpr int max = 32;
		constexpr int side = 18;
		constexpr int left = 10;
		constexpr int top = 100;

		for (auto [color_index, i] = tuple{ 0, 0 }; i < max; ++i)	// Number of columns
			for (int j = 0; j < 8; ++j, ++color_index)				// 8 rows in each column
			{
				squares.push_back(make_unique<Rectangle>(Point{ i * side + left, j * side + top }, side, side));
				squares[squares.size() - 1].set_color(color_index);
				squares[squares.size() - 1].set_fill_color(color_index);
				win.attach(squares[squares.size() - 1]);
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
