// 10/03/2026
// Chapter11.04.h
// Exercises

//
// This includes the 'Arrow' class from exercise [1] to further simplify drawing a diagram.
//

#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

/**********************************/
/******** CLASS DEFINITION ********/
/**********************************/
struct Arrow : Line		// Line with a Polygon at its tip (triangle)
{
	Arrow(const Point &p1, const Point &p2);

	void draw_specifics(Painter &painter) const override;

private:
	Polygon arrowhead;
};

/**********************************/
/******** HELPER FUNCTIONS ********/
/**********************************/
void rescale_to_max(int &primary_val, int &secondary_val, const int &max)
{
	if (primary_val == 0)
		error("invalid primary_val -> rescale_to_max()");

	double factor = 0.;
	if (primary_val < 0)
	{
		factor = double(-max) / double(primary_val);
		primary_val = -max;
	}
	else
	{
		factor = double(max) / double(primary_val);
		primary_val = max;
	}
	secondary_val = int(double(secondary_val) * factor);
}

/**********************************/
/******** MEMBER FUNCTIONS ********/
/**********************************/
Arrow::Arrow(const Point &p1, const Point &p2) :Line{ p1, p2 }
{
	// Make sure that: -arrow_size_max < delta_x/delta_y < arrow_size_max
	const int arrowhead_size_max = 15;

	int delta_x = p2.x - p1.x;
	int delta_y = p2.y - p1.y;

	// Scale up/down to size but keep proportions
	if (delta_x > arrowhead_size_max || delta_x < -arrowhead_size_max)	// Only need to rescale once
		rescale_to_max(delta_x, delta_y, arrowhead_size_max);

	else if (delta_y > arrowhead_size_max || delta_y < -arrowhead_size_max)
		rescale_to_max(delta_y, delta_x, arrowhead_size_max);

	// Top
	arrowhead.add({ p2.x + delta_x, p2.y + delta_y });
	// Right corner
	arrowhead.add({ p2.x - delta_y / 3, p2.y + delta_x / 3 });
	// Left corner
	arrowhead.add({ p2.x + delta_y / 3, p2.y - delta_x / 3 });
}

void Arrow::draw_specifics(Painter &painter) const
{
	Line::draw_specifics(painter);
	arrowhead.draw_specifics(painter);
}
