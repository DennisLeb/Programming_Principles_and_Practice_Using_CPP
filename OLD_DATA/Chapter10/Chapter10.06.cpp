// 05/03/2026
// Chapter10.06.cpp
// Exercises

//
// [10] Draw the source file diagram fron §10.8.1.
//

#include "PPP/Graph.h";
#include "PPP/Simple_window.h";

using namespace Graph_lib;

int main()
{
	Application app;
	Simple_window win{ Point{20, 20}, 600, 400, "Source file diagram" };

	//////////////
	// Ch10.cpp //
	//////////////
	Rectangle ch_10_file{ Point{150, 350}, 150, 20 };
	ch_10_file.set_color(Color::white);
	ch_10_file.set_fill_color(Color::yellow);

	Text ch_10_capt_1{ Point{150, 338}, "Ch10.cpp:" };
	ch_10_capt_1.set_font_size(7);
	ch_10_capt_1.set_color(Color::dark_cyan);

	Text ch_10_capt_2{ Point{155, 355}, "int main() {...}" };
	ch_10_capt_2.set_font_size(7);
	ch_10_capt_2.set_color(Color::dark_cyan);

	Line ch_10_arrow_1
	{ 
		Point{225, 350}, 
		Point{325, 300} 
	};
	ch_10_arrow_1.set_color(Color::white);
	
	Polygon ch_10_arrowhead_1
	{
		Point{325, 300},
		Point{318, 307},
		Point{315, 301}
	};
	ch_10_arrowhead_1.set_color(Color::white);
	ch_10_arrowhead_1.set_fill_color(Color::white);

	Line ch_10_arrow_2
	{ 
		Point{225, 350}, 
		Point{110, 225} 
	};
	ch_10_arrow_2.set_color(Color::white);
	
	Polygon ch_10_arrowhead_2
	{
		Point{110, 225},
		Point{125, 234},
		Point{115, 238}
	};
	ch_10_arrowhead_2.set_color(Color::white);
	ch_10_arrowhead_2.set_fill_color(Color::white);
	
	/////////////////////
	// Simple_window.h //
	/////////////////////
	Rectangle simple_window_file{ Point{250, 240}, 150, 60 };
	simple_window_file.set_color(Color::white);
	simple_window_file.set_fill_color(Color::yellow);

	Text simple_window_capt_1{ Point{250, 228}, "Simple_window.h:" };
	simple_window_capt_1.set_font_size(7);
	simple_window_capt_1.set_color(Color::dark_cyan);

	Text simple_window_capt_2{ Point{255, 245}, "// Simple window interface" };
	simple_window_capt_2.set_font_size(7);

	Text simple_window_capt_3{ Point{255, 257}, "struct Simple_window {...};" };
	simple_window_capt_3.set_font_size(7);
	simple_window_capt_3.set_color(Color::dark_cyan);
	
	Text simple_window_capt_4{ Point{255, 274}, "..." };
	simple_window_capt_4.set_font_size(7);

	Line simple_window_arrow_1
	{
		Point{400, 270},
		Point{490, 230}
	};
	simple_window_arrow_1.set_color(Color::white);

	Polygon simple_window_arrowhead_1
	{
		Point{490, 230},
		Point{483, 237},
		Point{480, 231}
	};
	simple_window_arrowhead_1.set_color(Color::white);
	simple_window_arrowhead_1.set_fill_color(Color::white);

	///////////
	// GUI.h //
	///////////
	Rectangle gui_file{ Point{415, 170}, 150, 60 };
	gui_file.set_color(Color::white);
	gui_file.set_fill_color(Color::yellow);

	Text gui_capt_1{ Point{415, 158}, "GUI.h:" };
	gui_capt_1.set_font_size(7);
	gui_capt_1.set_color(Color::dark_cyan);

	Text gui_capt_2{ Point{420, 175}, "// GUI interface" };
	gui_capt_2.set_font_size(7);

	Text gui_capt_3{ Point{420, 187}, "struct Button {...};" };
	gui_capt_3.set_font_size(7);
	gui_capt_3.set_color(Color::dark_cyan);

	Text gui_capt_4{ Point{420, 204}, "..." };
	gui_capt_4.set_font_size(7);

	Line gui_arrow_1
	{
		Point{415, 200},
		Point{385, 190}
	};
	gui_arrow_1.set_color(Color::white);

	Polygon gui_arrowhead_1
	{
		Point{385, 190},
		Point{394, 189},
		Point{391, 196}
	};
	gui_arrowhead_1.set_color(Color::white);
	gui_arrowhead_1.set_fill_color(Color::white);

	//////////////
	// Window.h //
	//////////////
	Rectangle window_file{ Point{235, 160}, 150, 60 };
	window_file.set_color(Color::white);
	window_file.set_fill_color(Color::yellow);

	Text window_capt_1{ Point{235, 148}, "Window.h:" };
	window_capt_1.set_font_size(7);
	window_capt_1.set_color(Color::dark_cyan);

	Text window_capt_2{ Point{240, 165}, "// Window interface" };
	window_capt_2.set_font_size(7);

	Text window_capt_3{ Point{240, 177}, "struct Window {...};" };
	window_capt_3.set_font_size(7);
	window_capt_3.set_color(Color::dark_cyan);

	Text window_capt_4{ Point{240, 194}, "..." };
	window_capt_4.set_font_size(7);

	Line window_arrow_1
	{
		Point{235, 190},
		Point{110, 95}
	};
	window_arrow_1.set_color(Color::white);

	Polygon window_arrowhead_1
	{
		Point{110, 95},
		Point{122, 100},
		Point{117, 104}
	};
	window_arrowhead_1.set_color(Color::white);
	window_arrowhead_1.set_fill_color(Color::white);

	/////////////
	// Graph.h //
	/////////////
	Rectangle graph_file{ Point{35, 165}, 150, 60 };
	graph_file.set_color(Color::white);
	graph_file.set_fill_color(Color::yellow);

	Text graph_capt_1{ Point{35, 153}, "Graph.h:" };
	graph_capt_1.set_font_size(7);
	graph_capt_1.set_color(Color::dark_cyan);

	Text graph_capt_2{ Point{40, 170}, "// Graphing interface" };
	graph_capt_2.set_font_size(7);

	Text graph_capt_3{ Point{40, 182}, "struct Shape {...};" };
	graph_capt_3.set_font_size(7);
	graph_capt_3.set_color(Color::dark_cyan);

	Text graph_capt_4{ Point{40, 197}, "..." };
	graph_capt_4.set_font_size(7);

	Line graph_arrow_1
	{
		Point{110, 165},
		Point{110, 95}
	};
	graph_arrow_1.set_color(Color::white);

	Polygon graph_arrowhead_1
	{
		Point{110, 95},
		Point{113, 106},
		Point{107, 106}
	};
	graph_arrowhead_1.set_color(Color::white);
	graph_arrowhead_1.set_fill_color(Color::white);

	/////////////
	// Point.h //
	/////////////
	Rectangle point_file{ Point{35, 75}, 150, 20 };
	point_file.set_color(Color::white);
	point_file.set_fill_color(Color::yellow);

	Text point_capt_1{ Point{35, 63}, "Point.h:" };
	point_capt_1.set_font_size(7);
	point_capt_1.set_color(Color::dark_cyan);

	Text point_capt_2{ Point{40, 80}, "struct Point {...};" };
	point_capt_2.set_font_size(7);
	point_capt_2.set_color(Color::dark_cyan);

	// Ch10.cpp //
	win.attach(ch_10_file);
	win.attach(ch_10_capt_1);
	win.attach(ch_10_capt_2);
	win.attach(ch_10_arrow_1);
	win.attach(ch_10_arrowhead_1);
	win.attach(ch_10_arrow_2);
	win.attach(ch_10_arrowhead_2);

	// Simple_window.h //
	win.attach(simple_window_file);
	win.attach(simple_window_capt_1);
	win.attach(simple_window_capt_2);
	win.attach(simple_window_capt_3);
	win.attach(simple_window_capt_4);
	win.attach(simple_window_arrow_1);
	win.attach(simple_window_arrowhead_1);

	// GUI.h //
	win.attach(gui_file);
	win.attach(gui_capt_1);
	win.attach(gui_capt_2);
	win.attach(gui_capt_3);
	win.attach(gui_capt_4);
	win.attach(gui_arrow_1);
	win.attach(gui_arrowhead_1);

	// Window.h //
	win.attach(window_file);
	win.attach(window_capt_1);
	win.attach(window_capt_2);
	win.attach(window_capt_3);
	win.attach(window_capt_4);
	win.attach(window_arrow_1);
	win.attach(window_arrowhead_1);

	// Graph.h //
	win.attach(graph_file);
	win.attach(graph_capt_1);
	win.attach(graph_capt_2);
	win.attach(graph_capt_3);
	win.attach(graph_capt_4);
	win.attach(graph_arrow_1);
	win.attach(graph_arrowhead_1);

	// Point.h //
	win.attach(point_file);
	win.attach(point_capt_1);
	win.attach(point_capt_2);

	win.wait_for_button();
	return 0;
}
