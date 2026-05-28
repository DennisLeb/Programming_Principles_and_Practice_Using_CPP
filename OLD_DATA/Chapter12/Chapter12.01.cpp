// 19/03/2026
// Chapter12.01.cpp
// Exercises

//
// [1] Define two classes 'Smiley' and 'Frowny', which are both derived from class 'Circle' and have two eyes and a mouth.
//     Next derive classes from 'Smiley' and 'Frowny', which add an appropriate hat to each.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/*----------------------------------------*\
| Class Definitions                        |
\*----------------------------------------*/
struct Smiley : Circle
{
	using Circle::Circle;

protected:
	void draw_specifics(Painter &painter) const override;
};

struct Frowny : Circle
{
	using Circle::Circle;

protected:
	void draw_specifics(Painter &painter) const override;
};

struct Hatted_smiley : Smiley
{
	using Smiley::Smiley;

protected:
	void draw_specifics(Painter &painter) const override;
};

struct Hatted_frowny : Frowny
{
	using Frowny::Frowny;

protected:
	void draw_specifics(Painter &painter) const override;
};

/*----------------------------------------*\
| Member Functions                         |
\*----------------------------------------*/
void Smiley::draw_specifics(Painter &painter) const
{
	Circle left_eye{ { center().x - radius() / 3, center().y - radius() / 3}, radius() / 8 };
	Circle right_eye{ { center().x + radius() / 3, center().y - radius() / 3}, radius() / 8};

	Arc mouth{ { center().x, center().y + radius() / 3}, radius() / 2, radius() / 4, 180, 180 };

	// Draw surrounding Circle on top layer
	Circle::draw_specifics(painter);

	left_eye.draw_specifics(painter);
	right_eye.draw_specifics(painter);
	mouth.draw_specifics(painter);
}

void Frowny::draw_specifics(Painter &painter) const
{
	Circle left_eye{ { center().x - radius() / 3, center().y - radius() / 3}, radius() / 8 };
	Circle right_eye{ { center().x + radius() / 3, center().y - radius() / 3}, radius() / 8};

	Arc mouth{ { center().x, center().y + radius() / 2}, radius() / 2, radius() / 4, 0, 180 };

	// Draw surrounding Circle on top layer
	Circle::draw_specifics(painter);

	left_eye.draw_specifics(painter);
	right_eye.draw_specifics(painter);
	mouth.draw_specifics(painter);
}

void Hatted_smiley::draw_specifics(Painter &painter) const
{
	Line hat_base{ { center().x - radius() * 3 / 4, point(0).y }, { center().x + radius() * 3 / 4, point(0).y } };

	// Smiley gets a rectangular hat
	Rectangle hat_top{ { center().x - radius() / 2, point(0).y - radius() / 3}, radius(), radius() / 3};

	Smiley::draw_specifics(painter);
	hat_base.draw_specifics(painter);
	hat_top.draw_specifics(painter);
}

void Hatted_frowny::draw_specifics(Painter &painter) const
{
	Line hat_base{ { center().x - radius() * 3 / 4, point(0).y }, { center().x + radius() * 3 / 4, point(0).y } };
	
	// Frowny gets a triangular hat
	Polygon hat_top{ { center().x - radius() / 2, point(0).y}, {center().x, point(0).y - radius() / 3} , {center().x + radius() / 2, point(0).y} };
	
	Frowny::draw_specifics(painter);
	hat_base.draw_specifics(painter);
	hat_top.draw_specifics(painter);
}


/*----------------------------------------*\
| Main                                     |
\*----------------------------------------*/
int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 1080, 720, "Smiley and Frowny" };

		// Smileys / Frowneys //
		Smiley smiley_1{ {300, 300}, 150 };
		smiley_1.set_color(Color::white);
		
		Smiley smiley_2{ {700, 400}, 300 };
		smiley_2.set_color(Color::white);
		smiley_2.set_style(Line_style(Line_style::dash, 10));
		
		Smiley smiley_3{ {540, 500}, 75 };
		smiley_3.set_color(Color::white);
		
		Smiley smiley_4{ {150, 600}, 25 };
		smiley_4.set_color(Color::white);
		smiley_4.set_fill_color(Color::dark_cyan);

		Frowny frowny_1{ {50, 400}, 50 };
		frowny_1.set_color(Color::white);

		Frowny frowny_2{ {100, 150}, 100 };
		frowny_2.set_color(Color::white);
		frowny_2.set_fill_color(Color::dark_red);

		Hatted_smiley hat_smiley_1{ {300, 125}, 85 };
		hat_smiley_1.set_color(Color::white);

		Hatted_frowny hat_frowny_1{ {600, 125}, 85 };
		hat_frowny_1.set_color(Color::white);
		hat_frowny_1.set_fill_color(Color::dark_blue);

		// Attachments //
		win.attach(smiley_1);
		win.attach(smiley_2);
		win.attach(smiley_3);
		win.attach(smiley_4);

		win.attach(frowny_1);
		win.attach(frowny_2);

		win.attach(hat_smiley_1);
		win.attach(hat_frowny_1);

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
