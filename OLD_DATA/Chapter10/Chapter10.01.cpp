// 04/03/2026
// Chapter10.01.cpp
// Exercises

//
// [1] Draw a rectangle as a 'Rectangle' and as a 'Polygon'.
//     Make the lines of the 'Polygon' red and the lines of the 'Rectangle' blue.
//
// [2] Draw a 100-by-30 'Rectangle' and place the text "Howdy!" inside it.
//
// [3] Draw your initials 150 pixels high. Use a thick line. Draw each initial in a different color.
//
// [4] Draw a 3-by-3 tic-tac-toe board of alternating white and red squares.
//
// [5] Draw a red 1/4-inch frame around a rectangle that is three-quarters the height of your screen and two-thirds the width.
//
// [6] What happens when you draw a 'Shape' that doesn't fit inside its window?
//     What happens when you draw a 'Window' that doesn't fit on your screen?
//     Write two programs that illustrate these two phenomena.
//

#include "PPP/Simple_window.h"
#include "PPP/Graph.h"

using namespace Graph_lib;

int main()
{
    Application app;
    Simple_window win({ 20, 20 }, 1200, 800, "Exercise");

    // [1]
    Rectangle rect{ Point{25, 25}, 50, 25 };
    rect.set_color(Color::blue);

    Polygon poly_rect{ Point{100, 25} };
    poly_rect.add(Point{ 150, 25 });
    poly_rect.add(Point{ 150, 50 });
    poly_rect.add(Point{ 100, 50 });
    poly_rect.set_color(Color::red);

    // [2]
    Rectangle howdy_rect{ Point{175, 25}, 100, 30 };
    howdy_rect.set_color(Color::white);

    Text howdy{ Point{195, 30}, "Howdy!" };
    howdy.set_color(Color::white);

    // [3]
    Mark first_initial{ Point{25, (win.y_max() - 150)}, 'D' };
    first_initial.set_font(Font::courier_bold);
    first_initial.set_font_size(50);
    first_initial.set_color(Color::blue);

    Mark last_initial{ Point{60, (win.y_max() - 150)}, 'L' };
    last_initial.set_font(Font::courier_bold);
    last_initial.set_font_size(50);
    last_initial.set_color(Color::red);

    // [4] look below for less disgusting solution I unfortunately couldn't implement.
    Rectangle ttt_rect_1{ Point{25,75}, 20, 20 };
    ttt_rect_1.set_fill_color(Color::white);
    Rectangle ttt_rect_2{ Point{45,75}, 20, 20 };
    ttt_rect_2.set_fill_color(Color::red);
    Rectangle ttt_rect_3{ Point{65,75}, 20, 20 };
    ttt_rect_3.set_fill_color(Color::white);
    Rectangle ttt_rect_4{ Point{25,95}, 20, 20 };
    ttt_rect_4.set_fill_color(Color::red);
    Rectangle ttt_rect_5{ Point{45,95}, 20, 20 };
    ttt_rect_5.set_fill_color(Color::white);
    Rectangle ttt_rect_6{ Point{65,95}, 20, 20 };
    ttt_rect_6.set_fill_color(Color::red);
    Rectangle ttt_rect_7{ Point{25,115}, 20, 20 };
    ttt_rect_7.set_fill_color(Color::white);
    Rectangle ttt_rect_8{ Point{45,115}, 20, 20 };
    ttt_rect_8.set_fill_color(Color::red);
    Rectangle ttt_rect_9{ Point{65,115}, 20, 20 };
    ttt_rect_9.set_fill_color(Color::white);

    // [5]
    Rectangle framed_rect{ Point{100,75}, (x_max() * 2 / 3), (y_max() * 3 / 4) };

    Lines frame
    { 
        // Top left to top right 
        Point{100, 75},
        Point{(x_max() * 2 / 3) + 100, 75},

        // Top right to bottom right 
        Point{(x_max() * 2 / 3) + 100, 75},
        Point{(x_max() * 2 / 3) + 100, (y_max() * 3 / 4) + 75 },

        // Bottom right to bottom left
        Point{(x_max() * 2 / 3) + 100, (y_max() * 3 / 4) + 75 },
        Point{100, (y_max() * 3 / 4) + 75 },
        
        // Bottom left to top right
        Point{100, (y_max() * 3 / 4) + 75 },
        Point{100, 75}
    };
    frame.set_style(Line_style(Line_style::solid, 24)); // 0.25 inch == 24 pixel
    frame.set_color(Color::red);

    /* I could've just done the following, but I wanted to test the 'Lines' class :)
    framed_rect.set_style(Line_style(Line_style::solid, 24));
    framed_rect.set_color(Color::red);
    */

    win.attach(rect);
    win.attach(poly_rect);
    win.attach(howdy_rect);
    win.attach(howdy);
    win.attach(first_initial);
    win.attach(last_initial);
    win.attach(ttt_rect_1);
    win.attach(ttt_rect_2);
    win.attach(ttt_rect_3);
    win.attach(ttt_rect_4);
    win.attach(ttt_rect_5);
    win.attach(ttt_rect_6);
    win.attach(ttt_rect_7);
    win.attach(ttt_rect_8);
    win.attach(ttt_rect_9);
    win.attach(framed_rect);
    win.attach(frame);

    win.wait_for_button();
}

/* This was supposed to be my solution for [4], but it seems that the Rectangle type is 'non-copyable' for some reason, preventing me from using a vector for the squares.
*  Now that I think about it, a nested for-loop with y_origin being altered in the outer loop would've been even better.

vector<Rectangle> ttt_squares;
for (auto [i, x_origin, y_origin] = tuple{ 1, 25, 75 }; i <= 9; ++i)
{
    if (i % 3 == 0 /* This is why i==1 *\/)
    {
        y_origin += 20;
        x_origin -= 60;
    }

    Rectangle new_square{ Point{x_origin, y_origin}, 20, 20 };

    // Alternate colors
    (i % 2 == 0 ? new_square.set_fill_color(Color::red) : new_square.set_fill_color(Color::white));
    ttt_squares.push_back(new_square);

    x_origin += 20;
}
    
for (auto& sqr : ttt_squares)
    win.attach(sqr);
*/