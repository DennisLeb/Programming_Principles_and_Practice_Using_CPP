// 10/03/2026
// Chapter11.04.cpp
// Exercises

//
// [4] Write a program that draws a class diagram like the one in §10.6.
//     It will simplify matters if you start by defining a 'Box' class that is a rectangle with a text label.
//
// Note:
//     Why did I do it like this? Why didn't I just use loops for this one? Am I slow?
// 
//     Perchance.
//

#include "Chapter11.04.h"

/**********************************/
/******** CLASS DEFINITION ********/
/**********************************/
struct Box : Rectangle	// A rectangle with a label
{
	Box(const Point &p, const int &ww, const int &hh, const string &s, const int &text_offset = 5) :Rectangle{ p, ww, hh }, label{ {p.x + text_offset, p.y + hh / 3}, s } {}
	Box(const Point &p_1, const Point &p_2, const string &s, const int &text_offset = 5) :Rectangle{p_1, p_2}, label { { p_1.x + text_offset, p_1.y + (p_2.y - p_1.y) / 3 }, s} {}

	void draw_specifics(Painter &painter) const override;

private:
	Text label;
};

/*********************************/
/******** MEMBER FUNCTION ********/
/*********************************/
void Box::draw_specifics(Painter &painter) const
{
	Rectangle::draw_specifics(painter);
	label.draw_specifics(painter);
}

/*************************/
/******** TESTING ********/
/*************************/
void test_box()
{
	Application app;
	Simple_window win{ {50, 50}, 1080, 720, "Some boxes" };

	Box box_1{ {50, 50}, {250, 250}, "this is some text" };
	box_1.set_color(Color::dark_cyan);

	Box box_2{ {250, 100}, {400, 250}, "hello, box" };
	box_2.set_color(Color::dark_cyan);

	Box box_3{ {300, 300}, 450, 150, "hello again, box", 250 };
	box_3.set_fill_color(Color::dark_cyan);

	win.attach(box_1);
	win.attach(box_2);
	win.attach(box_3);
	win.wait_for_button();
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
		Simple_window win{ {50, 50}, 1080, 360, "Class diagram" };

		// Variables //
		const int box_width = 200;
		const int box_height = 50;

		const int small_box_width = 115;

		// Boxes //
		Box window_box{ {50, 50}, box_width, box_height, "Window", 69 };
		window_box.set_fill_color(Color::dark_cyan);
		
		Box line_style_box{ {win.x_max() / 2 - 100, 50}, box_width, box_height, "Line_style", 49};
		line_style_box.set_fill_color(Color::dark_cyan);
		
		Box color_box{ {win.x_max() - 250, 50}, box_width, box_height, "Color", 73};
		color_box.set_fill_color(Color::dark_cyan);
		
		Box simple_window_box{ {50, win.y_max() / 2 - 25}, box_width, box_height, "Simple_window", 30};
		simple_window_box.set_fill_color(Color::dark_cyan);
		
		Box shape_box{ {win.x_max() / 2 - 100, win.y_max() / 2 - 25}, box_width, box_height, "Shape", 71};
		shape_box.set_fill_color(Color::dark_cyan);
		
		Box point_box{ {win.x_max() - 250, win.y_max() / 2 - 25}, box_width, box_height, "Point", 73};
		point_box.set_fill_color(Color::dark_cyan);
		
		Box line_box{ {50, win.y_max() - 75}, small_box_width, box_height, "Line", 34};
		line_box.set_fill_color(Color::dark_cyan);
		
		Box lines_box{ {195, win.y_max() - 75}, small_box_width, box_height, "Lines", 32};
		lines_box.set_fill_color(Color::dark_cyan);
		
		Box polygon_box{ {339, win.y_max() - 75}, small_box_width, box_height, "Polygon", 21};
		polygon_box.set_fill_color(Color::dark_cyan);
		
		Box axis_box{ {484, win.y_max() - 75}, small_box_width, box_height, "Axis", 37};
		axis_box.set_fill_color(Color::dark_cyan);
		
		Box rectangle_box{ {629, win.y_max() - 75}, small_box_width, box_height, "Rectangle", 10};
		rectangle_box.set_fill_color(Color::dark_cyan);
		
		Box text_box{ {774, win.y_max() - 75}, small_box_width, box_height, "Text", 37};
		text_box.set_fill_color(Color::dark_cyan);
		
		Box image_box{ {919, win.y_max() - 75}, small_box_width, box_height, "Image", 32};
		image_box.set_fill_color(Color::dark_cyan);

		// Arrows //
		Arrow simple_window_arrow{ {simple_window_box.point(0).x + box_width / 2, simple_window_box.point(0).y}, {window_box.point(0).x + box_width / 2, simple_window_box.point(0).y - box_height + 10} };
		simple_window_arrow.set_color(Color::dark_cyan);
		simple_window_arrow.set_fill_color(Color::white);
		
		Arrow line_arrow{ {line_box.point(0).x + small_box_width / 2, line_box.point(0).y}, {shape_box.point(0).x + box_width / 2 - 15, shape_box.point(0).y + box_height + 3} };
		line_arrow.set_color(Color::dark_cyan);
		line_arrow.set_fill_color(Color::white);
		
		Arrow lines_arrow{ {lines_box.point(0).x + small_box_width / 2, lines_box.point(0).y}, {shape_box.point(0).x + box_width / 2 - 15, shape_box.point(0).y + box_height + 6} };
		lines_arrow.set_color(Color::dark_cyan);
		lines_arrow.set_fill_color(Color::white);
		
		Arrow polygon_arrow{ {polygon_box.point(0).x + small_box_width / 2, polygon_box.point(0).y}, {shape_box.point(0).x + box_width / 2 - 15, shape_box.point(0).y + box_height + 9} };
		polygon_arrow.set_color(Color::dark_cyan);
		polygon_arrow.set_fill_color(Color::white);
		
		Arrow axis_arrow{ {axis_box.point(0).x + small_box_width / 2, axis_box.point(0).y}, {shape_box.point(0).x + box_width / 2 - 1, shape_box.point(0).y + box_height + 15} };
		axis_arrow.set_color(Color::dark_cyan);
		axis_arrow.set_fill_color(Color::white);
		
		Arrow rectangle_arrow{ {rectangle_box.point(0).x + small_box_width / 2, rectangle_box.point(0).y}, {shape_box.point(0).x + box_width / 2 + 15, shape_box.point(0).y + box_height + 9} };
		rectangle_arrow.set_color(Color::dark_cyan);
		rectangle_arrow.set_fill_color(Color::white);
		
		Arrow text_arrow{ {text_box.point(0).x + small_box_width / 2, text_box.point(0).y}, {shape_box.point(0).x + box_width / 2 + 15, shape_box.point(0).y + box_height + 6} };
		text_arrow.set_color(Color::dark_cyan);
		text_arrow.set_fill_color(Color::white);
		
		Arrow image_arrow{ {image_box.point(0).x + small_box_width / 2, image_box.point(0).y}, {shape_box.point(0).x + box_width / 2 + 15, shape_box.point(0).y + box_height + 3} };
		image_arrow.set_color(Color::dark_cyan);
		image_arrow.set_fill_color(Color::white);

		// Attachments //
		win.attach(window_box);
		win.attach(line_style_box);
		win.attach(color_box);
		win.attach(simple_window_box);
		win.attach(shape_box);
		win.attach(point_box);
		win.attach(line_box);
		win.attach(lines_box);
		win.attach(polygon_box);
		win.attach(axis_box);
		win.attach(rectangle_box);
		win.attach(text_box);
		win.attach(image_box);

		win.attach(simple_window_arrow);
		win.attach(line_arrow);
		win.attach(lines_arrow);
		win.attach(polygon_arrow);
		win.attach(axis_arrow);
		win.attach(rectangle_arrow);
		win.attach(text_arrow);
		win.attach(image_arrow);

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
