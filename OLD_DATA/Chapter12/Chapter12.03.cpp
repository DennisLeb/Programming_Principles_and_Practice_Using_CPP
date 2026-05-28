// 19/03/2026
// Chapter12.03.cpp
// Exercises

//
// [4] Define a class 'Immobile_Circle', which is just like 'Circle' but can't be moved.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/*----------------------------------------*\
| Class Definitions                        |
\*----------------------------------------*/
struct Immobile_Circle : Circle
{
	using Circle::Circle;

private:
	// Make it private to have compiler throw an error
	void move(int, int) override {}
};

/*----------------------------------------*\
| Main                                     |
\*----------------------------------------*/
int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 1080, 720, "Immobile Circle" };

		// Immobile_Circle //
		Immobile_Circle imm_circ{ {400, 300}, 200 };
		imm_circ.set_color(Color::white);

		// Doesn't work
		imm_circ.move(25, 75);

		win.attach(imm_circ);

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
