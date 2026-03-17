// 17/03/2026
// Chapter11.12.h
// Exercises

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
	rotation{ rotation_in_d }
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
