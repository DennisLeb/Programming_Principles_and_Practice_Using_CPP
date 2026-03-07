// 05/03/2026
// Chapter10.08.cpp
// Exercises

//
// [12] A superellipse is a two-dimensional shape defined by the equation
//			|x/a|^m + |y/b|^n = 1; where m > 0 and n > 0.
// 
//		Look up superellipse on the Web to get a better idea of what such shapes look like.
//		Write a program that draws "starlike" patterns by connecting points on a superellipse.
//		Take 'a', 'b', 'm', 'n' and 'N' as arguments. Select 'N' points on the superellipse defined by 'a', 'b', 'm', and 'n'.
//		Make the points equally spaced spaced for some definition of "equal".
//		Connect each of those 'N' points to one or more other points.
//		If you like you can make the number of points to which to connect a point another argument, or just use 'N - 1', i.e., all the other points.
//
// Note:
//     Large parts of my solution are based on an old forum post (likely a solution for this exercise from a previous edition of PPP).
//     Source - https://codereview.stackexchange.com/q/104026
// 
//     I couldn't really have figured this out on my own, since my math knowledge is quite limited.
//     I.e., I wouldn't have known how to simplify a lot of the mathematical functions I found during research.
//
// [13] Find a way to add color to the lines from the previous exercise.
//		Make some lines one color and other lines another color or other colors.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#define PI 3.14159265359

using namespace Graph_lib;

  /********************************/
/******** CLASS DEFINITION ********/
/********************************/

class Superellipse
{
public:
	Superellipse(const double &coeff_a, const double &coeff_b,
				 const double &exp_n, const double &exp_m,
				 const int &center_x, const int &center_y,
				 const double &precision);

	void draw(const int &, const int &) const;
	void draw_starmap(const int &, const int &) const;

private:
	vector<Point> coordinates;
};

  /********************************/
/******** UTILITY FUNCTION ********/
/********************************/

template <typename T>
int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}

  /********************************/
/******** MEMBER FUNCTIONS ********/
/********************************/

Superellipse::Superellipse(const double &coeff_a, const double &coeff_b, 
						   const double &exp_n, const double &exp_m, 
						   const int &center_x, const int &center_y, 
						   const double &precision = .01)
{
	if (precision < 0.01 || precision > 1) 
		error("precision out of range");

	for (auto [new_coordinates, d] = tuple<Point, double>{0, -1.}; d < 1.; d += precision)
	{
		double theta = d * PI;
		int x = coeff_a * pow(abs((double)cos(theta)), (double)2. / exp_m) * sgn(cos(theta));
		int y = coeff_b * pow(abs((double)sin(theta)), (double)2. / exp_n) * sgn(sin(theta));
		
		new_coordinates = Point(x + center_x, y + center_y);
		
		// Check for duplicate points
		if (coordinates.empty() || new_coordinates != *(coordinates.end() - 1))
			coordinates.push_back(new_coordinates);
	}
}

void Superellipse::draw(const int &win_width, const int &win_height) const
{
	///////////
   // Window //
   ///////////
	Application app;
	Simple_window win{ Point{50, 50}, win_width, win_height, "Superellipse" };

	// Center coordinates
	const int center_x = win_width / 2;
	const int center_y = win_height / 2;

	/////////
   // Axes //
   /////////
	Axis x_axis{ Axis::x, Point{100, center_y}, 600, 12, "x" };
	x_axis.set_color(Color::white);
	win.attach(x_axis);

	Axis y_axis{ Axis::y, Point{center_x, 500}, 400, 8, "y" };
	y_axis.set_color(Color::white);
	win.attach(y_axis);

	/////////
   // Text //
   /////////
	Text x_axis_max{ Point{695, 305}, "3" };
	x_axis_max.set_color(Color::white);
	x_axis_max.set_font_size(8);
	win.attach(x_axis_max);

	Text x_axis_min{ Point{90, 305}, "-3" };
	x_axis_min.set_color(Color::white);
	x_axis_min.set_font_size(8);
	win.attach(x_axis_min);

	Text y_axis_max{ Point{380, 100}, "2" };
	y_axis_max.set_color(Color::white);
	y_axis_max.set_font_size(8);
	win.attach(y_axis_max);

	Text y_axis_min{ Point{380, 495}, "-2" };
	y_axis_min.set_color(Color::white);
	y_axis_min.set_font_size(8);
	win.attach(y_axis_min);

	/////////////////
   // Superellipse //
   /////////////////
	Open_polyline super_e;
	super_e.set_color(Color::white);
	for (auto &pnt : coordinates)
		super_e.add(pnt);

	win.attach(super_e);
	win.wait_for_button();
}

void Superellipse::draw_starmap(const int &win_width, const int &win_height) const
{
	///////////
   // Window //
   ///////////
	Application app;
	Simple_window win(Point{ 50, 50 }, win_width, win_height, "Superellipse Starmap");

	// Center coordinates
	const int center_x = win_width / 2;
	const int center_y = win_height / 2;

	/////////
   // Axes //
   /////////
	Axis x_axis{ Axis::x, Point{100, center_y}, 600, 12, "x" };
	x_axis.set_color(Color::white);
	win.attach(x_axis);

	Axis y_axis{ Axis::y, Point{center_x, 500}, 400, 8, "y" };
	y_axis.set_color(Color::white);
	win.attach(y_axis);

	/////////
   // Text //
   /////////
	Text x_axis_max{ Point{695, 305}, "3" };
	x_axis_max.set_color(Color::white);
	x_axis_max.set_font_size(8);
	win.attach(x_axis_max);

	Text x_axis_min{ Point{90, 305}, "-3" };
	x_axis_min.set_color(Color::white);
	x_axis_min.set_font_size(8);
	win.attach(x_axis_min);

	Text y_axis_max{ Point{380, 100}, "2" };
	y_axis_max.set_color(Color::white);
	y_axis_max.set_font_size(8);
	win.attach(y_axis_max);

	Text y_axis_min{ Point{380, 495}, "-2" };
	y_axis_min.set_color(Color::white);
	y_axis_min.set_font_size(8);
	win.attach(y_axis_min);

	/////////////////
   // Draw starmap //
   /////////////////
	vector<Line*> starlines;
	for (int i = 0; i < coordinates.size() / 2; ++i)
	{
		Line *new_line = new Line{ coordinates[i], coordinates[coordinates.size() / 2 + i] };
		new_line->set_color(static_cast<Color>(randint(13)));
		starlines.push_back(new_line);
	}
	
	for (Line *line : starlines)
		win.attach(*line);
	
	win.wait_for_button();
	
	// I really hope this works like I think. This is the first time I've used the 'new' & 'delete' keywords.
	for (Line *line : starlines)
		delete line;
}

  /********************/
/******** MAIN ********/
/********************/

int main()
{
	try
	{
		// Window size
		const int win_width = 800;
		const int win_height = 600;

		// Center coordinates
		const int center_x = win_width / 2;
		const int center_y = win_height / 2;

		//////////////////
	   // Superellipses //
	   //////////////////
		double coeff_a = 100.;
		double coeff_b = 100.;

		double exp_n = 1. / 4.;
		double exp_m = 1. / 4.;

		for (int i = 0; i < 10; ++i)
		{
			Superellipse super_e{ coeff_a, coeff_b, exp_n, exp_m, center_x, center_y };
			super_e.draw(win_width, win_height);
			super_e.draw_starmap(win_width, win_height);

			coeff_a *= 1.1;
			coeff_b *= 1.1;
			exp_n *= 1.25;
			exp_m *= 1.25;
		}

		///////////
	   // Window //
	   ///////////
		Application app;
		Simple_window win{ Point{50, 50}, win_width, win_height, "Done!" };

		/////////
	   // Text //
	   /////////
		Text done_text{ Point{center_x - 110, center_y - 50}, "Done!" };
		done_text.set_font_size(50);
		done_text.set_color(Color::white);

		win.attach(done_text);
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
