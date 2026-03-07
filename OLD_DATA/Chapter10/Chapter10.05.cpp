// 05/03/2026
// Chapter10.05.cpp
// Exercises

//
// [9] Display an image on the screen, e.g., a photo of a friend.
//     Label the image both with a title on the window and with a caption in the window.
//

#include "PPP/Graph.h";
#include "PPP/Simple_window.h";

using namespace Graph_lib;

int main()
{
	Application app;
	Simple_window win{ Point{20, 20}, 600, 400, "Let's all love Lain!" };

	Image img{ Point{125, 100}, "Chapter10.05.1.jpeg" };
	img.scale(300, 300);

	Text caption{ Point{170, 80}, "Let's all love Lain!" };
	caption.set_color(Color::white);

	win.attach(img);
	win.attach(caption);
	win.wait_for_button();
	return 0;
}
