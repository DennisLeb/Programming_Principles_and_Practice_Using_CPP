// 17/03/2026
// Chapter11.13.h
// Exercises

#define PI 3.14159265359

/*------------------------------------------------------------------*\
| Class Definition                                                   |
\*------------------------------------------------------------------*/
struct Regular_hexagon : Closed_polyline
{
	Regular_hexagon(const Point &cntr, const int &dist_to_cntr);
	void draw_specifics(Painter &painter) const override;

	int get_diag_y() const { return diag_y; }
	int get_diag_x() const { return diag_x; }

private:
	int diag_y;
	int diag_x;
};

/*------------------------------------------------------------------*\
| Member Functions                                                   |
\*------------------------------------------------------------------*/
Regular_hexagon::Regular_hexagon(const Point &cntr, const int &dist_to_cntr)
{
	diag_y = sqrt(3) * dist_to_cntr / 2;
	diag_x = dist_to_cntr - diag_y * tan(30 * PI / 180);	// Convert 30° to radians

	Closed_polyline::add({ cntr.x - diag_x, cntr.y + diag_y });	// A
	Closed_polyline::add({ cntr.x + diag_x, cntr.y + diag_y });	// B
	Closed_polyline::add({ cntr.x + dist_to_cntr, cntr.y });	// C
	Closed_polyline::add({ cntr.x + diag_x, cntr.y - diag_y });	// D
	Closed_polyline::add({ cntr.x - diag_x, cntr.y - diag_y });	// E
	Closed_polyline::add({ cntr.x - dist_to_cntr, cntr.y });	// F
}

void Regular_hexagon::draw_specifics(Painter &painter) const
{
	Closed_polyline::draw_specifics(painter);
}
