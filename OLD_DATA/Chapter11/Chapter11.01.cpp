// 10/03/2026
// Chapter11.01.cpp
// Exercises

//
// [1] Define a class 'Arrow', which draws a line with an arrowhead.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/**********************************/
/******** CLASS DEFINITION ********/
/**********************************/
struct Arrow : Line		// Line with a Polygon at its tip (triangle)
{
	Arrow(const Point &p1, const Point &p2);
	
	void draw_specifics(Painter &painter) const override;

private:
	Polygon arrowhead;
};

/**********************************/
/******** HELPER FUNCTIONS ********/
/**********************************/
void rescale_to_max(int &primary_val, int &secondary_val, const int &max)
{
	if (primary_val == 0)
		error("invalid primary_val -> rescale_to_max()");

	double factor = 0.;
	if (primary_val < 0)
	{
		factor = double(-max) / double(primary_val);
		primary_val = -max;
	}
	else
	{
		factor = double(max) / double(primary_val);
		primary_val = max;
	}
	secondary_val = int(double(secondary_val) * factor);
}

/**********************************/
/******** MEMBER FUNCTIONS ********/
/**********************************/
Arrow::Arrow(const Point &p1, const Point &p2) :Line{p1, p2}
{
	// Make sure that: -arrow_size_max < delta_x/delta_y < arrow_size_max
	const int arrowhead_size_max = 15;

	int delta_x = p2.x - p1.x;
	int delta_y = p2.y - p1.y;

	// Scale up/down to size but keep proportions
	if (delta_x > arrowhead_size_max || delta_x < -arrowhead_size_max)	// Only need to rescale once
		rescale_to_max(delta_x, delta_y, arrowhead_size_max);

	else if (delta_y > arrowhead_size_max || delta_y < -arrowhead_size_max)
		rescale_to_max(delta_y, delta_x, arrowhead_size_max);

	// Top
	arrowhead.add({ p2.x + delta_x, p2.y + delta_y });
	// Right corner
	arrowhead.add({ p2.x - delta_y / 3, p2.y + delta_x / 3 });
	// Left corner
	arrowhead.add({ p2.x + delta_y / 3, p2.y - delta_x / 3 });
}

void Arrow::draw_specifics(Painter &painter) const
{
	Line::draw_specifics(painter);
	arrowhead.draw_specifics(painter);
}

/**********************/
/******** MAIN ********/
/**********************/
int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 1080, 720, "Arrows" };

		// Arrow definitions //
		Arrow arr1{ {win.x_max() / 3, win.y_max() / 2 }, { win.x_max() / 2, win.y_max() / 2 } };
		arr1.set_style(Line_style(Line_style::solid, 5));
		arr1.set_color(Color::red);
		
		Arrow arr2{ { win.x_max() / 2, win.y_max() / 2 }, { 800, 300 } };
		arr2.set_color(Color::cyan);
		arr2.set_fill_color(Color::cyan);
		
		Arrow arr3{ { 800, 300 }, { 500, 200 } };
		arr3.set_color(Color::green);
		arr3.set_fill_color(Color::dark_magenta);
		
		Arrow arr4{ { 50, 50 }, { 50, 200 } };
		arr4.set_style(Line_style(Line_style::dash, 4));
		arr4.set_color(139);
		arr4.set_fill_color(139);
		
		Arrow arr5{ { 50, 600 }, { 800, 600 } };
		arr5.set_color(Color::white);

		// Attachments //
		win.attach(arr1);
		win.attach(arr2);
		win.attach(arr3);
		win.attach(arr4);
		win.attach(arr5);
		
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
