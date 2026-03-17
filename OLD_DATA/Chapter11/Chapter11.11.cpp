// 14/03/2026
// Chapter11.11.cpp
// Exercises

//
// [12] Define a right triangle class.
//		Make an octagonal shape out of eight right triangles of different colors.
// 
//		Note:
//			After some research, I found that it's not even possible to make an octagon with 8 right triangles. 
//			It only works with 8 isosceles triangles, which can be cut in half to make an octagon of 16 right triangles.
//			So I guess I'll be doing that instead.
//			
//			Figuring this out cost me ~2 hours that I'll never get back..
// 

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

#define PI 3.14159265359

/*------------------------------------------------------------------*\
| Class Definition                                                   |
\*------------------------------------------------------------------*/

/* Constructor arguments:				|\
*      - Point origin (top left)		| \
*      - int side_a						|  \
*      - int side_b				 side_b |   \
*      - int rotation_in_d = 0			|____\
*									    side_a
*/

struct Right_triangle : Polygon
{
	Right_triangle(const Point &origin, const int &side_a, const int &side_b, const double &rotation_in_d = 0);

	void draw_specifics(Painter &painter) const override;

	int get_side_a() const { return side_a; }
	int get_side_b() const { return side_b; }
	int get_side_c() const { return side_c; }
	double get_rotation() const { return rotation; }

private:
	const int side_a;
	const int side_b;
	const int side_c;
	const double rotation;
};

/*------------------------------------------------------------------*\
| Member Functions                                                   |
\*------------------------------------------------------------------*/
Right_triangle::Right_triangle(const Point &origin, const int &side_a, const int &side_b, const double &rotation_in_d)
	:side_a{ side_a }, side_b{ side_b },
	side_c{ (int)round(sqrt(pow((double)side_a, 2.) + pow((double)side_b, 2.))) },
	rotation{rotation_in_d}
{
	if (!side_a || !side_b)
		error("invalid side length -> Right_triangle()");

	Polygon::add(origin);

	if (!rotation_in_d)
	{
		Polygon::add(Point{ origin.x, origin.y + side_b });
		Polygon::add(Point{ origin.x + side_a, origin.y + side_b });
		return;
	}

	// Convert degrees to radians
	const double theta_1 = rotation_in_d * PI / 180.;

	// Use side_b as radius and sin(theta_1) as direction to draw in
	Point point_C{ (int)round((double)origin.x + (double)side_b * sin(theta_1)), (int)round((double)origin.y + (double)side_b * cos(theta_1)) };
	Polygon::add(point_C);

	// Add theta_1 to 90° as radians
	const double theta_2 = PI / 2 + theta_1;

	Point point_B{ (int)round((double)point_C.x + (double)side_a * sin(theta_2)), (int)round((double)point_C.y + (double)side_a * cos(theta_2)) };
	Polygon::add(point_B);
}

void Right_triangle::draw_specifics(Painter &painter) const
{
	Polygon::draw_specifics(painter);
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
		Simple_window win{ {50, 50}, 1080, 1080, "Right Triangles" };

		// Octagon / Triangles //
		constexpr int side_a_len = 300;
		constexpr int side_b_len = side_a_len * 0.415;	// For some reason this is the only proportion that will line up correctly when decrementing by 45°

		const Point oct_origin{ win.x_max() / 2, win.y_max() / 2 };
		Point tri_origin
		{
			oct_origin.x - side_b_len,
			oct_origin.y - side_a_len
		};

		Vector_ref<Right_triangle> triangles;

		// Seed for random colors
		srand(time(0));

		for (auto [i, angle] = tuple{0, 270.}; i < 8; ++i, angle -= 45.)
		{
			double theta = angle * PI / 180.;

			triangles.push_back(make_unique<Right_triangle>(tri_origin, side_a_len, -side_b_len, angle));

			tri_origin =
			{
				tri_origin.x - (int)round(2. * (double)side_b_len * sin(theta)),
				tri_origin.y - (int)round(2. * (double)side_b_len * cos(theta))
			};

			triangles.push_back(make_unique<Right_triangle>(tri_origin, side_a_len, side_b_len, angle));
			
			triangles[triangles.size() - 2].set_color(Color::white);
			triangles[triangles.size() - 2].set_fill_color(rand() % 256);
			triangles[triangles.size() - 1].set_color(Color::white);
			triangles[triangles.size() - 1].set_fill_color(rand() % 256);

			win.attach(triangles[triangles.size() - 2]);
			win.attach(triangles[triangles.size() - 1]);
		}

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
