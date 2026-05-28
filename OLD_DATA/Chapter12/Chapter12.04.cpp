// 19/03/2026
// Chapter12.04.cpp
// Exercises

//
// [5] Define a 'Striped_rectangle' where instead of fill,
//     the rectangle is "filled" by drawing one-pixel-wide horizontal lines across the inside of the rectangle (say, draw every second line like that).
//     You may have to play with the width of lines and the line spacing to get a pattern you like.
//
// [6] Define a 'Striped_circle' class using the technique from 'Striped_rectangle'.
//
// [7] Define a 'Striped_closed_polyline' using the technique from 'Striped_rectangle' (this requires some algorhithmic inventiveness).
//
//     Sources:
//         https://en.wikipedia.org/wiki/Atan2
//     
//     INCOMPLETE. MIGHT RETURN TO THIS.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#define PI 3.14159265359

/*----------------------------------------*\
| Class Definitions                        |
\*----------------------------------------*/
struct Striped_rectangle : Rectangle
{
	using Rectangle::Rectangle;

protected:
	void draw_specifics(Painter &painter) const override;
};

struct Striped_circle : Circle
{
	using Circle::Circle;

protected:
	void draw_specifics(Painter &painter) const override;
};

/*
struct Striped_closed_polyline : Closed_polyline
{
	using Closed_polyline::Closed_polyline;

protected:
	void draw_specifics(Painter &painter) const override;
};
*/

/*----------------------------------------*\
| Helper Functions                         |
\*----------------------------------------*/
/*
// Taken out of 'Graph.cpp'
inline pair<double, double> line_intersect(const Point &p1, const Point &p2, const Point &p3, const Point &p4, bool &parallel)
{
	double x1 = p1.x;
	double x2 = p2.x;
	double x3 = p3.x;
	double x4 = p4.x;
	double y1 = p1.y;
	double y2 = p2.y;
	double y3 = p3.y;
	double y4 = p4.y;

	double denom = ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	if (denom == 0)
	{
		parallel = true;
		return pair<double, double>(0, 0);
	}

	parallel = false;
	return pair<double, double>
		(
			((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom,
			((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom
		);
}

// Taken out of 'Graph.cpp'
bool line_segment_intersect(const Point &p1, const Point &p2, const Point &p3, const Point &p4, Point &intersection)
{
	bool parallel;
	pair<double, double> u = line_intersect(p1, p2, p3, p4, parallel);

	if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) 
		return false;
	
	intersection.x = p1.x + u.first * (p2.x - p1.x);
	intersection.y = p1.y + u.first * (p2.y - p1.y);
	return true;
}

int getDirection(const int &x1, const int &x2)
{
	if (x1 > x2)		// Draw to the left
		return -1;
	else if (x1 < x2)	// Draw to the right
		return 1;
	else
		return 0;
}

// Draws in a given direction until intersection is found
Point getIntersectionPoint(const vector<Point> &points, const Point &start_p, const int &direction)
{
	// Go through opposing point pairs until 'max_delta_x' is surpassed //
	for (int i = points.size() - 1; i > 0; --i)
	{
		Point opposing_p_1 = points[i];
		Point opposing_p_2 = points[i - 1];
		
		int furthest_x;
		if (direction == 1)
			furthest_x = opposing_p_1.x > opposing_p_2.x ? opposing_p_1.x : opposing_p_2.x;
		else
			furthest_x = opposing_p_1.x < opposing_p_2.x ? opposing_p_1.x : opposing_p_2.x;

		for (int x_pos = start_p.x; abs(x_pos) < abs(furthest_x); x_pos += direction)
		{
			Point intersection{ 0, 0 };

			if (line_segment_intersect(start_p, { start_p.x + x_pos, start_p.y }, opposing_p_1, opposing_p_2, intersection))
				return intersection;
		}
	}
	return { 0, 0 };
}
*/

/*----------------------------------------*\
| Member Functions                         |
\*----------------------------------------*/
void Striped_rectangle::draw_specifics(Painter &painter) const
{
	Rectangle::draw_specifics(painter);

	if (fill_color().visibility())
	{
		for (int i = 0; i < height(); i += 8)
		{
			Line new_line{ {point(0).x, point(0).y + i}, {point(0).x + width(), point(0).y + i} };
			new_line.set_color(color());

			new_line.draw_specifics(painter);
		}

	} // draw_specifics() being const turned out to be pretty restrictive here, so I had to just keep the original fill in the background
}

void Striped_circle::draw_specifics(Painter &painter) const
{
	Circle::draw_specifics(painter);

	if (fill_color().visibility())
	{
		for (int i = 0; i < radius() * 2; i += 2)
		{	
			double theta = ((double)i / (double)radius() * 2.) * PI;

			Line new_line
			{ 
				Point{center().x - (int)round((double)radius() * cos(theta)), center().y + (int)round((double)radius() * sin(theta))},
				Point{center().x + (int)round((double)radius() * cos(theta)), center().y + (int)round((double)radius() * sin(theta))}
			};
			new_line.set_color(color());

			new_line.draw_specifics(painter);
		}
	}
}

/*
void Striped_closed_polyline::draw_specifics(Painter &painter) const
{
	Closed_polyline::draw_specifics(painter);

	if (fill_color().visibility() && number_of_points() > 2)
	{
		// Extract points vector from 'Shape' implementation (needed later) and find furthest x coordinate //
		vector<Point> points;
		int furthest_x = 0;
		for (int i = 0; i < number_of_points(); ++i)
		{
			points.push_back(point(i));

			if (furthest_x < abs(point(i).x))
				furthest_x = point(i).x;
		}


		Point draw_start = points[0];
		Point draw_end = points[1];

		// Go through point pairs //
		for (int i = 1; true; ++i)
		{
			// Returns angle between points
			double theta = atan2(draw_end.y - draw_start.y, draw_end.x - draw_start.x);

			int draw_direction = getDirection(draw_end.x, points[number_of_points() - i].x);
			if (!draw_direction)	// If x equal, check next pair
				goto skip_inner;
			

			// Draw lines between points //
			for (int j = 0; j < draw_start.y + draw_end.y; j += 8)
			{
				Point line_origin
				{ 
					draw_start.x + j * cos(theta) * draw_direction,
					draw_start.y + j * sin(theta) 
				};

				Point line_destination{getIntersectionPoint(points, line_origin, draw_direction)};

				Line new_line{ line_origin, line_destination };
				new_line.set_color(color());

				new_line.draw_specifics(painter);
			}

			skip_inner:
			if (draw_end.x == furthest_x)
				break;

			draw_start = point(i);
			draw_end = point(i + 1);
		}
	}
}
*/

/*----------------------------------------*\
| Main                                     |
\*----------------------------------------*/
int main()
{
	try
	{
		// Window //
		Application app;
		Simple_window win{ {50, 50}, 1080, 720, "Striped Shapes" };

		// Striped Shapes //
		Striped_rectangle striped_rect{ {300, 300}, 200, 150 };
		striped_rect.set_color(Color::yellow);
		striped_rect.set_fill_color(Color::dark_red);
		
		Striped_circle striped_circ{ {800, 200}, 100 };
		striped_circ.set_color(Color::magenta);
		striped_circ.set_fill_color(Color::dark_cyan);

		win.attach(striped_rect);
		win.attach(striped_circ);

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
