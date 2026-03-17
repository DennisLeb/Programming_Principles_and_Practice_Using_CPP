// 11/03/2026
// Chapter11.05.cpp
// Exercises

//
// [5] Make an RGB color chart (e.g., search the Web for "RGB color chart").
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

vector<Color> rgb_colors
{
	{51, 0, 0},			{51, 25, 0},		{51, 51, 0},		{25, 51, 0},		{0, 51, 51},		{0, 0, 51},
	{102, 0, 0},		{102, 51, 0},		{102, 102, 0},		{51, 102, 0},		{0, 102, 102},		{0, 0, 102},
	{153, 0, 0},		{153, 76, 0},		{153, 153, 0},		{76, 153, 0},		{0, 153, 153},		{0, 0, 153},
	{204, 0, 0},		{204, 102, 0},		{204, 204, 0},		{102, 204, 0},		{0, 204, 204},		{0, 0, 204},
	{255, 0, 0},		{255, 128, 0},		{255, 255, 0},		{128, 255, 0},		{0, 255, 255},		{0, 0, 255},
	{255, 51, 51},		{255, 153, 51},		{255, 255, 51},		{153, 255, 51},		{51, 255, 255},		{51, 51, 255},
	{255, 102, 102},	{255, 178, 102},	{255, 255, 102},	{178, 255, 102},	{102, 255, 255},	{102, 102, 255},
	{255, 153, 153},	{255, 204, 153},	{255, 255, 153},	{204, 255, 153},	{153, 255, 255},	{153, 153, 255},
	{255, 204, 204},	{255, 229, 204},	{255, 255, 204},	{229, 255, 204},	{204, 255, 255},	{204, 204, 255}
};

int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 360, 540, "RGB Color Chart" };

		// Squares //
		const int square_size = 50;
		int pos_x = 25, pos_y = 25;

		vector<Rectangle *> squares;
		for (auto it = rgb_colors.begin(); it != rgb_colors.end();)
		{
			for (int j = 0; j < 6; ++j, ++it)
			{
				Rectangle *new_square = new Rectangle{ {pos_x, pos_y}, square_size, square_size };
				new_square->set_fill_color(*it);
				squares.push_back(new_square);
				pos_x += square_size;
			}
			pos_y += square_size;
			pos_x -= square_size * 6;
		}

		// Attachments //
		for (Rectangle *square : squares)
			win.attach(*square);

		win.wait_for_button();

		for (Rectangle *square : squares)
			delete square;

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
