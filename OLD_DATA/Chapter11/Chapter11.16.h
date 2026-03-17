// 17/03/2026
// Chapter11.16.cpp
// Exercises

/*------------------------------------------------------------------*\
| Class Definition                                                   |
\*------------------------------------------------------------------*/
struct Box : Rectangle	// A rectangle with a label
{
	Box(const Point &p, const int &ww, const int &hh, const string &s, const int &text_offset = 5)
		:Rectangle{ p, ww, hh },
		origin{ p },
		width{ ww },
		height{ hh },
		label{ {p.x + text_offset, p.y + hh / 3}, s }
	{}

	Box(const Point &p_1, const Point &p_2, const string &s, const int &text_offset = 5) 
		:Rectangle{ p_1, p_2 },
		origin{ p_1 },
		width{ p_2.x - p_1.x }, 
		height{ p_2.y - p_1.y },
		label{ { p_1.x + text_offset, p_1.y + (p_2.y - p_1.y) / 3 }, s }
	{}

	void draw_specifics(Painter &painter) const override;

	Point get_origin() const { return origin; }

	int get_width() const { return width; }
	int get_height() const { return height; }

	Text label;

private:
	Point origin;

	int width;
	int height;
};

/*------------------------------------------------------------------*\
| Member Functions                                                   |
\*------------------------------------------------------------------*/
void Box::draw_specifics(Painter &painter) const
{
	Rectangle::draw_specifics(painter);
	label.draw_specifics(painter);
}
