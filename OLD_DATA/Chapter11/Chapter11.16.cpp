// 17/03/2026
// Chapter11.16.cpp
// Exercises

//
// [18] There is an 'Arc' class in 'Graph.h'.
//		Find it and use it to define a box with rounded corners.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#include "Chapter11.16.h"

/*------------------------------------------------------------------*\
| Class Definition                                                   |
\*------------------------------------------------------------------*/
struct Rounded_box : Box
{
	using Box::Box;

	void draw_specifics(Painter &painter) const override;
};

/*------------------------------------------------------------------*\
| Member Functions                                                   |
\*------------------------------------------------------------------*/


void Rounded_box::draw_specifics(Painter &painter) const
{
	constexpr int arc_len = 15;

	const int origin_x = this->get_origin().x;
	const int origin_y = this->get_origin().y;

	const int box_width = this->get_width();
	const int box_height = this->get_height();

	Lines lines
	{
		// TL -> TR
		{origin_x + arc_len, origin_y },
		{origin_x + box_width - arc_len, origin_y},

		// TR -> BR
		{origin_x + box_width, origin_y + arc_len},
		{origin_x + box_width, origin_y + box_height - arc_len},

		// BR -> BL
		{origin_x + box_width - arc_len, origin_y + box_height },
		{origin_x + arc_len, origin_y + box_height },

		// BL -> TL
		{origin_x, origin_y + box_height - arc_len},
		{origin_x, origin_y + arc_len },
	};

	Arc arc_1{ {origin_x + arc_len, origin_y + arc_len}, arc_len, arc_len, 90, 90 };							// TL
	Arc arc_2{ {origin_x + box_width - arc_len, origin_y + arc_len}, arc_len, arc_len, 0, 90 };					// TR
	Arc arc_3{ {origin_x + box_width - arc_len, origin_y + box_height - arc_len}, arc_len, arc_len, 270, 90 };	// BR
	Arc arc_4{ {origin_x + arc_len, origin_y + box_height - arc_len}, arc_len, arc_len, 180, 90 };				// BL

	lines.draw_specifics(painter);
	arc_1.draw_specifics(painter);
	arc_2.draw_specifics(painter);
	arc_3.draw_specifics(painter);
	arc_4.draw_specifics(painter);
	this->label.draw_specifics(painter);
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
		Simple_window win{ {50, 50}, 1080, 720, "Box With Rounded Corners" };

		// Rounded_boxes //
		Rounded_box box_1{ {win.x_max() / 4, win.y_max() / 4}, {win.x_max() * 3 / 4, win.y_max() * 3 / 4}, "This box has rounded corners", 100 };
		box_1.set_color(Color::white);

		Rounded_box box_2{ {75, 225}, 100, 400, "Why the long face?" };
		box_2.set_color(Color::white);

		Rounded_box box_3{ {800, 550}, 200, 150, "Bottom-right gang" };
		box_3.set_color(Color::white);

		// Attachments //
		win.attach(box_1);
		win.attach(box_2);
		win.attach(box_3);

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
