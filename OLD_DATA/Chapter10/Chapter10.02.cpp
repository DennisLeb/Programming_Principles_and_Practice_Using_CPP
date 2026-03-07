// 05/03/2026
// Chapter10.02.cpp
// Exercises

//
// [6] What happens when you draw a 'Shape' that doesn't fit inside its window?
//     What happens when you draw a 'Window' that doesn't fit on your screen?
//     Write two programs that illustrate these two phenomena.
//

#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

/* This draws a 'Rectangle', that doesn't fit inside its window.
*  You can still see it whenever you resize the window though. It doesn't do anything severe, it just looks odd. *\/

int main()
{
	Application app;
	Simple_window win{ Point{20, 20}, 600, 400, "Oversized Rectangle" };

	Rectangle rect{ Point{0, 0}, 700, 500 };
	rect.set_fill_color(Color::dark_cyan);

	win.attach(rect);
	win.wait_for_button();
	return 0;
}

/**/

/* This draws a window 10-times the size of your screen width and height. For me it covers both my main and my second monitor.
*  It's obviously impractical and I don't see a reason to ever do anything like it. Still pretty funny though.
*  The window does seem to have a problem with displaying the "next" button on my system, which is kind of interesting.
*  It's also impossible to resize it to a larger size, for some reason. *\/

int main()
{
	Application app;
	Simple_window win{ Point{20, 20}, x_max() * 10, y_max() * 10, "Oversized window"};

	win.wait_for_button();
	return 0;
}

/**/
